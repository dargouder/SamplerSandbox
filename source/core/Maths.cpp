#include <limits>
#include "Maths.h"

using namespace Solstice;

const float Maths::Infinity = std::numeric_limits<float>::max();

const float Maths::Pi = 3.14159265359f;

const float Maths::InversePi = 1.0f	/ Maths::Pi;

const float Maths::PiOver4 = Maths::Pi / 4.0;
const float Maths::PiOver2 = Maths::Pi / 2.0;

const float Maths::OneMinusEpsilon = 0.99999994f;