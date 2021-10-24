//this program can control ONE motor at a time
/* link info:	
 * D6-IN1 D7-IN2
 * D8-IN3 D9-IN4
 * motor1 on western
 * motor2 on eastern
 */
#include "motor_ctrl.h"
#define vRatio 5.2			//ratio of travel steps:distance
#define DeteceterOhm 0.01
#define tauLimitL -0.8726  //rad,50°
#define tauLimitR 0.8726
#define betaLimit 0.7853
#define triangleR 300		//mm

motorMove::motorMove(){			
	counter1=0;
	counter2=0;
	currentAlpha = 0.0;
	currentBeta = 0.0;
	height1 = 600.0;
	height2 = 600.0;
	//height3=600 mannul
	current1 = 0;
	current2 = 0;
	current3 = 0;
}

bool motorMove::changeheight(double inputHeight1,double inputHeight2){	
	double i,j = 0.0;
	bool IN1 = 0,IN2 = 0,IN3 = 0,IN4 = 0;
	if(inputHeight1<50)	inputHeight1 = 50;
	if(inputHeight2<50)	inputHeight2 = 50;
/*//debug
  Serial.println("Current height: ");
  Serial.println(height1);
  Serial.println(height2);
  */
	Serial.println("Will move to: ");
	Serial.println(inputHeight1);
  Serial.println(inputHeight2);
	i = inputHeight1 - height1;
	j = inputHeight2 - height2;
	/***********待核实*************/
	if(i>=0){IN1 = 1;IN2 = 0;}
	else {IN1 = 0;IN2 = 1;i=-i;}

	if(j>=0){IN3 = 1;IN4 = 0;}
	else {IN3 = 0;IN4 = 1;j=-j;}
digitalWrite(13,1);     //indicate that motor is moving
	counter1 = 0;					//zerolize coder counter 
	//while(counter1<(i*vRatio)){
		digitalWrite(6,IN1);
		digitalWrite(7,IN2);
	//}
	  delay(i/5.3*1000.0);
		digitalWrite(6,0);
		digitalWrite(7,0);

	counter2 = 0;
 // while(counter2<(j*vRatio)){
		digitalWrite(8,IN3);
		digitalWrite(9,IN4);
  //}
	  delay(j/5.3*1000.0);
		digitalWrite(8,0);
		digitalWrite(9,0);
//debug
//Serial.println("DONE");
	height1 = inputHeight1;
	height2 = inputHeight2;
digitalWrite(13,0);
	if(counter1*counter2!=0)
		return 1;
	else
		return 0;
}

bool motorMove::motorSetup(double oriheight1,double oriheight2){		
	height1 = oriheight1;
	height2 = oriheight2;
	//changeheight(400,400);		//change the angle of the panel steadly to protect the structure
	//changeheight(200,200);
	
	digitalWrite(6,1);			//upward move
	digitalWrite(7,0);
  //Serial.println("Now upward 1");
	digitalWrite(8,1);
	digitalWrite(9,0);
  //Serial.println("Now upward 2");

	delay(90000);				//THIS VALUE CHANGE DUE TO THE FACT
	digitalWrite(6,0);
	digitalWrite(7,0);
	
	digitalWrite(8,0);
	digitalWrite(9,0);

	height1 = 800.0;
	height2 = 800.0;
	changeheight(400,400);
	changeheight(200,200);
	/*
	if(counter1*counter2!=0)
		return 1;
	else
		return 0;
   */
}

void motorMove:: movetoflat(double val){				//go to ?mm height
	if(val<5||val>790)	return;
	changeheight(val,val);
}
void motorMove:: movetodir(double tau,double heightAngle){  //for initial tracking, input obj alpha,obj beta in DEGREE
  double tmpheight1 = 0.0,tmpheight2 = 0.0;
  tau = tau/180.0*3.14159;
  heightAngle = heightAngle/180.0*3.14159;
  if(tau<tauLimitL) tau = tauLimitL;
  if(tau>tauLimitR) tau = tauLimitR;
  currentAlpha = tau;
  if(heightAngle>1.57)  heightAngle = 1.57;
  if(heightAngle<betaLimit) heightAngle = betaLimit;
  currentBeta = heightAngle;
  //height to solar angle converter by tcy
  tmpheight1 = -0.5*triangleR*(cos(currentBeta)/sin(currentBeta))*(3*abs(cos(currentAlpha))+1.732*sin(currentAlpha))+600;
  tmpheight2 = -0.5*triangleR*(cos(currentBeta)/sin(currentBeta))*(3*abs(cos(currentAlpha))-1.732*sin(currentAlpha))+600; 
  Serial.print("Move to height:");Serial.print(tmpheight1);Serial.print(tmpheight2);Serial.print("\n");
  changeheight(tmpheight1,tmpheight2);
}

void motorMove:: changedir(double alpha,double beta){ //for passive tracking, input +-alpha, +-beta     
  int newtau = currentAlpha + alpha;
  int newh = currentBeta + beta;
  movetodir(newtau,newh);
}
bool motorMove::mydelay(unsigned long motorWaitTime){
  unsigned tmp_time_label = millis();
  while(1){
    if((millis()-tmp_time_label)>=motorWaitTime)
      return 1;
  }
}
/*
motorMove::bool debug(int ohm){			//print the current on the screen,  the register should be up-pulled to 5V source
	//requires advance define of serial port and frequency, consider default port as 10 and default reading port as A5
	int j = 0;
	for(int i = 0;i<10;++i)
		j+=analogRead(A5);
	j/=10;
	println(j/1024*5*ohm);
	
}
*/
