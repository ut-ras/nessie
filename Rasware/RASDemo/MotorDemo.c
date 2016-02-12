#include "RASDemo.h"

#include <RASLib/inc/common.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/pwm.h>


static tBoolean initialized = false;
static tPWM *LeftPWM; 
static tPWM *RightPWM;

void initMotors(void) 
	{
    if (!initialized) 
		{
      initialized = true; 
			LeftPWM= InitializePWM(PIN_B6,40000);
			RightPWM= InitializePWM(PIN_B7,40000);	
			SetPWM(LeftPWM, 0, 0);
		  SetPWM(RightPWM, 0, 0);	
    }
}


void motorDemo(void) {
    float left = 0, right = 0, speed = 0.75f, accel = 0.01f;
    char ch;    
    int i;

    Printf("Press:\n"
	   "  w-forward\n"
	   "  s-backward\n"
	   "  a-left\n"
	   "  d-right\n"    
           "  i-slowly forward\n"
	   "  k-slowly backward\n"
	   "  j-slowly left\n"
	   "  l-slowly right\n"    
           "  space-stop\n"
	   "  enter-quit\n");
  
    // wait for the user to enter a character
    ch = ' ';
    
    while (ch != '\n') {
        switch (ch) {
            case 'w':
                left = speed;
                right = speed;
                break;
            case 's':
                left = -speed;
                right = -speed;
                break;
            case 'a':
                left = -speed;
                right = speed;
                break;
            case 'd':
                left = speed;
                right = -speed;
                break;
            case 'i':
                right += accel;
                left += accel;
                break;
            case 'k':
                right -= accel;
                left -= accel;
                break;
            case 'j':
                right -= accel;
                left += accel;
                break;
            case 'l':
                right += accel;
                left -= accel;
                break;
            default:
                left = 0; 
                right = 0;
                break;
        }
				
					SetPWM(LeftPWM, left, 1);
					SetPWM(RightPWM, right, 1);
      
    } 
   
    // make sure the motors are off before exiting the demo 
					SetPWM(LeftPWM, 0, 0);
					SetPWM(RightPWM, 0, 0);
      
    Printf("\n");
}
