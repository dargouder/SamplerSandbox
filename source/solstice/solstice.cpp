#include <immintrin.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Camera.h"
#include "HitableList.h"
#include "IO/ImageIO.h"
#include "Sphere.h"
#include "samplers/StratifiedSampler.h"

using namespace Solstice;

RGBColour CheckerBoardTest(const Ray& r, Hitable& world, int depth) {
    HitRecord record;

    if (world.hit(r, 0.001, Maths::Infinity, record)) {
        double scale = 200.0;
        double sines = sin(scale * record.p.x) * sin(scale * record.p.y) *
                       sin(scale * record.p.z);
        if (sines < 0) {
            return RGBColour(1);
        } else {
            return RGBColour(0);
        }
    } else {
        return RGBColour(1.0);
    }
}

void BuildScene(HitableList& p_world) {
    p_world.list.push_back(
        std::make_unique<Sphere>(Vector3(0, -1000, -6), 1000));
}

Image RenderStratifiedSampler(int nx, int ny, int sppx, int sppy) {
    std::unique_ptr<Sampler> sampler =
        std::make_unique<StratifiedSampler>(sppx, sppy, true, 2);
    Vector3 look_from(0, 0, 0);
    Vector3 look_at(0, 0, -1);
    float dist_to_focus = 1.0;
    float aperture = 0.0;

    Camera camera(look_from, look_at, Vector3(0, 1, 0), 20,
                  float(nx) / float(ny), aperture, dist_to_focus);

    Image image(nx, ny);
    HitableList world;

    BuildScene(world);

    float nx_divisor = 1.0f / float(nx);
    float ny_divisor = 1.0f / float(ny);

    int ns = sppx * sppy;
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            RGBColour col(0);
            Point2i pixel(i, j);

            sampler->StartPixel(pixel);

            do {
                CameraSample cs = sampler->GetCameraSample(pixel);
                cs.m_pixel_sample.x *= nx_divisor;
                cs.m_pixel_sample.y *= ny_divisor;

                float u = float(i) / float(nx);
                float v = float(j) / float(ny);

                cs.m_pixel_sample.x += u;
                cs.m_pixel_sample.y += v;

                Ray r = camera.generate_ray(cs);

                col += CheckerBoardTest(r, world, 0);

            } while (sampler->StartNextSample());
            col = col / float(ns);
            image.set_pixel(i, j, col);
        }
    }

    return image;
}

bool DrawImage(std::string filename, const Image& image, const int nx,
               const int ny) {
    auto char_image = image.get_image();
    return ImageIO::export_png(filename, char_image, nx, ny);
}

void RenderRandomJittered(int nx, int ny) {
    // Vector3 look_from(13, 2, 3);

    Vector3 look_from(0, 0, 0);
    Vector3 look_at(0, 0, -1);
    float dist_to_focus = 1.0;
    float aperture = 0.0;

    Camera camera(look_from, look_at, Vector3(0, 1, 0), 20,
                  float(nx) / float(ny), aperture, dist_to_focus);

    Image image(nx, ny);
    HitableList world;

    BuildScene(world);

    float nx_divisor = 1.0f / float(nx);
    float ny_divisor = 1.0f / float(ny);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            RGBColour col(0);
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            float u_sample = 0.5f * nx_divisor;
            float v_sample = 0.5f * ny_divisor;
            CameraSample cs;
            cs.m_pixel_sample.x = u + u_sample;
            cs.m_pixel_sample.y = v + v_sample;
            Ray r = camera.generate_ray(cs);
            col += CheckerBoardTest(r, world, 0);

            image.set_pixel(i, j, col);
        }
    }
}

double MSE(const Image& ground_truth, const Image& observed_image, int nx,
           int ny) {
    double res = 0.0;
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            double error = ground_truth.get_pixel(i, j).r -
                           observed_image.get_pixel(i, j).r;
            res += error * error;
        }
    }
    return res / double(nx * ny);
}

int main() {
    float nx = 800.0f;
    float ny = 600.0f;

    int max_samples = 4;

    Image ground_truth =
        RenderStratifiedSampler(16, 16, max_samples, max_samples);

    std::ofstream file;
    file.open("mse.txt");

    for (int i = 1; i <= max_samples; ++i) {
        int total_spp = i * i;

        auto start = std::chrono::system_clock::now();
        auto image = RenderStratifiedSampler(nx, ny, i, i);
        auto end = std::chrono::system_clock::now();
        std::stringstream filename;
        filename << "Stratified_" << total_spp << ".png";
        DrawImage(filename.str(), image, nx, ny);
        std::chrono::duration<double> elapsed_seconds = end - start;
        double mse = MSE(ground_truth, image, nx, ny);
        // std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s\n";
        file << total_spp << "," << mse << std::endl;
        std::cout << "MSE for " << total_spp << ": " << mse << std::endl;
    }

    return 0;
}
