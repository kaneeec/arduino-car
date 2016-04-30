#include "Arduino.h"
#include "DCMotor.h"

DCMotor::DCMotor(int pinGoForwards, int pinGoBackwards) {
    this->pinGoForwards = pinGoForwards;
    this->pinGoBackwards = pinGoBackwards;

    pinMode(pinGoForwards, OUTPUT);
    pinMode(pinGoBackwards, OUTPUT);
}

void DCMotor::start() {
    this->started = true;
}

void DCMotor::stop() {
    this->started = false;
    digitalWrite(pinGoForwards, LOW);
    digitalWrite(pinGoBackwards, LOW);
}

void DCMotor::run() {
    if (started) {
        digitalWrite(getEnabledPin(), HIGH);
        digitalWrite(getDisabledPin(), LOW);
    }
}

void DCMotor::setDirection(MotorDirection direction) {
    this->direction = direction;
}

bool DCMotor::isRunning() {
    return this->started;
}

int DCMotor::getEnabledPin() {
    return direction == FORWARDS ? pinGoForwards : pinGoBackwards;
}

int DCMotor::getDisabledPin() {
    return direction == FORWARDS ? pinGoBackwards : pinGoForwards;
}



