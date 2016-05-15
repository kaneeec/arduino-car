#include "Arduino.h"
#include "libraries/StepperWithDriver/StepperWithDriver.h"
#include "libraries/DCMotor/DCMotor.h"
#include "libraries/IRemote/IrRemote.h"
#include "libraries/IRemote/IrRemoteInt.h"

const long IR_OK = 16712445;
const long IR_LEFT = 16720605;
const long IR_RIGHT = 16761405;
const long IR_UP = 16736925;
const long IR_DOWN = 16754775;
const long IR_STAR = 16728765;
const long IR_HASH = 16732845;

enum CarControl {
    MANUAL, AI
};

StepperWithDriver stepper(8, 9, 10, 11);
DCMotor dcMotor(2, 3);

IrReceiver irReceiver(5);
IrReading irReading;

CarControl control = MANUAL;

void readIr();

void setup() {
    irReceiver.enableIRIn();
}

void loop() {
    readIr();
    stepper.run();
    dcMotor.run();
}

void readIr() {
    if (irReceiver.decode(&irReading)) {
        if (control == MANUAL) {
            if (irReading.value == IR_OK) {
                if (dcMotor.isRunning()) {
                    dcMotor.stop();
                } else {
                    dcMotor.start();
                }
            } else if (irReading.value == IR_LEFT) {
                stepper.setAngle(10, LEFT);
            } else if (irReading.value == IR_RIGHT) {
                stepper.setAngle(10, RIGHT);
            } else if (irReading.value == IR_UP) {
                dcMotor.setDirection(FORWARDS);
            } else if (irReading.value == IR_DOWN) {
                dcMotor.setDirection(BACKWARDS);
            }
        }

        if (irReading.value == IR_STAR) {
            control = MANUAL;
        } else if (irReading.value == IR_HASH) {
            control = AI;
        }
        irReceiver.resume(); // Receive the next value
    }
}
