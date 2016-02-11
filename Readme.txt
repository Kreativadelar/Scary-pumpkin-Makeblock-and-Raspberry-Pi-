See video here: https://youtu.be/c8q74OZ3534

Instructions (Not done):

Installation on Raspberry Pi

Copy the Python folder to the home folder of pi user on the Raspberry Pi. You need to run the code in the Desktop due to that pyGame need to create a window to be able to play sounds.

If you want the script to automatically start when booting up do as follows:
•	Change in raspi-config so the Raspberry Pi boots to desktop automatic 
•	Create a folder named lxsession under ~/.config/
•	Create a folder named LXDE under ~/.config/lxsession (For newer versions you need to name it to LXDE-pi)
•	Create a file named autostart under ~/.config/lxsession/LXDE/ (~/.config/lxsession/LXDE-pi/)
•	Add the row below to the autostart file:

@bin/Python ….

When you now reboot the Pi it will start the script as soon the Pi has booted in to the desktop. (Be sure to have the Arduino attached to the pi otherwise the script will stop due to there are now error handling for the serial port implemented in the script. 

FAQ
The script can’t open port /dev/ttyACM0
Remove the USB cabel from Pi and reconnect it and run the following command 
Then you should see something similar down below:

Change in the Python script to what you find in the above printout.
