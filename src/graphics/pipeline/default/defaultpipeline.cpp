#include <graphics/pipeline/default/defaultpipeline.hpp>
#include <graphics/pipeline/default/stages/clearstage.hpp>
#include <graphics/pipeline/default/stages/framebufferresizestage.hpp>
#include <graphics/pipeline/default/stages/lightbufferstage.hpp>
#include <graphics/pipeline/default/stages/meshbatchingstage.hpp>
#include <graphics/pipeline/default/stages/meshrenderstage.hpp>
#include <graphics/pipeline/default/stages/transparencyrenderstage.hpp>
#include <graphics/pipeline/default/stages/debugrenderstage.hpp>
#include <graphics/pipeline/default/stages/postprocessingstage.hpp>
#include <graphics/pipeline/default/stages/submitstage.hpp>
#include <graphics/pipeline/default/postfx/tonemapping.hpp>
#include <graphics/pipeline/default/postfx/fxaa.hpp>
#include <graphics/pipeline/default/postfx/bloom.hpp>
#include <graphics/pipeline/default/postfx/depthoffield.hpp>
#include <graphics/pipeline/default/postfx/skybox.hpp>
#include <graphics/data/buffer.hpp>


namespace rythe::rendering
{
    void DefaultPipeline::setup(app::window& context)
    {
        attachStage<ClearStage>();
        attachStage<FramebufferResizeStage>();
        attachStage<LightBufferStage>();
        attachStage<MeshBatchingStage>();
        attachStage<MeshRenderStage>();
        attachStage<TransparencyRenderStage>();
        attachStage<DebugRenderStage>();
        attachStage<PostProcessingStage>();
        attachStage<SubmitStage>();

        PostProcessingStage::addEffect<Skybox>();
        PostProcessingStage::addEffect<DepthOfField>(-10);
        PostProcessingStage::addEffect<Bloom>(-15);
        PostProcessingStage::addEffect<Tonemapping>(-32);
        PostProcessingStage::addEffect<FXAA>(-64);


        buffer modelMatrixBuffer;

        {
            app::context_guard guard(context);
            addFramebuffer("main");
            modelMatrixBuffer = buffer(GL_ARRAY_BUFFER, sizeof(math::float4x4) * 1024, nullptr, GL_DYNAMIC_DRAW);
        }

        create_meta<buffer>("model matrix buffer", modelMatrixBuffer);
    }

}
