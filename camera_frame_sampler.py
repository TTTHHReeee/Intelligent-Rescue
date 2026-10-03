from maix import app, camera, display
import os


# Save one JPEG for every N camera frames. Increase this value to save less often.
SAVE_EVERY_N_FRAMES = 30
SAVE_DIR = "/root/images"
CAMERA_WIDTH = 640
CAMERA_HEIGHT = 480


def next_image_index(directory):
    """Find an unused filename so earlier captures are preserved."""
    index = 1
    while os.path.exists("{}/frame_{:06d}.jpg".format(directory, index)):
        index += 1
    return index


def main():
    os.makedirs(SAVE_DIR, exist_ok=True)

    cam = camera.Camera(CAMERA_WIDTH, CAMERA_HEIGHT)
    disp = display.Display()
    frame_count = 0
    image_index = next_image_index(SAVE_DIR)

    print("Saving one frame every {} frames to {}".format(SAVE_EVERY_N_FRAMES, SAVE_DIR))

    while not app.need_exit():
        img = cam.read()
        disp.show(img)
        frame_count += 1

        if frame_count % SAVE_EVERY_N_FRAMES == 0:
            image_path = "{}/frame_{:06d}.jpg".format(SAVE_DIR, image_index)
            img.save(image_path)
            print("Saved {}".format(image_path))
            image_index += 1


if __name__ == "__main__":
    main()
