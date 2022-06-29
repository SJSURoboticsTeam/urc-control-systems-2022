#pragma once
#include "dto/hand-dto.hpp"
#include "utility/math/units.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "../implementations/hand/pca9685.hpp"

namespace sjsu::arm
{
    class HandRouter
    {
        public:
        HandRouter(sjsu::Pca9685 &thumb, sjsu::Pca9685 &pointer, sjsu::Pca9685 &middle, sjsu::Pca9685 &ring, sjsu::Pca9685 &pinky) : 
        thumb_(thumb), pointer_(pointer), middle_(middle), ring_(ring), pinky_(pinky) {};

        //Initialize
        void Initialize(){
          thumb_.thumb.Initialize();
          pointer_.pointer.Initialize();
          middle_.middle.Initialize();
          ring_.ring.Initialize();
          pinky_.pinky.Initialize();

        }
        
        //SetFingerArguments
        arm_arguments SetFingerArguments(arm_arguments arguments){
            thumb_,SetAngle(units::angle::degree_t(arguments.thumb_angle)), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            pointer_.SetAngle(units::angle::degree_t(arguments.thumb_angle)), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            arguments = arguments
            return arguments;
        }

        //GetFingerArguments
        arm_arguments GetFingerArguments(arm_argumen)
    
        //HomeFingers
        void HomeFingers()
        {
            thumb_.setPulseWidth(1, 10ms)
            pointer_.setPulseWidth(2, )
            middle_.setPulseWidth(3, )
            ring_.setPulseWidth(4, )
            pinky_.setPulseWidth(5, )
        }

        private:
        sjsu::arm::arm_arguments arguments_;
        sjsu::Pca9685 &thumb_;
        sjsu::Pca9685 &pointer_;
        sjsu::Pca9685 &middle_;
        sjsu::Pca9685 &ring_;
        sjsu::Pca9685 &pinky_;
    };
}