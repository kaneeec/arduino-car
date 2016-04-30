#include "Arduino.h"
#include "libraries/StepperWithDriver/StepperWithDriver.h"
#include "libraries/DCMotor/DCMotor.h"
#include "libraries/IRemote/IrRemote.h"
#include "libraries/IRemote/IrRemoteInt.h"

const int IR_IN = 5;

const long IR_START_STOP = 16712445;
const long IR_LEFT = 16720605;
const long IR_RIGHT = 16761405;
const long IR_FORWARDS = 16736925;
const long IR_BACKWARDS = 16754775;
const long IR_STAR = 16728765;
const long IR_HASH = 16732845;

void readIr();

StepperWithDriver stepper(8, 9, 10, 11);
DCMotor dcMotor(2, 3);

IrReceiver irReceiver(IR_IN);
IrReading irReading;

Direction direction = LEFT;

void setup() {
    Serial.begin(9600);
    stepper.setAngle(360, direction);
    irReceiver.enableIRIn();
}

void loop() {
    readIr();
    stepper.run();
    dcMotor.run();
}

void readIr() {
    if (irReceiver.decode(&irReading)) {
        if (irReading.value == IR_START_STOP) {
            if (dcMotor.isRunning()) {
                dcMotor.stop();
            } else {
                dcMotor.start();
            }
        }
        if (irReading.value == IR_LEFT) {
            direction = LEFT;
            stepper.setAngle(45, LEFT);
        }
        if (irReading.value == IR_RIGHT) {
            stepper.setAngle(45, RIGHT);
        }
        if (irReading.value == IR_FORWARDS) {
            dcMotor.setDirection(FORWARDS);
        }
        if (irReading.value == IR_BACKWARDS) {
            dcMotor.setDirection(BACKWARDS);
        }
        Serial.println(irReading.value);
        irReceiver.resume(); // Receive the next value
    }
}
