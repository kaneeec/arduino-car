#ifndef LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_
#define LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_

enum Direction {
    LEFT, RIGHT
};

class StepperWithDriver {

    public:
        StepperWithDriver(int pin1, int pin2, int pin3, int pin4);
        void setSteps(int steps, Direction direction);
        void setAngle(int angle, Direction direction);
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
        Direction direction = LEFT;

        int motorState = -1;

        void setNextState(Direction direction);
        void step(Direction direction);
        void stop();
};

#endif /* LIBRARIES_STEPPERWITHDRIVER_STEPPERWITHDRIVER_H_ */
