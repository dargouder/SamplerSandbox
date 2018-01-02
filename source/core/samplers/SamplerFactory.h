//
// Created by Darryl Gouder on 22/12/2017.
//
#pragma once

#include "samplers/StratifiedSampler.h"

namespace Solstice
{
    std::unique_ptr<Sampler> FactorySampler(std::string p_type, int x_pixels, int y_pixels, bool jitter, int dims)
    {
        if (p_type == "stratified")
        {
            return std::move(std::make_unique<StratifiedSampler>(x_pixels, y_pixels, jitter, dims));
        }
        std::cout << "No type detected" << std::endl;
        return nullptr;
    }

}