#pragma once
#include <graphics/data/postprocessingeffect.hpp>
#include <graphics/util/bindings.hpp>

namespace legion::rendering
{
    enum struct tonemapping_type
    {
        aces, legion, reinhard, reinhard_jodie, unreal3
    };

    class Tonemapping : public PostProcessingEffect<Tonemapping>
    {
    private:
        static std::atomic<id_type> m_currentShader;
        static std::atomic_bool m_autoExposure;
        static std::atomic<float> m_exposure;

    public:
        static void setAlgorithm(tonemapping_type type) noexcept;

        static void enableAutoExposure(bool enable) noexcept;
        static void setExposure(float value) noexcept;

        void setup(app::window& context) override;

        void renderPass(framebuffer& fbo, RenderPipelineBase* pipeline, camera& cam, const camera::camera_input& camInput, time::span deltaTime);

    };


}
