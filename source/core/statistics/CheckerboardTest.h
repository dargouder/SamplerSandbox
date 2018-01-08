//
// Created by Darryl Gouder on 22/12/2017.
//

#pragma once

#include "ConvergenceTest.h"

namespace Solstice
{
    class CheckerboardTest : public ConvergenceTest
    {
      public:
        RGBColour EvaluatePixel(const Ray& r);

        CheckerboardTest(const double p_checkerBoardSize = 200.0);

      private:
        double checkerBoardSize;
        Scene scene;
    };
}  // namespace Solstice
