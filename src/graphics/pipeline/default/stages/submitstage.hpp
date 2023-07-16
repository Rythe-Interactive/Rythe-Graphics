#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>

namespace rythe::rendering
{
    class SubmitStage : public RenderStage<SubmitStage>
    {
        unsigned int m_quadVAO, m_quadVBO;
        shader_handle m_screenShader;

    public:
        virtual void setup(app::window& context) override;
        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
        virtual rsl::priority_type priority() override;
    };
}
