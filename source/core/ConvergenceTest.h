//
// Created by Darryl Gouder on 22/12/2017.
//
#pragma once

#include <memory>

#include "RGBColour.h"
#include "Scene.h"

namespace Solstice
{
    class ConvergenceTest
    {
      public:
        virtual RGBColour EvaluatePixel(const Ray& r) = 0;

        ConvergenceTest();
        ~ConvergenceTest();
    };
}  // namespace Solstice