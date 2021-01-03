## Building
- `cd MarBot/ros-noetic/`
- `catkin_make`
- `source devel/setup.bash`

## Note for UMA Members
If you're trying to run this on a Raspberry Pi in `uma-env-rpi`, here's a couple extra steps I didn't add to image itself:
- `sudo apt-get install libwiringpi-dev`
- `sudo chown uma /dev/gpiomem` (this is bad but it worked so w/e)

If you're trying to run/compile the controller side of things, you'll also need:
- `sudo apt-get install libsdl2-dev`
