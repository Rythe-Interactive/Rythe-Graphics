#pragma once
#include <graphics/data/postprocessingeffect.hpp>

namespace rythe::rendering
{
    class Skybox : public PostProcessingEffect<Skybox>
    {
    public:
        void setup(app::window& context) override;

        void renderPass(framebuffer& fbo, RenderPipelineBase* pipeline, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime);

    };


}
