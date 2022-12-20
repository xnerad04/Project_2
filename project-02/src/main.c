/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions

#define servo1 PB1          // Servo 1 pin
#define servo2 PB2          // Servo 2 pin
#define BTN PD2             // Button on joystick

#define MIN_POS 950         // Min position of servo
#define MAX_POS 2050        // Max position of servo
#define STEP 10             // Step for the servos

uint8_t last_btn;           // Last state of button
uint8_t curr_btn;           // Current state of button
int8_t state = 0;           // Button state

uint32_t servo1_pos = MIN_POS;    // Start Servo 1 in min position 
uint32_t servo2_pos = MAX_POS;    // Start Servo 2 in max position 

int main(void)
{
  // Button pin
  GPIO_mode_input_pullup(&DDRD, BTN);

  // Servo pins
  GPIO_mode_output(&DDRB, servo1);
  GPIO_mode_output(&DDRB, servo2);

  // Configure Analog-to-Digital Convertion unit
  // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
  ADMUX = ADMUX | (1<<REFS0);
  // Select input channel ADC0 (voltage divider pin)
  ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
  // Enable ADC module
  ADCSRA = ADCSRA | (1<<ADEN);
  // Enable conversion complete interrupt
  ADCSRA = ADCSRA | (1<<ADIE);
  // Set clock prescaler to 128
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

  // Configuration of 8-bit Timer/Counter0 for Timer update
  // Set the overflow prescaler to 16 ms and enable interrupt    
  TIM0_overflow_16ms();
  TIM0_overflow_interrupt_enable();
  
  // Waveform Generation Mode 8 (1000)
  TCCR1B |= (1<<WGM13);

  // Set compare output mode
  TCCR1A |= (1<<COM0A1) | (1<<COM0B1);

  // Set TOP value 
  ICR1 = 20000;

  OCR1A = servo1_pos;
  OCR1B = servo2_pos;

  TCCR1B |= (1<<CS11);      // Set prescaler to 8

  PCICR |= (1<<PCIE0);      // Any change of any enable PCINT[7:0] pins will cause an interrupt
  PCMSK0 |= (1<<PCINT0);    // Enable PCINT0 change interrupt  
  
  // Enables interrupts by setting the global interrupt mask
  sei();

  // Infinite loop
  while (1)
  {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
  }

  // Will never reach this
  return 0;
}



ISR(TIMER0_OVF_vect)
{
  // Start ADC conversion
  ADCSRA |= (1<<ADSC);

  // Read button
  curr_btn = GPIO_read(&PIND, BTN);

  // If button gets pressed, switch 'state' from 0 to 1 or from 1 to 0 (switch between servos)
  if(curr_btn != last_btn)
  {
    if(GPIO_read(&PIND, BTN) == curr_btn && curr_btn == 1)
    {
      if(state == 0)
      {
        state = 1;
      }
      else
      {
        state = 0;
      }
    }
  }
  last_btn = curr_btn;
}



ISR(ADC_vect)
{
  uint16_t value = 0;   // value for ADC
  value = ADC;          // ADC --> 'value'

  if(value >= 700)  // Joystick pushed to the "right"
  {
    if(state == 0)  // Using 'state' to determine which servo is moved
    {
      servo1_pos += STEP;
    }
    else
    {
      servo2_pos += STEP;
    }
  }

  else if(value <= 300) // Joystick pushed to the "left"
  {
    if(state == 0)  // Using 'state' to determine which servo is moved
    {
      servo1_pos -= STEP;
    }
    else
    {
      servo2_pos -= STEP;
    }
  }

  else  // Joystick is in the middle
  {}    // Nothing changes


  // Limits for servos
  if(servo1_pos < MIN_POS)
  {
    servo1_pos = MIN_POS;
  }

  if(servo2_pos < MIN_POS)
  {
    servo2_pos = MIN_POS;
  }

  if(servo1_pos > MAX_POS)
  {
    servo1_pos = MAX_POS;
  }

  if(servo2_pos > MAX_POS)
  {
    servo2_pos = MAX_POS;
  }



  // Servo position values send to registers
  OCR1A = servo1_pos;
  OCR1B = servo2_pos;
}