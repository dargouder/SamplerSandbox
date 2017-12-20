#pragma once

/*
* PCG Random Number Generation for C++
*
* Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* For additional information about the PCG random number generation scheme,
* including its license and other licensing options, visit
*
*     http://www.pcg-random.org
*/

/*
* This file is based on the demo program for the C generation schemes.
* It shows some basic generation tasks.
*/

#include <random>       // for random_device

#include "random/pcg_random.hpp"
namespace Solstice {
	class RNG {

	private:
		pcg32 rng;
		std::uniform_real_distribution<float> uniform_dist;

	public:
		RNG() {
			pcg_extras::seed_seq_from<std::random_device> seed_source;
			rng = pcg32(seed_source);
			uniform_dist = std::uniform_real_distribution<float>(0, 1);
		}

		float GetFloat()
		{
			return uniform_dist(rng);
		}

		uint32_t UniformUInt32(int p_num)
		{
			return rng(p_num);
		}

	};
}