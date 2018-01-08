//
// Created by Darryl Gouder on 28/12/2017.
//

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Camera.h"
#include "SamplerRenderer.h"

#include "IO/ImageIO.h"

#include "statistics/CheckerboardTest.h"

using namespace Solstice;

SamplerRenderer::SamplerRenderer() : image(0, 0, "") {}

SamplerRenderer::SamplerRenderer(std::unique_ptr<Sampler> p_sampler,
                                 int p_res_x, int p_res_y,
                                 std::string p_image_name)
    : sampler(std::move(p_sampler)),
      res_x(p_res_x),
      res_y(p_res_y),
      image(p_res_x, p_res_y, p_image_name)
{
}

void SamplerRenderer::Render()
{
    std::unique_ptr<ConvergenceTest> checkTest =
        std::make_unique<CheckerboardTest>(300);

    int nx = res_x;
    int ny = res_y;

    Vector3 look_from(0, 0, 0);
    Vector3 look_at(0, 0, -1);
    double dist_to_focus = 1.0;
    double aperture = 0.0;

    Camera camera(look_from, look_at, Vector3(0.0, 1.0, 0.0), 20.0,
                  double(nx) / double(ny), aperture, dist_to_focus);

    double nx_divisor = 1.0 / nx;
    double ny_divisor = 1.0 / ny;
    int ns = sampler->m_samples_per_pixel;

    for (int j = 0; j < ny; j++)
    {
        for (int i = 0; i < nx; i++)
        {
            RGBColour col(0);
            Point2i pixel(i, j);

            sampler->StartPixel(pixel);

            do
            {
                CameraSample cs = sampler->GetCameraSample(pixel);

                cs.m_pixel_sample.x *= nx_divisor;
                cs.m_pixel_sample.y *= ny_divisor;

                float u = float(i) / float(nx);
                float v = float(j) / float(ny);

                cs.m_pixel_sample.x += u;
                cs.m_pixel_sample.y += v;

                Ray r = camera.generate_ray(cs);
                col += checkTest->EvaluatePixel(r);

            } while (sampler->StartNextSample());
            col = col / float(ns);
            image.set_pixel(i, j, col);
        }
    }

    auto char_image = image.get_image();
    ImageIO::export_png(image.get_image_name(), char_image, nx, ny);
}
