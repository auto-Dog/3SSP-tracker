#ifndef __TRACKING_H__
#define __TRACKING_H__
	#include <math.h>
  	#include <Arduino.h>
	#include "control.h"
	#include <ThreeWire.h>
	#include <RtcDS1302.h>
	#include "motor_ctrl.h"
	bool timeAssert();
	bool weatherAssert();
	void passiveTracking();
	void activeTracking();
	void realTimeDebug();

#endif
