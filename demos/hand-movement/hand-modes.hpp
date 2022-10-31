#pragma once
#include "peripherals/lpc40xx/i2c.hpp"
#include "pca9685.hpp"
#include "hand-router.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:
        // Closes the hand to the minimum angle
        static hand_arguments CloseMode(hand_arguments arguments)
        {
            arguments.pinky_angle = min_angle_;
            arguments.ring_angle = min_angle_;
            arguments.middle_angle = min_angle_;
            arguments.index_angle = min_angle_;
            arguments.thumb_angle = min_angle_;
            return arguments;
        }
        // Opens the hand to the maximum angle
        static hand_arguments OpenMode(hand_arguments arguments)
        {
            arguments.pinky_angle = max_angle_;
            arguments.ring_angle = max_angle_;
            arguments.middle_angle = max_angle_;
            arguments.index_angle = max_angle_;
            arguments.thumb_angle = max_angle_;
            return arguments;
        }
        // Sets angle of each finger according to what mission control sends to each individual finger.
        static hand_arguments IndividualMode(hand_arguments arguments)
        {
          //  kClampedAngle.to();
            // int pClamped=clamp(arguments.pinky_angle,mapped_min_angle,mapped_max_angle);
            // int rClamped=clamp(arguments.ring_angle,mapped_min_angle,mapped_max_angle);
            // int mClamped=clamp(arguments.middle_angle, mapped_min_angle, mapped_max_angle);
            // int iClamped=clamp(arguments.index_angle, mapped_min_angle, mapped_max_angle);
            // int tClamped=clamp(arguments.thumb_angle,mapped_min_angle, mapped_max_angle);
            // int p=Map(pClamped, min_angle,max_angle,mapped_min_angle,mapped_max_angle);
            // int r=Map(rClamped, min_angle,max_angle,mapped_min_angle,mapped_max_angle);
            // int m=Map(mClamped, min_angle, max_angle,mapped_min_angle,mapped_max_angle);
            // int i=Map(iClamped,min_angle, max_angle,mapped_min_angle,mapped_max_angle);
            // int t=Map(tClamped,max_angle,min_angle,mapped_min_angle,mapped_max_angle);

            return arguments;
        }
        // Sets angle of all fingers according to what mission control sends to finger_angle.
        static hand_arguments SimultaneousMode(hand_arguments arguments)
        {
            arguments.pinky_angle = arguments.index_angle;
            arguments.ring_angle = arguments.index_angle;
            arguments.middle_angle = arguments.index_angle;
            arguments.index_angle = arguments.index_angle;
            arguments.thumb_angle = arguments.index_angle;
            return arguments;
        }

    private:
        static constexpr int kMinAngle = 88;
        // static constexpr int neutral_angle_ = 90;
        static constexpr int kMaxAngle = 175;
        static constexpr int kMappedMinAngle=0;
        static constexpr int kMappedMaxAngle=100;
    };
}