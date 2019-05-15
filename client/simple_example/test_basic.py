from gpiozero import Robot
import time

robot = Robot(left=(7,8), right=(9,10))

robby.forward(0.4)
time.sleep(2)

robby.right(0.4)
time.sleep(2)