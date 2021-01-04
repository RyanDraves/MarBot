# MarBot
Raspberry Pi Robot Experimentation. The goal is implement basic teleoperation capabilities via various platforms, such as ROS & ZMQ. The host computer will run a simple GUI that allows for this manual control.

## Common Dependencies
On the Pi:
- `sudo apt-get install libwiringpi-dev`

On the host computer:
- `sudo apt-get install libsdl2-dev`

Note that certain environments will require both Pi and host dependencies if your build command builds both versions simulataneously (i.e. a lazy `catkin_make` for ROS Noetic).

## Wiring Schematic
The robot in question assumes a simple setup where the Raspberry Pi is connected to two motors it can control forward and backward. This code currently hardcodes PWM 8, 9, 10, & 11 for the left and right motors (two each). If you're actually attempting to use the repository on a robot, the odds are low you'd wire it the same way, so just play aroud until it drives properly.

## Note For UMA Members
If you happen to be attempting to run the UM::Autonomy environment on a Raspberry Pi and want to move it around, please see the ROS Noetic folder for its README. Other platforms are irrelevant for you.
