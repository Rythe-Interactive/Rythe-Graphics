#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>

namespace rythe::rendering
{
    class FramebufferResizeStage : public RenderStage<FramebufferResizeStage>
    {
        static std::atomic<float> m_renderScale;

        math::ivec2 m_framebufferSize;
        texture_handle m_colorTexture[2];
        texture_handle m_normalTexture[2];
        texture_handle m_positionTexture[2];
        texture_handle m_overdrawTexture[2];
        texture_handle m_depthStencilTexture[2];

    public:
        static void setRenderScale(float renderScale);
        static float getRenderScale();

        virtual void setup(app::window& context) override;
        void shutdown();
        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
        virtual priority_type priority() override;

    };
}
