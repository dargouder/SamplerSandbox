//
// Created by Darryl Gouder on 28/12/2017.
//
#pragma once

#include "Renderer.h"

#include "IO/Image.h"

namespace Solstice {

    class SamplerRenderer : public Renderer {
    public:
        std::unique_ptr<Sampler> sampler;
        int res_x;
        int res_y;
        Image image;

        SamplerRenderer();
        SamplerRenderer(std::unique_ptr<Sampler> p_sampler, int p_res_x, int p_res_y, std::string p_image_name);
        void Render();
    };
}