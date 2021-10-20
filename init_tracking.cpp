#include "init_tracking.h"
#define betaDegree 30.1
double iniheight1,iniheight2;
//从电脑端输入 若输入N，代表默认两根杆高为0，时间不做调整
//若仅要更改高度，输入H&高度值一&高度值二 
//若要更改高度和时间 输入D&高度值一&高度值2-YYYY-MM-DD-HH-MM-SS-(weekday Sun1-7Sat)
//示例：D&120.00&120.00-2021-07-12-12:00:00
void inputinfo(){ 
  char tmp = ' ';
  char charCache[40] = " ";
  int charCount = 0;
  int yyyy = 0, mo = 0, dd = 0, hh = 0,mm = 0,ss = 0;
  while(!Serial.available());	//没有讯息传入时，停留此处
  tmp = Serial.read();
  switch(tmp){
    case 'N': break;

    case 'H': 
      while(charCount<14){
        if(Serial.available()){
          charCache[charCount] = Serial.read();
          charCount++;
        }
      }
      iniheight1 = (charCache[1]-48)*100.0+(charCache[2]-48)*10.0+(charCache[3]-48)*1.0+(charCache[5]-48)*0.1+(charCache[6]-48)*0.01;
      iniheight2 = (charCache[8]-48)*100.0+(charCache[9]-48)*10.0+(charCache[10]-48)*1.0+(charCache[12]-48)*0.1+(charCache[13]-48)*0.01;
	//for debug
	  Serial.println(iniheight1);
	  Serial.println(iniheight2);
    break;

    case 'D': 
    while(charCount<34){
        if(Serial.available()){
          charCache[charCount] = Serial.read();
          charCount++;
        }
      }
      iniheight1 = (charCache[1]-48)*100.0+(charCache[2]-48)*10.0+(charCache[3]-48)*1.0+(charCache[5]-48)*0.1+(charCache[6]-48)*0.01;
      iniheight2 = (charCache[8]-48)*100.0+(charCache[9]-48)*10.0+(charCache[10]-48)*1.0+(charCache[12]-48)*0.1+(charCache[13]-48)*0.01;
      yyyy = (charCache[15]-48)*1000+(charCache[16]-48)*100+(charCache[17]-48)*10+(charCache[18]-48);
      mo = (charCache[20]-48)*10+(charCache[21]-48);
      dd = (charCache[23]-48)*10+(charCache[24]-48);
      hh = (charCache[26]-48)*10+(charCache[27]-48);
      mm = (charCache[29]-48)*10+(charCache[30]-48);
      ss = (charCache[32]-48)*10+(charCache[33]-48);
      RtcDateTime dt(yyyy,mo,dd,hh,mm,ss);
      Rtc.SetDateTime(dt);
	//for debug
	  Serial.println(iniheight1);
	  Serial.println(iniheight2);
    Serial.print("Input Date: "); 
    Serial.print(yyyy); Serial.print('-');Serial.print(mo);Serial.print('-');Serial.print(dd);Serial.print(',');
    Serial.print(hh);Serial.print(":");Serial.print(mm);Serial.print(":");Serial.print(ss);

      break;
    default:break;
  }
}

bool initTracking(){
	bool err = 0;
  double iniheight1=0.0,iniheight2=0.0;
	pinMode(13,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(2,INPUT);
  pinMode(3,INPUT);
	pinMode(10,INPUT);
//no input info in formal version
	inputinfo();
	err = myMotor.motorSetup(iniheight1,iniheight2);       //coonect the motor and check
  /*
	double timeval = 0;
	double tau1 = 0,deltaDegree = 0;	//tau for time angle, deltaDegree for sun height angle
	tau1 = -15.0*(12.0-timeval);
	deltaDegree = tau1-tau;
	tau = tau1;
	motor0.motorMove(deltaDegree,1);
	motor0.runNow();
  */
  if(!err)
    Serial.println("Initialize failed. Trying again.");
  else
    Serial.println("Initialize successfully.");

  return err;
}
