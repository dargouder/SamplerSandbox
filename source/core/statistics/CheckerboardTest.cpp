//
// Created by Darryl Gouder on 22/12/2017.
//

#include "CheckerboardTest.h"

using namespace Solstice;

CheckerboardTest::CheckerboardTest(double p_checkerBoardSize)
    : checkerBoardSize(p_checkerBoardSize)
{
    scene.BuildFloorScene();
}

RGBColour CheckerboardTest::EvaluatePixel(const Ray &r)
{
    HitRecord record;

    if (scene.Intersect(r, record))
    {
        double sines = sin(checkerBoardSize * record.p.x) *
                       sin(checkerBoardSize * record.p.y) *
                       sin(checkerBoardSize * record.p.z);

        if (sines < 0)
        {
            return RGBColour(1.0);
        }
        else
        {
            return RGBColour(0.0);
        }
    }
    else
    {
        return RGBColour(1.0);
    }
}
