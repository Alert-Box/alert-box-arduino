# alert_box_arduino
This is a device made from an arduino, whose goal is to provide an interface to interact with the user. 
It is made of an Arduino nano, connected via I2C to an LCD, and to 3 RGB adressable LEDs that can be programmed in any way.

Once assembled, the provided code can be uploaded on the arduino, and provide a box with which you can interact through simple serial commands.
Each command is composed of simple text, and will either print something on the screen or alter the state of the LEDs.

Behind the LED are 3 clicky pushbuttons, meaning that those LED indicators can also act as buttons. The buttons may be handled by the arduino
(code will be coming soon for this), but are currently handled by a Raspberry pi that sends commands to the Arduino according to a more
complex program than what the Arduino could handle.
