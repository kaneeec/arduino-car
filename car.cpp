#include "Arduino.h"
#include "libraries/StepperWithDriver/StepperWithDriver.h"
#include "libraries/DCMotor/DCMotor.h"
#include "libraries/BTController/BTController.h"

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

StepperWithDriver stepper(6, 7, 8, 9);
DCMotor dcMotor(2, 3);
BTController bt(10, 11);

CarControl control = MANUAL;

void readBtController();

void setup() {
}

void loop() {
    readBtController();
    stepper.run();
    dcMotor.run();
}

void readBtController() {
    if (bt.read()) {
        String value = bt.getValue();

        if (value.indexOf('1') >= 0) {
            dcMotor.setDirection(FORWARDS);
            dcMotor.start();
        } else if (value.indexOf('2') >= 0) {
            dcMotor.setDirection(BACKWARDS);
            dcMotor.start();
        } else {
            dcMotor.stop();
        }

        if (value.indexOf('3') >= 0) {
            stepper.setAngle(3, LEFT);
        } else if (value.indexOf('4') >= 0) {
            stepper.setAngle(3, RIGHT);
        }
    }
}
