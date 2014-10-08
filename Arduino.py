import numpy as np
import serial
import time

serialPort = '/dev/tty.usbmodem1421' # Mac OS


if __name__=="__main__":
	poses = {0, 1, 2, 3, 4, 5, 6, 0xfffff}
	ser = serial.Serial(serialPort, 9600)
	last = 0
	laspose = 0
	pos = np.zeros((1,3))
	while(1):
		fp = open('myo.txt')
		for i,x in enumerate(fp):
			if i < last:
				continue
			num = x.split(" ")     
			if num[-1] == '':
				num = np.delete(num, -1)
			if float(num[-1]) in poses:
				lastpose = int(num[-1])
				pos = np.array(num[-4:-1])
			else:
				pos = np.array(num[-3:])
			pos = pos.astype(np.intc)
			ser.write([pos[0], pos[1], pos[2], lastpose])
			time.sleep(0.005)
