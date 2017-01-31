import serial
import time
import sys
from curtsies import Input

# set up serial object
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)
if ser.isOpen():
    print "Port is open and connection is made.\n"

# function that sets the direction of the motors
def set_dir(dir):
    if dir == "KEY_UP" or dir == "w":
        ser.write('o')
        print 'fwd\n'
    elif dir == " " or dir == "b":
        ser.write('_')
        print 'stp\n'
    elif dir == "KEY_LEFT" or dir == "a":
        ser.write('?')
        print 'lft\n'
    elif dir == "KEY_RIGHT" or dir == "d":
        ser.write('O')
        print 'rgt\n'
    elif dir == "KEY_DOWN" or dir == "s":
        ser.write('/')
        print 'bwd\n'
    else:
        ser.write('_')

# main
def main():
    with Input(keynames='curses') as input_generator:
        for e in input_generator:
            set_dir(e)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        sys.exit()
