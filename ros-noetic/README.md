## Dependencies
A ROS Noetic installation.

## Building
- `cd MarBot/ros-noetic/`
- `catkin_make` (use `--only-pkg-with-deps [package_name]` if you wish to avoid installing Pi & host dependencies on the same machine)
- `source devel/setup.bash` (you can do this once)

## Running
First, figure out either the IP address or hostname of your Raspberry Pi. This will be `[pi_address]` in the commands below.

On the Pi:
- `export ROS_MASTER_URI=http://[pi_address]:11311`
- `roscore &`
- `rosrun marbot_teleop marbot_teleop_node`

On the host:
- `export ROS_MASTER_URI=http://[pi_address]:11311`
- `rosrun marbot_teleop_controller marbot_teleop_controller_node`

## Note for UMA Members
If you're trying to run this on a Raspberry Pi in `uma-env-rpi`, here's a couple extra steps I didn't add to image itself:
- `sudo apt-get install libwiringpi-dev libsdl2-dev`
- `sudo chown uma /dev/gpiomem` (this is bad but it worked so w/e)

The fact that you're in a Docker image on the Pi should be irrelevant, as they're configured to use host networking. You can use `uma-env` on the host machine just the same, just keep in mind that WSL2 is unlikely to work since Windows won't let you share host networking (at least not in the way you need it to).
