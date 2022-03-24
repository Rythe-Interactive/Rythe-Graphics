#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>
#include <graphics/components/renderable.hpp>

namespace legion::rendering
{
    class MeshBatchingStage : public RenderStage<MeshBatchingStage>
    {
    public:
        virtual void setup(app::window& context) override;
        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, time::span deltaTime) override;
        virtual priority_type priority() override;
    };
}