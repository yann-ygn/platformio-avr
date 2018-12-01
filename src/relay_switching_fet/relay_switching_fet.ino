#include <arduino.h>

#define FOOTSWITCH 4
#define RELAY 3
#define J175 0

long int now;
int switchState;
int lastSwitchState = 0;
int relayState = 0;
long int lastPressTime = 0;

int footSwitchPress();

void setup()
{
    pinMode(FOOTSWITCH, INPUT_PULLUP);
    pinMode(RELAY, OUTPUT);
    pinMode(J175, OUTPUT);

    digitalWrite(RELAY, relayState);
}

void loop()
{
    now = millis();

    if (footSwitchPress())
    {
        lastPressTime = now;
        relayState = !relayState;

        switch (relayState)
        {            
            // Effect -> Bypass
            case 0:
                digitalWrite(J175, HIGH);
                delay(10);
                digitalWrite(RELAY, relayState);
            break;
            
            // Bypass -> Effect
            case 1:
                digitalWrite(RELAY, relayState);
                delay(10);
                digitalWrite(J175, LOW);
            break;
        }
    }
}

int footSwitchPress()
{
    switchState = digitalRead(FOOTSWITCH);

    if (switchState == LOW && now - lastPressTime > 300)
    {
        lastSwitchState = switchState;
        return 1;
    }

    lastSwitchState = switchState;
    return 0;
}
