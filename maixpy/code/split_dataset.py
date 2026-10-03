"""按比例划分 YOLO 数据集到 train 和 val。

默认复制文件，不删除源文件。图片和同名标签会同步进入相同的数据集划分。
使用前修改顶部全局变量即可。
"""

from pathlib import Path
import random
import shutil


# ==================== 可修改的全局变量 ====================
DATASET_DIR = Path(r"D:/桌面/工训/test_datasets_2")
IMAGES_DIR = DATASET_DIR / "images"
LABELS_DIR = DATASET_DIR / "labels"

# 只需要修改这两个数字，例如 7:2 或 8:2。
TRAIN_RATIO = 7
VAL_RATIO = 3

IMAGE_EXTENSIONS = {".jpg", ".jpeg", ".png", ".bmp"}
LABEL_EXTENSION = ".txt"
RANDOM_SEED = 20261002

# False=复制，True=移动。建议先保持 False。
MOVE_FILES = False

# True 时只显示划分结果，不复制或移动任何文件。
DRY_RUN = False

# 已存在同名文件时是否覆盖。False 更安全。
OVERWRITE_EXISTING = False

# 没有对应标签时："skip" 跳过，"image_only" 仍划分图片，"error" 直接报错。
# 当前目录没有标签文件，因此默认仍划分图片；目标检测项目可改成 "skip"。
MISSING_LABEL_POLICY = "image_only"
# =========================================================


def collect_images():
    """只读取 images 根目录，自动排除已有的 train/val 子目录。"""
    return sorted(
        path
        for path in IMAGES_DIR.iterdir()
        if path.is_file() and path.suffix.lower() in IMAGE_EXTENSIONS
    )


def destination_path(source_path: Path, split: str, root: Path):
    return root / split / source_path.name


def copy_or_move(source: Path, destination: Path):
    if DRY_RUN:
        return
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists() and not OVERWRITE_EXISTING:
        raise FileExistsError("目标文件已存在: {}".format(destination))
    if MOVE_FILES:
        shutil.move(str(source), str(destination))
    else:
        shutil.copy2(source, destination)


def main():
    if not IMAGES_DIR.is_dir():
        raise FileNotFoundError("图片目录不存在: {}".format(IMAGES_DIR))
    if not LABELS_DIR.is_dir():
        raise FileNotFoundError("标签目录不存在: {}".format(LABELS_DIR))
    if TRAIN_RATIO <= 0 or VAL_RATIO <= 0:
        raise ValueError("TRAIN_RATIO 和 VAL_RATIO 必须大于 0")
    if MISSING_LABEL_POLICY not in {"skip", "image_only", "error"}:
        raise ValueError("MISSING_LABEL_POLICY 设置不正确")

    pairs = []
    skipped = []
    for image_path in collect_images():
        label_path = LABELS_DIR / (image_path.stem + LABEL_EXTENSION)
        if not label_path.exists():
            if MISSING_LABEL_POLICY == "error":
                raise FileNotFoundError("缺少标签: {}".format(label_path))
            if MISSING_LABEL_POLICY == "skip":
                skipped.append(image_path.name)
                continue
            label_path = None
        pairs.append((image_path, label_path))

    random.Random(RANDOM_SEED).shuffle(pairs)
    train_count = round(len(pairs) * TRAIN_RATIO / (TRAIN_RATIO + VAL_RATIO))
    train_items = pairs[:train_count]
    val_items = pairs[train_count:]

    for split, items in (("train", train_items), ("val", val_items)):
        for image_path, label_path in items:
            image_destination = destination_path(image_path, split, IMAGES_DIR)
            copy_or_move(image_path, image_destination)
            if label_path is not None:
                label_destination = destination_path(label_path, split, LABELS_DIR)
                copy_or_move(label_path, label_destination)

    print("总样本: {}".format(len(pairs)))
    print("train: {} ({})".format(len(train_items), TRAIN_RATIO))
    print("val: {} ({})".format(len(val_items), VAL_RATIO))
    print("跳过无标签图片: {}".format(len(skipped)))
    print("完成。DRY_RUN={}, MOVE_FILES={}".format(DRY_RUN, MOVE_FILES))


if __name__ == "__main__":
    main()
