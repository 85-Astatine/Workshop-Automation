# Workshop-Automation
![20230803_154615](https://github.com/RoboticsAayush/Workshop-Automation/assets/84365147/e4fa1150-09a0-46d0-af38-80b36dd8ee30)

My workshop utilizes an ESP32 and an Arduino Nano. Here are the features of the room:<br />
Here is the link to my Workshop Tour - [https://www.youtube.com/watch?v=yD-OuP3egbA&pp=ygUOYWF5dXNoIGJoc2FubGk%3D](https://youtu.be/yD-OuP3egbA)

->All the lights and fans can be controlled via speech or through the dedicated apps.<br />
->The air conditioner is automated, and the door can also be opened automatically (I'm looking into improving the system, possibly using hydraulics).<br />
->Several routines are set up using various devices like foot switches, table taps, and NFC stickers placed around the workshop (more details can be found in the workshop video).<br />
->There are two types of LEDs:<br />
    ->Active LEDs: There are 573 WB2812B LEDs arranged around the main frame. Each LED's color and brightness can be controlled individually.<br />
    ->Passive LEDs: There are 1800 12V RGB LED strips running along the perimeter of the room. These can be controlled using three MOSFETs for each color channel. To ensure temperature control, I've integrated temperature sensors with all the MOSFETs, and there's a fan in place with an automatic cutoff feature in case temperatures rise.<br /><br />

                    
The ESP32 handles the speech-to-text conversion from Alexa and transmits the desired commands to the Arduino Nano via UART. It also takes care of displaying information and reading various sensors and switches, including temperature and humidity sensors, foot switches, table tap switches, touch switches, etc.<br /><br />

The Arduino Nano receives the commands and is connected to most of the peripherals, enabling it to toggle relays and MOSFETs on and off. Additionally, the Nano controls the 573 individually programmable LEDs mounted across the entire frame. Simultaneously, the 15A MOSFETs manage all the passive 12V LED strips.







 
