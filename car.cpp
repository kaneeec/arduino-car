#include "Arduino.h"
#include "libraries/StepperWithDriver/StepperWithDriver.h"
#include "libraries/IRemote/IRremote.h"
#include "libraries/IRemote/IRremoteInt.h"

const int IR_IN = 5;
const int DC_LEFT = 2;
const int DC_RIGHT = 3;

const long IR_START_STOP = 16712445;
const long IR_LEFT = 16720605;
const long IR_RIGHT = 16761405;
const long IR_UP = 16736925;
const long IR_DOWN = 16754775;

void readIr();

StepperWithDriver stepper(8, 9, 10, 11);

IRrecv irrecv(IR_IN);
decode_results irValue;

Direction direction = LEFT;

void setup() {
    Serial.begin(9600);

    stepper.setAngle(360, direction);
    pinMode(DC_LEFT, OUTPUT);
    pinMode(DC_RIGHT, OUTPUT);

    irrecv.enableIRIn();
}

void loop() {
    readIr();
    stepper.run();
}

void readIr() {
    if (irrecv.decode(&irValue)) {
        if (irValue.value == IR_START_STOP) {
            // stop/start
        }
        if (irValue.value == IR_LEFT) {
            direction = LEFT;
            stepper.setAngle(45, LEFT);
        }
        if (irValue.value == IR_RIGHT) {
            stepper.setAngle(45, RIGHT);
        }
        Serial.println(irValue.value);
        irrecv.resume(); // Receive the next value
    }
}
