#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__
#include <Arduino.h>
#include <math.h>
//#include "control.h"

  //control the motor
	class motorMove{
		public:
			motorMove();
			void movetoflat(double);				//go to 400mm height
			void movetodir(double,double);	//for initial tracking, input obj alpha,obj beta. take degree as unit
			void changedir(double,double);	//for passive tracking, input +-alpha, +-beta. take degree as unit			
			bool changeheight(double,double);	//control the support directly
			int counter1,counter2;
			double height1;
			double height2;
			bool motorSetup(double,double);	//input current height of colum 1 and 2
      bool mydelay(unsigned long);    //for multithreading timer


		private:
			double currentAlpha;
			double currentBeta;
			int current1;
			int current2;
			int current3;
			
			//bool debug(int ohm);		//print the current on the screen,  the register should be up-pulled to 5V source
	};
	
#endif
//void runNStep(int speed=5,int steps);
