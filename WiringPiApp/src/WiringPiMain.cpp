// SPDX-FileCopyrightText: 2000 Argonne National Laboratory
//
// SPDX-License-Identifier: EPICS

/* WiringPiMain.cpp */


#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "epicsExit.h"
#include "epicsThread.h"
#include "iocsh.h"

#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <wiringPi.h>

int main(int argc,char *argv[])
{
    wiringPiSetupGpio();
    int i;
    for(i=2;i<30;i++) {
        pinMode(i, OUTPUT);//INPUT, OUTPUT, PWM_OUTPUT
        pullUpDnControl(i, PUD_DOWN);
    }
    //Set all GPIO pin to output except 0 and 1
    //Based on some document, BCM0 and 1 are for SD Card and should be 
    //avoid to used.
    	
    if(argc>=2) {
        iocsh(argv[1]);
        epicsThreadSleep(.2);
    }
    iocsh(NULL);
    epicsExit(0);
    return(0);
}



extern "C" {
	void SetGPIO(int ChIndx,long val);
	void SetMode(int ChIndx,long val);
	long GetGPIO(int ChIndx);
	void SetGPIO(int ChIndx,long val)
	{
		if(ChIndx >=2 && ChIndx<32) {
			if(val!=0) {
				digitalWrite(ChIndx,1);
			}
			else {
				digitalWrite(ChIndx,0);
			}
		}
	}
	void SetMode(int ChIndx,long val)
	{
		if(ChIndx >=2 && ChIndx<32) {
			if(val!=0) {
				pinMode(ChIndx, OUTPUT);//INPUT, OUTPUT, PWM_OUTPUT
			}
			else {
				pinMode(ChIndx, INPUT);//INPUT, OUTPUT, PWM_OUTPUT
			}
		}
	}
	long GetGPIO(int ChIndx)
	{
		int rval;
		rval=0;
		if(ChIndx >= 0 && ChIndx<32) {
			rval = digitalRead(ChIndx);
		}
		return rval;        
	}
	

    
}
