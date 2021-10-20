//  太阳能controller ver1.1
//  features:
//  1. 尝试采用分时中断计数
//  2. 更改DS1302时钟程序，尝试修复不能设定时间和不能走时的问题
//  3. 

/*  port info:
 *  D4 D5 D12 rtc model DAT CLK RST
 * 	D6 D7 motor1 output label
 *  D8 D9 motor2 output label
 *  A2 A3 A4 A5 light sensor lt lb rt rb
 *  A0 A1 motor position read
 *  RX TX connect to computer
 *  D2 D3 motor1 2 interrupt
 *  D10 "switch" only to disable control, while system still runs in loop
 * 
 */
#include "control.h"
bool err0 = 0;                       //record the mistake

ThreeWire clkIO(4,5,12);               //DS1302 model DAT-CLK-RST
RtcDS1302<ThreeWire> Rtc(clkIO);
motorMove myMotor;
RtcDateTime earlier;

void isr0();
void isr1();
void setup(){
  Serial.begin(9600);
  Rtc.Begin();
  if (Rtc.GetIsWriteProtected()){
    Rtc.SetIsWriteProtected(false);
  }
  if (!Rtc.GetIsRunning()){
    Rtc.SetIsRunning(true);
  }

  while(!err0){
	  digitalWrite(13,1);
    //initialization Static length of support 1&2 should be given.
    //Also it can set current time
    err0 = initTracking();  
  }
  digitalWrite(13,0);
}


void loop(){
  bool tmp01 = 0,	  //assert the weather, 1 for sunny
	runnow = 0;  //whether start the servo or not (run every 10 mins)
  //bool switchon = digitalRead(10);
//for debug
  realTimeDebug();delay(2000);

    tmp01 = weatherAssert();
    runnow = timeAssert();
    if(runnow){
      //if(tmp01)
        //passiveTracking();
      //if(!tmp01)
        activeTracking();
    }
}

void isr0(){
  myMotor.counter1++;
  Serial.print("counter 1:");
  Serial.println(myMotor.counter1);
}

void isr1(){
  myMotor.counter2++;
  Serial.print("counter 2:");
  Serial.println(myMotor.counter2);
}
