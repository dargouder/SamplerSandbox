//
// Created by Darryl Gouder on 28/12/2017.
//

#pragma once

#include "renderers/SamplerRenderer.h"
#include "samplers/SamplerFactory.h"

namespace Solstice
{
    class RendererParameters
    {
      public:
        std::string type;
        std::string image_name;
        int x_res;
        int y_res;
        SamplerParameters samplerParameters;
    };

    std::unique_ptr<Renderer> RendererFactory(RendererParameters parameters)
    {
        if (parameters.type == "sampler")
        {
            std::unique_ptr<Sampler> sampler =
                SamplerFactory(parameters.samplerParameters);
            auto renderer = std::make_unique<SamplerRenderer>(
                std::move(sampler), parameters.x_res, parameters.y_res,
                parameters.image_name);
            return std::move(renderer);
        }
        std::cout << "No type detected" << std::endl;
        return nullptr;
    }

}  // namespace Solstice