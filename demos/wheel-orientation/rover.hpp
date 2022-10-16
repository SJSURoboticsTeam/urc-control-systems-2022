#pragma once
#include <array>

#include "utility/log.hpp"
#include "leg.hpp"

namespace sjsu::demo
{
    class Rover
    {
    public:
        struct Legs
        {
            sjsu::demo::Leg *left = nullptr;
            sjsu::demo::Leg *right = nullptr;
            sjsu::demo::Leg *back = nullptr;
        };

        Rover(Legs &legs) : legs_(legs){};

        void Initialize()
        {
            legs_.left->Initialize();
            legs_.right->Initialize();
            legs_.back->Initialize();
        }

        void SetLegsToZeroExceptBack(int back_angle)
        {
            legs_.left->SetSteerAngle(0);
            legs_.right->SetSteerAngle(0);
            sjsu::LogInfo("setting back angle in 3s...");
            sjsu::Delay(3s);
            legs_.back->SetSteerAngle(back_angle);
        }

        /// [0] = {L, R, B}, [1] = {B, L, R}, [2] = {R, B, L}
        void SwitchLegOrientation(int position)
        {
            legs_.left = legs_array_[(position + 0) % 3];
            legs_.right = legs_array_[(position + 1) % 3];
            legs_.back = legs_array_[(position + 2) % 3];
            printf("Orientation: %d\tlegs_.left: %p\t legs_.right: %p\t legs_.back: %p\n", position % 3, legs_.left, legs_.right, legs_.back);
            legs_.right->Print();
            legs_.left->Print();
            legs_.back->Print();
        };

    private:
        Legs legs_;
        std::array<Leg *, 3> legs_array_{legs_.left, legs_.right, legs_.back};
    };
};