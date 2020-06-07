#include <Arduino.h>

#include "hardware.h"
#include "potentiometer.h"
#include "tap.h"
#include "selector.h"
#include "bypass.h"
#include "memory.h"
#include "program.h"
#include "FV1.h"
#include "midi.h"
#include "expression.h"

Midi midi0;
Memory mem0;
Selector selector0;
Tap tap0;
Bypass bypass0;
FV1 dsp0;
Pot pot0(A3);
Pot pot1(A1);
Pot pot2(A4);
Pot pot3(A0);
DigitalPot dpot0(3);
Expr expr0(A2, 23);

void Hardware::hardwareSetup()
{
    midi0.midiSetup();
    mem0.memorySetup();
    
    midi0.setMidiChannel(mem0.readMidiChannel());

    bypass0.setBypassState(mem0.readBypassState());
    bypass0.bypassSetup();
    //attachInterrupt(digitalPinToInterrupt(11), bypassInterrupt, FALLING);

    dsp0.FV1Setup();
    
    tap0.tapSetup();
    
    pot0.potSetup();
    pot1.potSetup();
    pot2.potSetup();
    pot3.potSetup();

    dpot0.digitalPotSetup();

    expr0.exprSetup();

    selector0.selectorSetup();
}