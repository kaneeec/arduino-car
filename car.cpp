#include "Arduino.h"
#include "libraries/StepperWithDriver/StepperWithDriver.h"
#include "libraries/IRemote/IRremote.h"
#include "libraries/IRemote/IRremoteInt.h"
#include "libraries/DCMotor/DCMotor.h"

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

IRrecv irSensor(IR_IN);
decode_results irSensorReading;

Direction direction = LEFT;

void setup() {
    Serial.begin(9600);
    stepper.setAngle(360, direction);
    irSensor.enableIRIn();
}

void loop() {
    readIr();
    stepper.run();
    dcMotor.run();
}

void readIr() {
    if (irSensor.decode(&irSensorReading)) {
        if (irSensorReading.value == IR_START_STOP) {
            if (dcMotor.isRunning()) {
                dcMotor.stop();
            } else {
                dcMotor.start();
            }
        }
        if (irSensorReading.value == IR_LEFT) {
            direction = LEFT;
            stepper.setAngle(45, LEFT);
        }
        if (irSensorReading.value == IR_RIGHT) {
            stepper.setAngle(45, RIGHT);
        }
        if (irSensorReading.value == IR_FORWARDS) {
            dcMotor.setDirection(FORWARDS);
        }
        if (irSensorReading.value == IR_BACKWARDS) {
            dcMotor.setDirection(BACKWARDS);
        }
        Serial.println(irSensorReading.value);
        irSensor.resume(); // Receive the next value
    }
}
