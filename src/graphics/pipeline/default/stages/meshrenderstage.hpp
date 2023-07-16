#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>

namespace rythe::rendering
{
    class MeshRenderStage : public RenderStage<MeshRenderStage>
    {
        std::vector<math::float4x4> m_matrices;

    public:
        virtual void setup(app::window& context) override;
        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
        virtual rsl::priority_type priority() override;
    };
}
