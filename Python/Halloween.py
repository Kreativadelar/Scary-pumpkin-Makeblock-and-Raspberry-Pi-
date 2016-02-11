'''
**   _   __               _   _                _      _            
**  | | / /              | | (_)              | |    | |           
**  | |/ / _ __ ___  __ _| |_ ___   ____ _  __| | ___| | __ _ _ __ 
**  |    \| '__/ _ \/ _` | __| \ \ / / _` |/ _` |/ _ \ |/ _` | '__|
**  | |\  \ | |  __/ (_| | |_| |\ V / (_| | (_| |  __/ | (_| | |   
**  \_| \_/_|  \___|\__,_|\__|_| \_/ \__,_|\__,_|\___|_|\__,_|_|   
**                                                                 
**
**  Scary pumpkin using Makeblock modules
**  from Kreativadelar.se, Sweden
**
**  This code is written "quick & dirty" and should not be as a guide
**  in how to program Python. Feel free to change code as you like
**  and share with your friends.
**
**  If you want to share your code changes, please e-mail them to
**  info@kreativadelar.se and we will put them on our web for other
**  customers to download.
**
**  (C) Kreativadelar.se 2015, Sweden, Patrik
**  http://www.kreativadelar.se
**
**  To use this code you need the following libraries: 
**  
**  pyGame 
**  pySerial
**
**  Version 1.0, Initial public release, July 2015
**
**  This example code is in the public domain.
**
'''

import serial
import time
import struct
import codecs
import pygame

def serial_read():
    # read response from serial port
    if serial_port.isOpen():
        for c in serial_port.read():
            if c == '\r':
                serial_read.line = serial_read.buffer
                serial_read.buffer = ""
                serial_read.newLine = True
                break
            else:
                if c != '\n':
                    serial_read.buffer = serial_read.buffer + c
    else:
        print("Port is not open!!");

    
def serial_write(value=float):
	_b = struct.pack('f', value)

	serial_port.write("1".encode())
	serial_port.write(":".encode())
	serial_port.write(_b)
	
def checkForNewAruinoCommand():
    # get the last line from serial port
   serial_read()  
   if serial_read.newLine:
       print("Arduino -> " + serial_read.line)
       serial_read.newLine = False 
       if serial_read.line == '0': 
           print("Pi -> Arduino state changed to: 0")
           return 0
       elif serial_read.line == '1':
           print("Pi -> Arduino state changed to: 1")
           return 1
       elif serial_read.line == '2':
           print("Pi -> Arduino state changed to: 2")
           return 2
       elif serial_read.line == '4':
           print("Pi -> Arduino state changed to: 3")
           return 4

# open serial port
try:
    serial_port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=1)
except serial.SerialException as e:
   print("could not open serial port '{}': {}".format("/dev/ttyACM0", e))


pygame.init()
Channel1End = pygame.USEREVENT + 1
Channel2End = pygame.USEREVENT + 2
Channel1 = pygame.mixer.Channel(2)
Channel1.set_endevent(Channel1End)
Channel2 = pygame.mixer.Channel(3)
Channel2.set_endevent(Channel2End)
scareSound = pygame.mixer.Sound("content/Scary_Scream-SoundBible.ogg");
laughSound = pygame.mixer.Sound("content/Evil_Laughs-Mike_Koenig-933903605.ogg");
pygame.display.set_mode((200,100))
pygame.mixer.music.load("content/Spooky Chains-SoundBible.com-969772338.mp3")

serial_read.buffer = "";
serial_read.line = "";
serial_read.newLine = False

currentStat = -1
currentArduinoState = -1

while True:	
   
   # Check for new command from Arduino
   currentArduinoState = checkForNewAruinoCommand();


   if currentArduinoState == 0:
       # Reset
       currentArduinoState = -1
       if currentStat != 0:
           print("Pi -> Reseting")
           pygame.mixer.music.stop()
           pygame.event.clear()
           serial_write(0)
           print("Pi -> Sent state 0")
           currentStat = 0
           
   elif currentArduinoState == 1:
       # Start Music
       if currentStat != 1:
           print("Pi -> Start Music")
           pygame.mixer.music.play()
           serial_write(1)
           print("Pi -> Sent state 1")
           currentStat = 1
           
   elif currentArduinoState == 2:
       # Start scare sound
       if currentStat != 2:
           print("Pi -> Start scare sound")
           serial_write(3)
           scareSound = pygame.mixer.Sound("content/Scary_Scream-SoundBible.ogg");
           Channel1.set_endevent(Channel1End)
           Channel1.play(scareSound)
           print("Pi -> Sent state 3")
           currentStat = 2   

   elif currentArduinoState == 4 and currentStat==3:
       # Start laugh sound
       if currentStat != 4:
           print("Pi -> Start laugh sound")
           laughSound = pygame.mixer.Sound("content/Evil_Laughs-Mike_Koenig-933903605.ogg");
           Channel2.set_endevent(Channel2End)
           Channel2.play(laughSound)
           currentStat = 4
      
   for event in pygame.event.get():
        if event.type == Channel1End:
            # Send state 4 when sound done
            print("Pi -> Scare sound done")
            serial_write(4)
            currentStat = 3
        elif event.type == Channel2End:
            # Send state when sound done
            # Turn off music
            print("Pi -> Laugh sound done")
            serial_write(5)
            print("Pi -> Sent state 5")
            pygame.mixer.music.fadeout(1000)
            pygame.event.clear()

            
#close the serial port
serial_port.close()   