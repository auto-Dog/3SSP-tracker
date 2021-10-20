#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__
	//控制直流电机运动，通过编码器波形来检测运动
	//#define unsigned int uint
#include <Arduino.h>
#include <math.h>
//#include "control.h"

	class motorMove{
		public:
			motorMove();
			void movetoflat(double);				//go to 400mm height
			void movetodir(double,double);	//for initial tracking, input obj alpha,obj beta. take degree as unit
			void changedir(double,double);	//for passive tracking, input +-alpha, +-beta. take degree as unit			
			bool changeheight(double,double);	//control the support directly
			int counter1,counter2;
			//int counter;
			double height1;
			double height2;
			bool motorSetup(double,double);	//input current height of colum 1 and 2

		private:
			double currentAlpha;
			double currentBeta;
			int current1;
			int current2;
			int current3;
			
	};
  void isr0();
void isr1();
	
#endif
