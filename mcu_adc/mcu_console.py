# -*- coding: utf-8 -*-
import threading
import serial
import sys

#console command: python mcu_console.py /dev/ttyUSB1 115200

class ThreadClass(threading.Thread):
  def run(self):
    while not done:
      sys.stdout.write(device.readline())

if __name__=="__main__":
  # port open
  devPort = sys.argv[1]
  bitsPerSecond = sys.argv[2]
  try:
    device = serial.Serial(devPort, bitsPerSecond, timeout=1)
    done = 0
  except:
    print "Failed to connect on " + devPort
    done = 1
  
  # data i/o
  portOut = ThreadClass()
  portOut.start()
  
  while not done:
    try:
      device.write(sys.stdin.readline())
    except:
      # programm end
      done = 1
      # thread close
      portOut.join()
      device.close()
      print ("Port is closed.")