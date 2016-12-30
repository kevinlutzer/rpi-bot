# Author: Kevin Lutzer
# Date: Dec 29 2016
# Description: Script to control the rpi motors over ssh

#imports
import RPi.GPIO as GPIO
import time
import sys

#gpio pin connections to the h-bridge
MOTORL_N = 5
MOTORL_P = 6
MOTORR_P = 13
MOTORR_N = 19

#function to init the gpio states as well as the BCM python module
def init_gpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(MOTORL_N, GPIO.OUT)
    GPIO.setup(MOTORL_P, GPIO.OUT)
    GPIO.setup(MOTORR_N, GPIO.OUT)
    GPIO.setup(MOTORR_P, GPIO.OUT)

# function to make the robot go forward
def go_fwd():
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


init_gpio()
go_fwd()
time.sleep(10)
stop_m()
GPIO.cleanup()
