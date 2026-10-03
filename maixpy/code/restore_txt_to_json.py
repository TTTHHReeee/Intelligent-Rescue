"""Restore LabelMe JSON annotations from a YOLO TXT archive.

Each TXT row must use the normalized YOLO format:
    class_id center_x center_y width height
"""

from __future__ import annotations

import io
import json
import zipfile
from pathlib import Path

from PIL import Image


# ==================== User-adjustable settings ====================
INPUT_ZIP = Path(r"D:\桌面\工训\datasets_2\labels\train_txt.zip")
OUTPUT_DIR = Path(r"D:\桌面\工训\datasets_2\labels\train_json")
OVERWRITE_EXISTING = True
JSON_VERSION = "3.3.5"
# ================================================================


def read_classes(archive: zipfile.ZipFile) -> list[str]:
    class_entry = next(
        (
            name
            for name in archive.namelist()
            if Path(name).name.lower() == "classes.txt"
        ),
        None,
    )
    if class_entry is None:
        raise FileNotFoundError("classes.txt was not found in the archive")

    labels = [line.strip() for line in archive.read(class_entry).decode("utf-8-sig").splitlines()]
    labels = [label for label in labels if label]
    if not labels:
        raise ValueError("classes.txt does not contain any labels")
    return labels


def image_entry_for_txt(archive: zipfile.ZipFile, txt_name: str) -> str:
    stem = Path(txt_name).stem
    candidates = [
        name
        for name in archive.namelist()
        if Path(name).stem == stem
        and Path(name).suffix.lower() in {".jpg", ".jpeg", ".png", ".bmp"}
    ]
    if len(candidates) != 1:
        raise FileNotFoundError(
            "Expected one image for {}, found {}".format(txt_name, candidates)
        )
    return candidates[0]


def parse_yolo_rows(
    raw_text: str,
    labels: list[str],
    txt_name: str,
    image_width: int,
    image_height: int,
) -> list[dict]:
    shapes = []
    for line_number, line in enumerate(raw_text.splitlines(), start=1):
        line = line.strip()
        if not line:
            continue

        fields = line.split()
        if len(fields) != 5:
            raise ValueError(
                "{} line {} must contain 5 fields, got {}".format(
                    txt_name, line_number, len(fields)
                )
            )

        try:
            class_id = int(fields[0])
            center_x, center_y, box_width, box_height = map(float, fields[1:])
        except ValueError as exc:
            raise ValueError(
                "{} line {} contains a non-numeric value".format(txt_name, line_number)
            ) from exc

        if not 0 <= class_id < len(labels):
            raise ValueError(
                "{} line {} uses class id {} outside classes.txt".format(
                    txt_name, line_number, class_id
                )
            )
        if not all(0.0 <= value <= 1.0 for value in (center_x, center_y, box_width, box_height)):
            raise ValueError(
                "{} line {} has coordinates outside the normalized 0..1 range".format(
                    txt_name, line_number
                )
            )
        if box_width <= 0.0 or box_height <= 0.0:
            raise ValueError(
                "{} line {} has a non-positive box size".format(txt_name, line_number)
            )

        shapes.append(
            {
                "label": labels[class_id],
                "score": None,
                "points": [
                    [
                        (center_x - box_width / 2.0) * image_width,
                        (center_y - box_height / 2.0) * image_height,
                    ],
                    [
                        (center_x + box_width / 2.0) * image_width,
                        (center_y - box_height / 2.0) * image_height,
                    ],
                    [
                        (center_x + box_width / 2.0) * image_width,
                        (center_y + box_height / 2.0) * image_height,
                    ],
                    [
                        (center_x - box_width / 2.0) * image_width,
                        (center_y + box_height / 2.0) * image_height,
                    ],
                ],
                "group_id": None,
                "description": "",
                "difficult": False,
                "shape_type": "rectangle",
                "flags": {},
                "attributes": {},
                "kie_linking": [],
            }
        )

    return shapes


def make_labelme_json(
    image_name: str, image_width: int, image_height: int, shapes: list[dict]
) -> dict:
    return {
        "version": JSON_VERSION,
        "flags": {},
        "shapes": shapes,
        "imagePath": Path(image_name).name,
        "imageData": None,
        "imageHeight": image_height,
        "imageWidth": image_width,
        "description": "",
    }


def main() -> None:
    if not INPUT_ZIP.is_file():
        raise FileNotFoundError("Input archive does not exist: {}".format(INPUT_ZIP))

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    generated = 0

    with zipfile.ZipFile(INPUT_ZIP) as archive:
        labels = read_classes(archive)
        txt_entries = sorted(
            name
            for name in archive.namelist()
            if Path(name).suffix.lower() == ".txt"
            and Path(name).name.lower() != "classes.txt"
        )

        if not txt_entries:
            raise FileNotFoundError("No annotation TXT files were found in the archive")

        for txt_name in txt_entries:
            image_name = image_entry_for_txt(archive, txt_name)
            output_path = OUTPUT_DIR / (Path(txt_name).stem + ".json")
            if output_path.exists() and not OVERWRITE_EXISTING:
                continue

            with Image.open(io.BytesIO(archive.read(image_name))) as image:
                image_width, image_height = image.size

            shapes = parse_yolo_rows(
                archive.read(txt_name).decode("utf-8-sig"),
                labels,
                txt_name,
                image_width,
                image_height,
            )
            data = make_labelme_json(image_name, image_width, image_height, shapes)
            output_path.write_text(
                json.dumps(data, ensure_ascii=False, indent=2) + "\n",
                encoding="utf-8",
            )
            generated += 1

    print("labels:", ", ".join(labels))
    print("TXT files:", len(txt_entries))
    print("JSON files generated:", generated)
    print("output:", OUTPUT_DIR)


if __name__ == "__main__":
    main()
