"""按排序结果给文件重新编号。

使用前只需要修改下面的全局变量。默认只处理 TARGET_DIR 这一层的文件，
不会进入 train、val 等子目录；RECURSIVE=True 时会对每个子目录分别编号。
"""

from pathlib import Path
import re
import uuid


# ==================== 可修改的全局变量 ====================
TARGET_DIR = Path(r"D:\桌面\工训\images_2\images_2")
RECURSIVE = False
FILE_EXTENSIONS = {".jpg", ".jpeg", ".png", ".bmp"}

NAME_PREFIX = "image_"
START_INDEX = 787
INDEX_DIGITS = 6

# True 只打印计划，不真正改名；确认结果后改为 False。
DRY_RUN = False

# True 按文件名中的数字排序，例如 image_2 排在 image_10 前面。
NATURAL_SORT = True
# =========================================================


def natural_key(path: Path):
    """按人类直觉排序文件名。"""
    parts = re.split(r"(\d+)", path.name.lower())
    return [int(part) if part.isdigit() else part for part in parts]


def sort_key(path: Path):
    return natural_key(path) if NATURAL_SORT else path.name.lower()


def files_in(directory: Path):
    extensions = {ext.lower() for ext in FILE_EXTENSIONS}
    iterator = directory.rglob("*") if RECURSIVE else directory.iterdir()
    return sorted(
        (
            path
            for path in iterator
            if path.is_file()
            and path.suffix.lower() in extensions
        ),
        key=sort_key,
    )


def rename_group(files):
    if not files:
        return

    # 先改成临时名，避免 image_1 和 image_2 互换时互相覆盖。
    temporary = []
    for path in files:
        temp_path = path.with_name(".__rename_tmp_{}__{}".format(uuid.uuid4().hex, path.name))
        temporary.append((path, temp_path))
        if not DRY_RUN:
            path.rename(temp_path)

    for offset, (old_path, temp_path) in enumerate(temporary):
        index = START_INDEX + offset
        new_name = "{}{:0{}d}{}".format(
            NAME_PREFIX,
            index,
            INDEX_DIGITS,
            old_path.suffix.lower(),
        )
        new_path = old_path.with_name(new_name)
        print("{} -> {}".format(old_path, new_path))
        if not DRY_RUN:
            temp_path.rename(new_path)


def main():
    if not TARGET_DIR.is_dir():
        raise FileNotFoundError("目录不存在: {}".format(TARGET_DIR))

    if RECURSIVE:
        grouped = {}
        for path in files_in(TARGET_DIR):
            grouped.setdefault(path.parent, []).append(path)
        for directory in sorted(grouped):
            rename_group(sorted(grouped[directory], key=sort_key))
    else:
        rename_group(files_in(TARGET_DIR))

    print("完成。DRY_RUN={}".format(DRY_RUN))


if __name__ == "__main__":
    main()
