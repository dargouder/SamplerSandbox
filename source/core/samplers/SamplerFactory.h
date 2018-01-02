//
// Created by Darryl Gouder on 22/12/2017.
//
#pragma once

#include "samplers/StratifiedSampler.h"


namespace Solstice
{
    class SamplerParameters
    {
    public:
        std::string type;
        int x_samples;
        int y_samples;
        bool jitter;
        int dims;
    };


    std::unique_ptr<Sampler> SamplerFactory(SamplerParameters parameters)
    {
        if (parameters.type == "stratified")
        {
            return std::move(std::make_unique<StratifiedSampler>(parameters.x_samples, parameters.y_samples, parameters.jitter, parameters.jitter));
        }
        std::cout << "No type detected" << std::endl;
        return nullptr;
    }

}