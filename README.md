# Project - Servo motors
Application of joy-stick and two servo motors. 

Our application consists of two servo motors and joy-stick. Joy-stick determines, which direction motors are rotating. 

### Team members

* Adam Neradilek
* Ondřej Nesvadba

## Hardware description
### Servo motors


### Joystick HW-504
![HW-504](https://user-images.githubusercontent.com/99417291/205458618-b3d640bc-a72d-437f-a9a0-8da89a7361f3.png)

* Pin GND: ground
* Pin +5: power supply 5 V
* Pin Vrx: information about x-axis position 
* Pin Vry: information about y-axis position
* Pin SW: transmission of information

### Connection in SimulIde
![image](https://user-images.githubusercontent.com/99417291/208712092-fbd5b50d-67e6-4db2-9d2d-8608bf3d7f97.png)

### Final connection
![IMG_20221213_132029](https://user-images.githubusercontent.com/99417291/208711538-e73572ae-ff3c-47cb-8178-8e8e60578788.jpg)

## Software description

### Project Structure
---------------------------------------------------------------
PROJECT_2       
- include        
  - [timer.h](...)

- lib             
  - gpio
    - [gpio.c](...)
    - [gpio.h](...)
  - uart
    - [uart.c](...)
    - [uart.h](...)
  - adc
    - [adc.c](...)
    - [adc.h](...)

- src           
  - [main.c](...)
- README.md       
---------------------------------------------------------------

## Video


## References
1. https://www.electronics-lab.com/project/using-sg90-servo-motor-arduino/
2. https://github.com/arduino-libraries/Servo
