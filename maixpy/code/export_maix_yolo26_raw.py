"""Expose YOLO26 one-to-one detection heads as six ONNX outputs.

The original Ultralytics export keeps a decoded end-to-end output named
``output0``.  MaixHub/MaixPy YOLO26 conversion expects three bbox outputs and
three class outputs instead, so this script creates a separate ONNX file whose
graph outputs are those six existing tensors.
"""

from pathlib import Path
import shutil

import onnx
import onnxruntime as ort


# ==================== User-adjustable settings ====================
INPUT_ONNX = Path(__file__).resolve().parent / "runs" / "detect" / "train-6" / "weights" / "best.onnx"
OUTPUT_ONNX = INPUT_ONNX.with_name("best_maix.onnx")

OUTPUT_NAMES = [
    "/model.23/one2one_cv2.0/one2one_cv2.0.2/Conv_output_0",
    "/model.23/one2one_cv2.1/one2one_cv2.1.2/Conv_output_0",
    "/model.23/one2one_cv2.2/one2one_cv2.2.2/Conv_output_0",
    "/model.23/one2one_cv3.0/one2one_cv3.0.2/Conv_output_0",
    "/model.23/one2one_cv3.1/one2one_cv3.1.2/Conv_output_0",
    "/model.23/one2one_cv3.2/one2one_cv3.2.2/Conv_output_0",
]

# Keep a backup if the chosen output path already exists.
BACKUP_EXISTING_OUTPUT = True
# ================================================================


def value_info_by_name(model):
    entries = list(model.graph.value_info)
    entries.extend(model.graph.input)
    entries.extend(model.graph.output)
    return {entry.name: entry for entry in entries}


def main():
    if not INPUT_ONNX.is_file():
        raise FileNotFoundError("Input ONNX does not exist: {}".format(INPUT_ONNX))

    model = onnx.load(str(INPUT_ONNX), load_external_data=False)
    entries = value_info_by_name(model)
    missing = [name for name in OUTPUT_NAMES if name not in entries]
    if missing:
        raise RuntimeError("Required YOLO26 output tensors are missing: {}".format(missing))

    if OUTPUT_ONNX.exists() and BACKUP_EXISTING_OUTPUT:
        backup = OUTPUT_ONNX.with_suffix(".backup.onnx")
        shutil.copy2(OUTPUT_ONNX, backup)
        print("Backed up existing output to: {}".format(backup))

    del model.graph.output[:]
    for name in OUTPUT_NAMES:
        output_info = onnx.ValueInfoProto()
        output_info.CopyFrom(entries[name])
        model.graph.output.append(output_info)

    onnx.checker.check_model(model)
    OUTPUT_ONNX.parent.mkdir(parents=True, exist_ok=True)
    onnx.save(model, str(OUTPUT_ONNX))

    session = ort.InferenceSession(
        str(OUTPUT_ONNX),
        providers=["CPUExecutionProvider"],
    )
    outputs = session.get_outputs()
    print("Created: {}".format(OUTPUT_ONNX))
    print("Output count: {}".format(len(outputs)))
    for output in outputs:
        print("{} {}".format(output.name, output.shape))


if __name__ == "__main__":
    main()
