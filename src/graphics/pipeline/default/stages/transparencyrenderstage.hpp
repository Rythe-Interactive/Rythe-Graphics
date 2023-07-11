#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>

namespace rythe::rendering
{
    class TransparencyRenderStage : public RenderStage<TransparencyRenderStage>
    {
        std::vector<math::mat4> m_matrices;

    public:
        virtual void setup(app::window& context) override;
        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
        virtual priority_type priority() override;
    };
}
