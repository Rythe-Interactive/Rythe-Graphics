#pragma once
#include <graphics/pipeline/base/pipeline.hpp>

namespace rythe::rendering
{
    class DefaultPipeline : public RenderPipeline<DefaultPipeline>
    {
        virtual void setup(app::window& context) override;
    };
}
