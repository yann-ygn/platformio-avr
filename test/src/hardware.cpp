#include <Arduino.h>
#include "bypass.h"
#include "encoder.h"
#include "fv1.h"
#include "led.h"
#include "leddriver.h"
#include "memory.h"
#include "potentiometer.h"
#include "switch.h"

Bypass byp(2, 1);
TemporarySwitch bypfsw(11, 1000);
Led bypled(10);