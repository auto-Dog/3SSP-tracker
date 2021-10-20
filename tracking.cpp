#include "tracking.h"
#define timeGap 300
#define thresoldBrt 900
#define floatingB 50
#define phi 0.5414


/*
 * A2 A3 A4 A5 light sensor lt lb rt rb
 * the sensor looks like this
 * (lt)2 || 4(rt)
 * =============  ⊙ SOUTH 
 * (lb)3 || 5(rb)
 * 需要实际测量一下各种情况传感器数值
 * 仅适用于北回归线以北的北半球
*/
	bool timeAssert(){
        RtcDateTime now = Rtc.GetDateTime();
        if(now.Hour()>16||now.Hour()<8) return 0;
        if(now.TotalSeconds()-earlier.TotalSeconds()>=timeGap)  {
            earlier = now;
            return 1;
        }
        return 0;
    }

    bool weatherAssert(){
        int lt = 2;
        int lb = 3;
        int rt = 4;
        int rb = 5;

        int ltb = analogRead(lt); // top left
        int rtb = analogRead(rt); // top right
        int lbb = analogRead(lb); // down left
        int rbb = analogRead(rb); // down rigt
        int av = (ltb+rtb+lbb+rbb)/4;
        if(av>thresoldBrt) 
            return 1;
        else
            return 0;


    }

	void passiveTracking(){
        int lt = 2;
        int lb = 3;
        int rt = 4;
        int rb = 5;

        int ltb = analogRead(lt); // top left
        int rtb = analogRead(rt); // top right
        int lbb = analogRead(lb); // down left
        int rbb = analogRead(rb); // down rigt
        int avt = (ltb+rtb)/2;
        int avb = (lbb+rbb)/2;
        int avl = (ltb+lbb)/2;
        int avr = (rtb+rbb)/2;
        int dvert = avt - avb;
        int dhori = avl - avr;

        while(dhori>floatingB||dhori<(-floatingB)){
            if(dhori>0)
                myMotor.changedir(1,0);  //non-linear variance function: f(x) = 
            else
                myMotor.changedir(-1,0);
            
            ltb = analogRead(lt); // top left
            rtb = analogRead(rt); // top right
            lbb = analogRead(lb); // down left
            rbb = analogRead(rb); // down rigt
            // avt = (ltb+rtb)/2;
            // avb = (lbb+rbb)/2;
            avl = (ltb+lbb)/2;
            avr = (rtb+rbb)/2;
            // dvert = avt - avb;
            dhori = avl - avr;
        }
        while(dvert>floatingB||dvert<(-floatingB)){
            if(dhori>0)
                myMotor.changedir(0,1);  
            else
                myMotor.changedir(0,-1);
            ltb = analogRead(lt); // top left
            rtb = analogRead(rt); // top right
            lbb = analogRead(lb); // down left
            rbb = analogRead(rb); // down rigt
            avt = (ltb+rtb)/2;
            avb = (lbb+rbb)/2;
            //avl = (ltb+lbb)/2;
            //avr = (rtb+rbb)/2;
            dvert = avt - avb;
            //dhori = avl - avr;
        }
    }

	void activeTracking(){
        RtcDateTime now = Rtc.GetDateTime();
        //solar angles caclulation δ φ τ
        double delta = 23.45*sin(2*3.1415*(284+(now.Month()-1)*30.5+now.Day())/365); //consider there are 30.5 days in a month
        double tau = ((now.Hour()+now.Minute()/60.0)-12.0)*15.0;
        //should be updated if use worldwide
        double heightAngle = asin(sin(phi)*sin(delta/180*3.14159) + cos(phi)*cos(delta/180*3.14159)*cos(tau/180*3.14159))/3.14159*180.0;
		double dirAngle = asin(cos(delta/180*3.14159)*sin(tau/180*3.14159)/cos(heightAngle/180*3.14159))/3.14159*180.0;
        myMotor.movetodir(dirAngle,heightAngle);
    }

    void realTimeDebug(){
        //switchon
        Serial.println("*******************************");
        //Serial.print("Switch statue:");
        //Serial.print(digitalRead(10));

        //light sensor debug
        int lt = 2;
        int lb = 3;
        int rt = 4;
        int rb = 5;
        int ltb = analogRead(lt); // top left
        int rtb = analogRead(rt); // top right
        int lbb = analogRead(lb); // down left
        int rbb = analogRead(rb); // down rigt
        Serial.println("Light sensors:");
        Serial.print("\n lt:");Serial.print(ltb);
        Serial.print("\n rt:");Serial.print(rtb);
        Serial.print("\n lb:");Serial.print(lbb);
        Serial.print("\n rb:");Serial.print(rbb);


        //motor debug
        Serial.print("\n Motor1 height:");Serial.print(myMotor.height1);
        Serial.print("\n Motor2 height:");Serial.print(myMotor.height2);        


        //rtc module debug
        RtcDateTime tmpnow = Rtc.GetDateTime();
        Serial.print("\n Current time: ");
        Serial.print(tmpnow.Year());Serial.print("-");
        Serial.print(tmpnow.Month());Serial.print("-");
        Serial.print(tmpnow.Day());Serial.print(",");
        Serial.print(tmpnow.Hour());Serial.print(":");
        Serial.print(tmpnow.Minute());Serial.print(":");
        Serial.print(tmpnow.Second());Serial.print("\n");
        Serial.println("================================");

    }
