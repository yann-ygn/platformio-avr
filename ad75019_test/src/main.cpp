#include <Arduino.h>
#include "SwitchMatrix.h"

SwitchMatrix AD75019(0);

void setup()
{
  AD75019.switchMatrixSetup();
  Serial.begin(115200);
  delay(1000);

  AD75019.setSwitchArray(5, 0, 1);

  for (int y = 15; y >= 0; y--) // Rows
  {
      Serial.print("y : ");
      Serial.print(y);
      Serial.print(" ");

      for (int x = 15; x >= 0; x--) // Columns
      {
        Serial.print(AD75019.getSwitchArray(y, x));
        Serial.print(" ");
      }

      Serial.println();
  }

  delay(1000);
  AD75019.sendSwitchArray();
}

void loop()
{

}

/**
#include <Arduino.h>

///////////////////////////////////////////////////////////////////////
//
//   AD75019 Switch Matrix Control
//
///////////////////////////////////////////////////////////////////////

// AD75019 connections
#define SCLK_PIN	7 // = SCK  = PB5 = atmega pin 19
#define SIN_PIN		5 // = MOSI = PB3 = atmega pin 17
#define PCLK_PIN	0  // = OC1A = PB1 = atmega pin 15

#define MAXPROGRAMS 8
#define NUMPROGRAMS 5 // rhythm/delay/delay+boost/special/mute

// ************ AD75019 connection definitions. Board/hardware dependent. *******

// First nibble is the input of the effect, they are connected to the Y's.
// Second nibble is the output of the effect, connected to the X.

// The first six definitions are fixed 'effects' on the board. Make sure
// that 'output only' are not used as input, and 'input only' are not used as output,
// since the other nibble of the definition is not defined! (Hm, that sounded weird) 
#define INNPUT    0x00 // The input to the Switcheroo, it's an 'effect output' only.
#define OUT_L     0x0b // OUT_L is an 'effect input' FIXME: labeling schematic. PCB is ok.
#define OUT_R     0x09 // Same for OUT_R
#define GND       0x20 // This is an 'effect output' only, can be used to ground
                       // the input of unused effects.
#define MIXER1    0x0e // Two-in-one opamp mixer block on the PCB.
#define MIXER2    0x0f // The other mixer input.
#define MIXER_OUT 0x10 // The output of the mixer.

// The rest are the connections to the headers
// If there's a need for more headers, they can be soldered to the
// AD75019 socket on the bottom of the PCB and then defined here.
#define CONN_5 0x58
#define CONN_6 0x73
#define CONN_7 0x92
#define CONN_8 0xb5
#define CONN_9 0xd4
#define CONN_A 0xf7
#define CONN_B 0xe6
#define CONN_C 0xa1
#define CONN_D 0x6c

// ************ Effect connection definitions **************************
//
// Defines what effect is connected to which header, so composing the
// programs becomes easier.
#define GATE     CONN_5
#define POST     CONN_6
#define DELAY    CONN_9
#define BOOST    CONN_7
#define HM2      CONN_8
#define SPECIAL  CONN_A
#define FEEDBCK  CONN_B
#define TAILS    CONN_C
#define FV1_FBCK CONN_D

// Globals
uint16_t      programs[NUMPROGRAMS][16];
int           activeprogram=0; // Rhythm

// Connects the output of effect 'from' to the input of effect 'to', in program 'program'
void connect(uint8_t program, uint8_t from, uint8_t to) {
  uint8_t x, y;
  // Find out correct Y and X from the effect- and hardwaredefinitions
  y = to & 0x0f;                // Lower nibble needed: mask out higher nibble
  x = from >> 4;                // Higher nibble needed: shift down to lower nibble
  programs[program][y] |= 1<<x; // Then set this bit in the program.
}

void connect_all() {
  memset(programs, 0, sizeof(programs)); // Empty the program memory

  // default rhythm
  connect(0, INNPUT,    HM2);
  connect(0, HM2,       GATE);
  connect(0, GATE,      MIXER1);
  connect(0, DELAY,     MIXER2);
  connect(0, MIXER_OUT, OUT_L);
  connect(0, GND,       DELAY);
  connect(0, GND,       BOOST);
  connect(0, FV1_FBCK,  TAILS);
  connect(0, TAILS,     FV1_FBCK);
 
  // delay
  connect(1, INNPUT,    HM2);
  connect(1, HM2,       GATE);
  connect(1, GATE,      DELAY);
  connect(1, GND,       MIXER1);
  connect(1, DELAY,     MIXER2);
  connect(1, MIXER_OUT, OUT_L);
  connect(1, GND,       BOOST);
  connect(1, FV1_FBCK,  FEEDBCK);
  connect(1, FEEDBCK,   FV1_FBCK);

  // delay+boost
  connect(2, INNPUT,    HM2);
  connect(2, HM2,       GATE);
  connect(2, GATE,      DELAY);
  connect(2, DELAY,     BOOST);
  connect(2, GND,       MIXER1);
  connect(2, BOOST,     MIXER2);
  connect(2, MIXER_OUT, OUT_L);
  connect(2, FV1_FBCK,  FEEDBCK);
  connect(2, FEEDBCK,   FV1_FBCK);

  // special
  connect(3, INNPUT,    HM2);
  connect(3, HM2,       GATE);
  connect(3, GATE,      SPECIAL);
  connect(3, SPECIAL,   OUT_L);
 
  // mute
  connect(4, GND,       HM2);
  connect(4, GND,       GATE);
  connect(4, GND,       MIXER1);
  connect(4, GND,       DELAY);
  connect(4, GND,       MIXER2);
  connect(4, GND,       OUT_L);

  for (int y = 15; y >= 0; y--) // Rows
  {
      Serial.print("y : ");
      Serial.print(y);
      Serial.print(" ");

      for (int x = 15; x >= 0; x--) // Columns
      {
        Serial.print(bitRead(programs[0][y], x));
        Serial.print(" ");
      }

      Serial.println();
  }
}

void update(uint8_t newprogram) {
  uint8_t i;
  uint16_t n, mask;
  // Clock in from highest bits to lowest
  for (i=16;--i<255;) { // Stops when uint8_t flips over
    n = programs[newprogram][i];
    for (mask = 0x8000; mask; mask >>= 1) {
      Serial.println(n);
      Serial.println(mask);
      // Mask goes from bit 15 to bit 0.
      digitalWrite(SIN_PIN, (n & mask) ? HIGH : LOW);
      asm("nop"); asm("nop");
      digitalWrite(SCLK_PIN, HIGH);
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      digitalWrite(SCLK_PIN, LOW);
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }
  }
  asm("nop"); asm("nop"); asm("nop"); asm("nop");
  asm("nop"); asm("nop"); asm("nop"); asm("nop");
  digitalWrite(PCLK_PIN, LOW);
  asm("nop"); asm("nop"); asm("nop"); asm("nop");
  asm("nop"); asm("nop"); asm("nop"); asm("nop");
  digitalWrite(PCLK_PIN, HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(SCLK_PIN, OUTPUT);
  pinMode(SIN_PIN, OUTPUT);
  digitalWrite(PCLK_PIN, HIGH);
  pinMode(PCLK_PIN, OUTPUT);
  connect_all();         // Build programs
  update(activeprogram); // Set switches to default
}

void loop() {

}
**/