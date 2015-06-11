# -*- coding: utf-8 -*-
"""
Created on Sat May 02 16:09:30 2015

@author: pietro
"""
import serial
import numpy as np
import matplotlib.pyplot as plt
plt.close("all")

output_file_name='res.dat'
val_max = 60 # define maximum number of aquision lines
com_port='COM9' # define COM port
baud_rate=9600 # define baud rate speed (same as Arduino board)

ser = serial.Serial(com_port, baud_rate, timeout=40) # define COM Port
i=0

volt_array =  np.array([])
#temperature_array = np.array([])
temperature_array = np.array([])
time_array =  np.array([])

text_file = open (output_file_name, 'w') # create dat file

while i < val_max:
        line = ser.readline()
        voltage, temperature, time = line.split('*')

        #np.concatenate((volt_array,float(voltage)),axis=0)        
        volt_array=np.append(volt_array, [float(voltage)])
        temperature_array = np.append(temperature_array,[float(temperature)])
        time_array = np.append(time_array,[float(time)])
        
        # write in res.dat
        text_file.write(voltage + ' ')
        text_file.write(temperature + ' ')
        text_file.write(time)
        
        i = i + 1
        print voltage, temperature, time
print volt_array
print time_array
ser.close() # close COM port
text_file.close() # close file

plt.figure()
plt.plot(time_array, volt_array, linewidth=2.0)
plt.plot(time_array, volt_array,'ro')
plt.xlabel('Time (s)')
plt.ylabel('Voltage (V)')
plt.grid()
plt.show()
