"""Print the AXModel output names and shapes on MaixCAM2."""

from maix import nn


MODEL_PATH = "/root/my_model/model_9531.mud"


def describe(value):
    for field in ("name", "shape", "dtype", "format"):
        try:
            print("  {} = {}".format(field, getattr(value, field)))
        except Exception:
            pass
    print("  repr = {}".format(value))


def main():
    print("Loading generic model: {}".format(MODEL_PATH))
    model = nn.NN(MODEL_PATH)

    print("Model type: {}".format(type(model)))
    print("Model attributes: {}".format([name for name in dir(model) if "info" in name.lower()]))

    for method_name in ("inputs_info", "outputs_info"):
        method = getattr(model, method_name, None)
        print("{} available: {}".format(method_name, method is not None))
        if method is None:
            continue
        try:
            values = method()
            print("{} count: {}".format(method_name, len(values)))
            for index, value in enumerate(values):
                print("{}[{}]:".format(method_name, index))
                describe(value)
        except Exception as exc:
            print("{} failed: {}".format(method_name, exc))

    try:
        print("extra_info = {}".format(model.extra_info()))
    except Exception as exc:
        print("extra_info failed: {}".format(exc))


if __name__ == "__main__":
    main()
