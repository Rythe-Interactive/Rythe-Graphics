#pragma once
#include <graphics/data/framebuffer.hpp>
#include <graphics/components/camera.hpp>
#include <graphics/pipeline/base/pipelinebase.hpp>
#include <graphics/pipeline/base/renderstage.hpp>
#include <application/application.hpp>

#include <memory>
#include <any>

namespace rythe::rendering
{
    template<typename Self>
    class RenderPipeline : public RenderPipelineBase
    {
        friend class Renderer;
    protected:
        static std::multimap<priority_type, std::unique_ptr<RenderStageBase>, std::greater<>> m_stages;

    public:

        template<typename StageType CNDOXY(inherits_from<StageType, RenderStage<StageType>> = 0)>
        static void attachStage();

        static void attachStage(std::unique_ptr<RenderStageBase>&& stage);

        virtual void setup(app::window& context) = 0;

        void init(app::window& context) override;

        void shutdown() override;

        void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
    };
}

#include <graphics/pipeline/base/pipeline.inl>
