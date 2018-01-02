
#include <cmath>

#include "renderers/RendererFactory.h"

using namespace Solstice;


int main(int argc, char* argv[]) {

    std::cout << "Welcome to the Sampler Sandbox Application" << std::endl;

    RendererParameters params;
    if (argc == 0)
    {
        return -1;
    } else {
        for (int i = 0; i < argc; ++i)
        {
            if(!strcmp(argv[i], "--spp"))
            {
                int spp = atoi(argv[++i]);
                int spp_root = floor(sqrt(spp));
                params.samplerParameters.x_samples = spp_root;
                params.samplerParameters.y_samples = spp_root;
                params.samplerParameters.jitter = true;
                params.samplerParameters.dims = 2;
            } else if (!strcmp(argv[i], "--sampler"))
            {
                params.type = "sampler";
                params.samplerParameters.type = argv[++i];
            } else if (!strcmp(argv[i], "--nx"))
            {
                params.x_res = atoi(argv[++i]);
            } else if (!strcmp(argv[i], "--ny"))
            {
                params.y_res = atoi(argv[++i]);
            }else if (!strcmp(argv[i], "--output"))
            {
                params.image_name = argv[++i];
            }
        }
        if (argc > 1)
        {
            std::unique_ptr<Renderer> renderer;
            renderer = RendererFactory(params);
            renderer->Render();
        }
    }



//    int nx = 600;
//    int ny = 400;
//
//    int max_samples = 60;
//
//    Image ground_truth =
//            RenderStratifiedSampler(nx, ny, max_samples, max_samples);
//
//    std::ofstream file;
//    file.open("mse.txt");
//
//    for (int i = 1; i <= max_samples; ++i) {
//
//        int total_spp = i * i;
//
//        auto start = std::chrono::system_clock::now();
//        auto image = RenderStratifiedSampler(nx, ny, i, i);
//        auto end = std::chrono::system_clock::now();
//        std::stringstream filename;
//        filename << "Stratified_" << total_spp << ".png";
//        DrawImage(filename.str(), image, nx, ny);
//        std::chrono::duration<double> elapsed_seconds = end - start;
//
//        double mse = Statistics::MSE(ground_truth, image, nx, ny);
//
//        // std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s\n";
//        file << total_spp << ", " << mse << std::endl;
//        std::cout << "MSE for " << total_spp << ": " << mse << std::endl;
//    }

    return 0;
}
