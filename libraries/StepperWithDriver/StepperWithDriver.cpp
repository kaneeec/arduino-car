#include "Arduino.h"
#include "StepperWithDriver.h"

StepperWithDriver::StepperWithDriver(int pin1, int pin2, int pin3, int pin4) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}

void StepperWithDriver::run() {
    if (stepsToGo > 0) {
        started = true;
        step(direction);
        delay(1);
        if ((currentStep++) == stepsToGo) {
            stop();
        }
    }
}

void StepperWithDriver::stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    started = false;
    stepsToGo = 0;
    currentStep = 0;
}

void StepperWithDriver::setSteps(int steps, MotorDirection direction) {
    this->stepsToGo = steps * STEPS_PER_TURN; 
    this->direction = direction;
}

void StepperWithDriver::setAngle(int angle, MotorDirection direction) {
    float partial = (float) angle / 360;
    float steps = STEPS_PER_TURN * STEPS_PER_TURN * partial;
    this->stepsToGo = round(steps);
    this->direction = direction;
}

void StepperWithDriver::step(MotorDirection direction) {
    if (micros() - lastStepTime >= 1000 && started) {
        switch (motorState) {
            case 0:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, HIGH);
                break;
            case 1:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, HIGH);
                digitalWrite(pin4, HIGH);
                break;
            case 2:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, HIGH);
                digitalWrite(pin4, LOW);
                break;
            case 3:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, HIGH);
                digitalWrite(pin3, HIGH);
                digitalWrite(pin4, LOW);
                break;
            case 4:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, HIGH);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, LOW);
                break;
            case 5:
                digitalWrite(pin1, HIGH);
                digitalWrite(pin2, HIGH);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, LOW);
                break;
            case 6:
                digitalWrite(pin1, HIGH);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, LOW);
                break;
            case 7:
                digitalWrite(pin1, HIGH);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, HIGH);
                break;
            default:
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, LOW);
                digitalWrite(pin3, LOW);
                digitalWrite(pin4, LOW);
                delay(500);
                break;
        }

        setNextState(direction);
        lastStepTime = micros();
    }
}

void StepperWithDriver::setNextState(MotorDirection direction) {
    motorState += direction == RIGHT ? 1 : -1;
    if (motorState > 7) {
        motorState = 0;
    }
    if (motorState < 0) {
        motorState = 7;
    }
}

