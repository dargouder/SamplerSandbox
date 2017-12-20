
#pragma once

namespace Solstice {
	
	class Maths{
public:
		inline static float Min(float max, float min){
			return max > min ? min : max;
		}
		inline static float Clamp(float p_val, float p_low, float p_high){
			if (p_val < p_low) {
				return p_low;
			}
			else if (p_val > p_high){
				return p_high;
			}
			else {
				return p_val;
			}
		}
		
		static const float Infinity;
		static const float Pi;
		static const float InversePi;
		static const float PiOver4;
		static const float PiOver2;
		static const float OneMinusEpsilon;
	};
}