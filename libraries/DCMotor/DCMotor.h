#ifndef LIBRARIES_DCMOTOR_DCMOTOR_H_
#define LIBRARIES_DCMOTOR_DCMOTOR_H_

#include "../Commons/MotorUtils.h"

class DCMotor {

    public:
        DCMotor(int pinGoForwards, int pinGoBackwards);
        void start();
        void stop();
        void run();
        void setDirection(MotorDirection direction);
        bool isRunning();

    private:
        int pinGoForwards;
        int pinGoBackwards;

        bool started = false;
        MotorDirection direction = FORWARDS;

        int getEnabledPin();
        int getDisabledPin();

};

#endif /* LIBRARIES_DCMOTOR_DCMOTOR_H_ */
