#ifndef LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_
#define LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_

#include "../Commons/MotorUtils.h"

class StepperWithDriver {

    public:
        StepperWithDriver(int pin1, int pin2, int pin3, int pin4);
        void setSteps(int steps, MotorDirection direction);
        void setAngle(int angle, MotorDirection direction);
        void run();

    private:
        const long STEPS_PER_TURN = 64;
    
        int pin1;
        int pin2;
        int pin3;
        int pin4;

        bool started = false;

        long stepsToGo = 0;
        long currentStep = 0;
        long lastStepTime = millis();
        MotorDirection direction = LEFT;

        int motorState = -1;

        void setNextState(MotorDirection direction);
        void step(MotorDirection direction);
        void stop();

};

#endif /* LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_ */
