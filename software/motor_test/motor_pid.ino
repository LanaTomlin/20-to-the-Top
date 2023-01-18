//timer interrupts
//by Amanda Ghassaei
//June 2012
//https://www.instructables.com/id/Arduino-Timer-Interrupts/

//timer setup for timer0, timer1, and timer2.
//For arduino uno or any board with ATMEL 328/168.. diecimila, duemilanove, lilypad, nano, mini...

//this code will enable all three arduino timer interrupts.
//timer0 will interrupt at 2kHz
//timer1 will interrupt at 1Hz
//timer2 will interrupt at 8kHz

//storage variables


void pid_setup(){
  
cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
/*
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR1A = 156;// = (16*10^6) / (1000*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
*/


sei();//allow interrupts

}//end setup

ISR(TIMER0_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
  calc_pid();
}

  
void calc_pid()
{
  //UNITS OF TIME: 1MS

    double encoder = enc.read();
    enc.write(0);
    double new_pos = (encoder/64)*2*3.14*pulley_dia + old_pos; 
    double error = new_pos - set_dist;
    integral += error*0.001;
    if((integral*k > 245)|| (integral*k < -245))
      integral = integral/2.0;
    //derivitive = (prev_error - error)*100;
    SPEED = (k*(error + integral + derivitive));
    SPEED = constrain(SPEED, -245, 245);
    old_pos = new_pos;
    prev_error = error;
    motor.setSpeed(SPEED);
   
    if(abs(old_pos - set_dist) > 100){
      motor.setSpeed(SPEED);
    }
    else
    {
      motor.setSpeed(0);
      integral = integral/2.0;
    }
  } 
