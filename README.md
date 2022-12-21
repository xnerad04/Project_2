# Project - Servo motors
Application of joy-stick and two servo motors. 

Our application consists of two servo motors and joy-stick. Joy-stick determines, which direction motors are rotating. When pushing to the left side in direction of x-axis, servo is rotating counter-clockwise, when pushing to the right, servo is rotating clockwise. By pushing the joy-stick button, you can change which of the two servo motors is controlled. 

### Team members

* Adam Neradilek
* Ondřej Nesvadba

## Hardware description
### Servo motors
![2567_plastove-micro-servo-sg90-9g--kontinualni](https://user-images.githubusercontent.com/99417291/208713518-54b4f144-c576-4ae3-a44d-02fd31184724.jpg)

* brown PIN: ground (GND)
* red PIN: power supply (5V)
* orange/yellow PIN: PWM signal

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
As described above, application controls two servo motors by pushing joy-stick to the left, right, or pushing the joy-stick button. By pushing the button, you can change, which servo is controlled. Then by pushing in the direction of x-axis to the left or right, you control, if servo is rotating clockwise or counter-clockwise. 

#### TIMER0_OVF_vect Flowchart
![TIMER0_OVF_vect](https://github.com/xnerad04/Project_2/blob/main/Flowchart%20TIMER0_OVF_vect.JPG)

#### ADC_vect Flowchart
![ADC_vect](https://github.com/xnerad04/Project_2/blob/main/Flowchart%20ADC_vect.JPG)

### Project Structure
---------------------------------------------------------------
PROJECT_2       
- include        
  - [timer.h](https://github.com/xnerad04/Project_2/blob/main/project-02/include/timer.h)

- lib             
  - gpio
    - [gpio.c](https://github.com/xnerad04/Project_2/blob/main/project-02/lib/gpio/gpio.c)
    - [gpio.h](https://github.com/xnerad04/Project_2/blob/main/project-02/lib/gpio/gpio.h)

- src           
  - [main.c](https://github.com/xnerad04/Project_2/blob/main/project-02/src/main.c)
- README.md       
---------------------------------------------------------------

## Simulation
![Simulation in SimulIde](https://github.com/xnerad04/Project_2/blob/main/Simulation.gif)

## References
1. https://www.electronics-lab.com/project/using-sg90-servo-motor-arduino/
2. https://github.com/arduino-libraries/Servo
