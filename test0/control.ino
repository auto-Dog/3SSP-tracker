
// beta版太阳能controller，仅限10月25日附近使用
// 实验地理坐标：北纬31°5′(31.08)，东经121°25′(121.42)
/*  port info:
 *  (delete)D4 D5 D12 rtc model DAT CLK RST
 *  D12 for relay
 * 	D6 D7 motor1 output label
 *  D8 D9 motor2 output label
 *  A2 A3 A4 A5 light sensor lt lb rt rb
 *  RX TX connect to computer
 *  D2 D3 motor1 2 interrupt
 *  D10 "switch" only to disable control, while system still runs in loop
 * 
 */
#include "control.h"
#include <MsTimer2.h>
bool err0 = 0;                       //record the mistake

// ThreeWire clkIO(4,5,12);               //DS1302 model DAT-CLK-RST
// RtcDS1302<ThreeWire> Rtc(clkIO);
// RtcDateTime earlier;
motorMove myMotor;


int six_minutes = 0;
/*------------------------------------------------------*/
int mannulmonth = 10;
int mannulday = 25;
double timefactor = 0.267;
/*------------------------------------------------------*/
bool pwrswitch = 0;  //choose power input from group 1/2
// void isr0();
// void isr1();
bool time_trigger(unsigned long);
void pwrchange(){
  pwrswitch=!pwrswitch;
  digitalWrite(12,pwrswitch);//this switch reverse per minute
}
unsigned long privt = 0;

void setup(){
  
  Serial.begin(9600);
  // Rtc.Begin();
  // if (Rtc.GetIsWriteProtected()){
  //   Rtc.SetIsWriteProtected(false);
  // }
  // if (!Rtc.GetIsRunning()){
  //     Rtc.SetIsRunning(true);
  // }
  digitalWrite(13,1);
  MsTimer2::set(60000,pwrchange);
  MsTimer2::start();
  initTracking();
  /*while(!err0){
	  digitalWrite(13,1);
    //initialization Static length of support 1&2 should be given.
    //Also it can set current time
    err0 = initTracking();
    if(!err0)
    Serial.println('error!');  
  }*/

  digitalWrite(13,0);
}


void loop(){
  bool tmp01 = 0,	  //assert the weather, 1 for sunny
	runnow = 0;  //whether start the servo or not (run every 10 mins)
  //realTimeDebug();
  double delta = 0.0,tau = 0.0,heightAngle=0.0,dirAngle=0.0;
  if (six_minutes<=8*10){    //runs before 16:00
    if(time_trigger(360000)||six_minutes==0){
      //solar angles caclulation δ φ τ,CAUTION:these results in DEGREE
      delta = 23.45*sin(2*3.1415*(284+(mannulmonth-1)*30.5+mannulday)/365); //consider there are 30.5 days in a month
      tau = (8.0-(120-121.42)*0.067+timefactor+six_minutes*0.1-12.0)*15.0;	//start from 8:00 in GMT+8, plus correcting factor
      //should be updated if use worldwide
      heightAngle = asin(sin(0.5431)*sin(delta/180*3.14159) + cos(0.5431)*cos(delta/180*3.14159)*cos(tau/180*3.14159))/3.14159*180.0;
      //dirAngle = acos((sin(heightAngle/180*3.14159)*sin(0.5431)-sin(delta))/(cos(heightAngle/180*3.14159)*cos(0.5431)))/3.14159*180.0;
      dirAngle = asin(cos(delta/180*3.14159)*sin(tau/180*3.14159)/cos(heightAngle/180*3.14159))/3.14159*180.0;
      myMotor.movetodir(dirAngle,heightAngle);
      
      six_minutes+=1;
      Serial.print("Current time:");Serial.print(8.0+six_minutes*0.1);Serial.print("\n");
    }
  }
  
}

bool time_trigger(unsigned long trig_label){
  if((unsigned long)(millis()-privt)>=trig_label){	//ATTENTION! Always indicate the ulong type when calculating or definiting
    privt = millis();
    return 1;
  }
  else
    return 0;
}

/*
void isr0(){
  myMotor.counter1++;
  delay(2);
}

void isr1(){
  myMotor.counter2++;
  delay(2);
}
*/
