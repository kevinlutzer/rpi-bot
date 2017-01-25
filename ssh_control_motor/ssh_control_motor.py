# Author: Kevin Lutzer
# Date: Dec 29 2016
# Description: Script to control the rpi motors over ssh

#imports
import RPi.GPIO as GPIO
import time
import sys
from curtsies import Input

#gpio pin connections to the h-bridge
MOTORL_N = 5
MOTORL_P = 6
MOTORR_P = 13
MOTORR_N = 19

# function to init the gpio states as well as the BCM python module
def init_gpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(MOTORL_N, GPIO.OUT)
    GPIO.setup(MOTORL_P, GPIO.OUT)
    GPIO.setup(MOTORR_N, GPIO.OUT)
    GPIO.setup(MOTORR_P, GPIO.OUT)

# function to make the robot go forward
def go_bwd():
    GPIO.output(MOTORL_N, GPIO.HIGH)
    GPIO.output(MOTORL_P, GPIO.LOW)
    GPIO.output(MOTORR_N, GPIO.HIGH)
    GPIO.output(MOTORR_P, GPIO.LOW)

# stop all motors from moving
def stop_m():
    GPIO.output(MOTORL_N, GPIO.LOW)
    GPIO.output(MOTORL_P, GPIO.LOW)
    GPIO.output(MOTORR_N, GPIO.LOW)
    GPIO.output(MOTORR_P, GPIO.LOW)

# go backwards with motors
def go_fwd():
    GPIO.output(MOTORL_N, GPIO.LOW)
    GPIO.output(MOTORL_P, GPIO.HIGH)
    GPIO.output(MOTORR_N, GPIO.LOW)
    GPIO.output(MOTORR_P, GPIO.HIGH)

# move left
def go_lft():
    GPIO.output(MOTORL_N, GPIO.HIGH)
    GPIO.output(MOTORL_P, GPIO.LOW)
    GPIO.output(MOTORR_N, GPIO.LOW)
    GPIO.output(MOTORR_P, GPIO.HIGH)

# move right
def go_rgt():
    GPIO.output(MOTORL_N, GPIO.LOW)
    GPIO.output(MOTORL_P, GPIO.HIGH)
    GPIO.output(MOTORR_N, GPIO.HIGH)
    GPIO.output(MOTORR_P, GPIO.LOW)

# function that sets the direction of the motors
def set_dir(dir):
    if dir == "KEY_UP" or dir == "w":
        go_fwd()
    elif dir == " " or dir == "b":
        stop_m()
    elif dir == "KEY_LEFT" or dir == "a":
        go_lft()
    elif dir == "KEY_RIGHT" or dir == "d":
        go_rgt()
    elif dir == "KEY_DOWN" or dir == "s":
        go_bwd()
    else:
        stop_m()


def main():
    init_gpio()
    with Input(keynames='curses') as input_generator:
        for e in input_generator:
            set_dir(e)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        GPIO.cleanup()
        sys.exit()
