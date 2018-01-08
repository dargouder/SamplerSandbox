//
// Created by Darryl Gouder on 28/12/2017.
//
#pragma once

#include <string>
#include "Sampler.h"

namespace Solstice
{
    class Renderer
    {
      public:
        Renderer();
        virtual void Render() = 0;
    };

}  // namespace Solstice