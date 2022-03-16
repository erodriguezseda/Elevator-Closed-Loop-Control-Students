/*************************************************************************************
Program Name: 
Description: 
Author: 
Date: 
**************************************************************************************/
/************************** Pseudo code*******************************
    Include required libraries
    Declare serial object to PC, Motor object to DC motor pins, Encoder Object
    Declare variables for duty cycle, error, desired height, etc. 
    Define coefficients of polynomial fit for counts-to-height
    Define other control parameters such as Kp, Ki, Kd, etc. 

    Set Serial Connection to PC to desired baudrate

    While(true)  //indefinite while loop
        Ask User for Control type
        Ask User for desired height of elevator
        Ask User for duration of experiment
        Ask User for frequency of the control experiment

        While (time <= Duration of experiment)  //Enter Control Loop
            Read Encoder
            Convert from Counts to Measured Height
            Compute Error = Desired Height - Measured Height 
            If Logic Control 
                If Error > 0
                    Set duty cycle to Forward Motion
                Else-If Error < 0
                    Set duty cycle to Reverse Motion
                Else
                    Set duty cycle to Hold Position
                End-If
            Else If P-Control
                Duty cyle = Kp*Error + HoldValue
            Else If PI-Control
                Compute Integral of Error Signal
                Duty cycle = Kp*Error + Ki*IntegralError + HoldValue  
            Else If PID-Control
                Compute Integral of Error Signal
                Compute Derivate of Error Signal
                Duty cycle = Kp*Error + Ki*IntegralError + Kd*DerivativeError + HoldValue                 
            End-If
            Truncate duty cycle if exceeds -1 to 1 range
            Set Motor speed using duty cycle

            Regulate frequency of control law execution
        End-While
    End-While
**********************************************************************/
//------------- START PROGRAM
/************** Libraries ******************************************/
#include "mbed.h"                   //Include mbed library
#include "Motor.h"                  //Include Motor.h Library by Simon Ford (see ICE 02)
#include "QEI.h"                    //Include QEI.h Library 
#include "platform/mbed_thread.h"   //Include timing functions library

/************** Declare Objects ******************************************/ 
//[Insert] Declare Serial object for PC communication
//[Insert] Declare QEI object for encoder, use correct pins #
//[Insert] Declare Motor object for actuator, use correct pins #
PwmOut dummyPwm(p23);		//[DO NOT MODIFY] Dummy variable used to set the PWM period of all signals
				//[IMPORTANT] It is important that you declare the dummyPwm variable after you
				//you have declared the motor, not before. 

/************** Declare and Initialize Variables and Parameters ************/
//[Insert] For example: Define and initialize the coefficients of your polynomial fit, measurements, 
//[Insert] Define duty cycle variable to be sent to the motor, error variables, etc...
//[Insert] Define control parameters, Pwm value to hold the elevator in place, Kp, Ki, etc.... 

/************** Time variables to regulate execution of code **************/
Timer t;                    	//[DO NOT MODIFY] Timer to regulate control sequence 
Timer tlog;                 	//[DO NOT MODIFY] Timer to log data 
float dt;			//[DO NOT MODIFY] Variable to measure time window left in program 
float Fs = 20.0;            	//[TO BE MODIFIED by USER using TERA TERM] Sampling Frequency (default of 20 Hz) 
								
int main()
{
    //[INSERT] Set serial communication baud rate to PC to 115200
		
    while(1) {					//[DO NOT MODIFY WHILE LINE] Indefinite while loop 
	dummyPwm.period(0.00005);		//[DO NOT MODIFY] This sets the period of all PWM signals to 0.00005 sec

    //[INSERT] Set motor speed to zero. Always set the motor speed to zero before starting an experiment
	//[INSERT] Use the commands of your choice (printf, putc, scanf, getc, any other) to give/ask instructions to user
	//[INSERT] Obtain and save parameters enter by user: desired height (as a float), sampling frequency (as a float named Fs)
	// and duration of experiment (as a float)
		
        thread_sleep_for(500); 		//Small wait... to give you some time
        t.start(); 		//[DO NOT MODIFY] Start Timer that regulate control sequence
        tlog.start();		//[DO NOT MODIFY] Start Timer that you will use to log time data
	
	    //[INSERT: Needed for PI and PID Controllers ONLY] Set Integral of Error to Zero before entering the experiment/run - this is only needed for PI control
		
        while(tlog.read() <= DURATION of Experiment) {  //[INSERT] Entering Control Loop: Modify condition in while loop  
							//While loop must execute as long as specified by user
            
		//[INSERT] Here you should read the encoder
		//[INSERT] Using your calibration equation, convert encoder counts to height
		//[INSERT] Compute error = desired height - measured height
			
		//[INSERT: Needed for PI Controller ONLY] Compute/Update Integral of Error

		//[INSERT: FOR LOGIC CONTROLLER]   Compute Duty Cycle for motor speed using Logic Control Algorithm (a series of if-else statements)
		//[INSERT: FOR P-Controller]       Compute Duty Cycle for motor speed using Proportional (P) Control Algorithm 
		//[INSERT: FOR PI-Controller]      Compute Duty Cycle for motor speed using Proportional-Integral (PI) Control Algorithm 
        //[INSERT: FOR PID-Controller]     Compute Duty Cycle for motor speed using Proportional-Integral-Derivative (PID) Control Algorithm 
		//[INSERT] For P, PI, and PID controllers, make sure duty cycle does not exceed 1 and -1. Use if statements to truncate the dc signal to 1 or -1
			
		//[INSERT] Set speed of motor with duty cycle computed
        //[INSERT] Print to Tera Term data: time (using tlog.read()), measured height, error height, and duty cycle (all of them should be floats)

		//[DO NOT MODIFY the following lines of code] This code makes sure the control sequence is executed every "1/Fs" seconds
		float Ts = 1/Fs;		//[DO NOT MODIFY] Ts is the control period, inverse of control sampling frequency
            	dt = Ts-t.read();  		//[DO NOT MODIFY]
            	t.stop();			    //[DO NOT MODIFY]
            	t.reset();			    //[DO NOT MODIFY]
            	if (dt >= 0) {			//[DO NOT MODIFY]
                	thread_sleep_for(1000*dt);		//[DO NOT MODIFY]
            	}  				        //[DO NOT MODIFY]
            	t.start();			    //[DO NOT MODIFY]
        }				//[DO NOT MODIFY] End of Control While Loop
	t.stop(); 			//[DO NOT MODIFY] 
        t.reset();			//[DO NOT MODIFY]
        tlog.stop();			//[DO NOT MODIFY] Stop and reset timer used when logging data
        tlog.reset();			//[DO NOT MODIFY]
		
        //[INSERT] Set speed of motor to zero
    }	//End of indefinite while loop
}		//End of main function