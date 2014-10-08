import numpy as np
import serial
import time

serialPort = '/dev/tty.usbmodem1421' # Mac OS


if __name__=="__main__":
	#poses = {0, 1, 2, 3, 4, 5, 6, 0xfffff}
	ser = serial.Serial(serialPort, 9600)
	last = 0
	while(1):
		fp = open('myo.txt')
		for i,x in enumerate(fp):
			if i < last:
				continue
			ser.write([int(x)])
			time.sleep(0.005)
