#include "init_tracking.h"
#define betaDegree 30.1
double iniheight1,iniheight2;
//从电脑端输入 若输入N，代表默认两根杆高为0，时间不做调整
//若仅要更改高度，输入H&高度值一&高度值二 
//若要更改高度和时间 输入D&高度值一&高度值2-YYYY-MM-DD-HH-MM-SS-(weekday Sun1-7Sat)
//示例：D&120.00&120.00-2021-03-09-18:42:00
void inputinfo(){ 
  char tmp = ' ';
  char charCache[40] = " ";
  int charCount = 0;
  int yyyy = 0, mo = 0, dd = 0, hh = 0,mm = 0,ss = 0;
  //while(!Serial.available());	//stop here when no message received
  //tmp = Serial.read();
 /*

      yyyy = 2021;
      mo = 4;
      dd = 6;
      hh = 9;
      mm = 30;
      ss = 0;
      RtcDateTime dt(yyyy,mo,dd,hh,mm,ss);
      Rtc.SetDateTime(dt);
	//for debug

    Serial.print("Date: "); 
    Serial.print(yyyy); Serial.print('-');Serial.print(mo);Serial.print('-');Serial.print(dd);Serial.print(',');
    Serial.print(hh);Serial.print(":");Serial.print(mm);Serial.print(":");Serial.print(ss);

	  //Serial.println(yyyy ' ' mo ' ' dd ' ' hh ' ' mm ' ' ss);
    */
  }


bool initTracking(){
	bool err = 0;
  //double iniheight1=400.0,iniheight2=400.0;
	pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(2,INPUT);
  pinMode(3,INPUT);
	pinMode(10,INPUT_PULLUP);
  //make sure the motors stop
  digitalWrite(6,0);
	digitalWrite(7,0);
  digitalWrite(8,0);
	digitalWrite(9,0);
	//inputinfo();
	err = 1;//myMotor.motorSetup(iniheight1,iniheight2);       //coonect the motor and check
  /*
	double timeval = 0;
	double tau1 = 0,deltaDegree = 0;	//tau for time angle, deltaDegree for sun height angle
	tau1 = -15.0*(12.0-timeval);
	deltaDegree = tau1-tau;
	tau = tau1;
	motor0.motorMove(deltaDegree,1);
	motor0.runNow();
  
  if(!err)
    Serial.println("Initialize failed. Trying again.");
  else
    Serial.println("Initialize successfully.");
*/
  return err;
}
