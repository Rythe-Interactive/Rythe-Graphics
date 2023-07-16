#include <graphics/pipeline/default/postfx/fxaa.hpp>

namespace rythe::rendering
{
    void FXAA::setup(app::window& context)
    {
        using namespace rythe::core::fs::literals;
        m_fxaaShader = ShaderCache::create_shader("fxaa", "engine://shaders/fxaa.shs"_view);
        addRenderPass<&FXAA::renderPass>();
    }

    void FXAA::renderPass(framebuffer& fbo, RenderPipelineBase* pipeline, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime)
    {
        //Try to get color attachment.
        auto color_attachment = fbo.getAttachment(FRAGMENT_ATTACHMENT);
        if (!std::holds_alternative<texture_handle>(color_attachment)) return;

        //Get color texture.
        auto color_texture = std::get<texture_handle>(color_attachment);

        static id_type texelSizeId = rsl::nameHash("texelSize");
        static id_type blurConstraintId = rsl::nameHash("blurConstraint");
        static id_type reductionScaleId = rsl::nameHash("reductionScale");
        static id_type reductionConstraintId = rsl::nameHash("reductionConstraint");

        fbo.bind();
        m_fxaaShader.bind();

        auto renderSize = color_texture.get_texture().size();
        m_fxaaShader.get_uniform<math::float2>(texelSizeId).set_value(math::float2(1.f / renderSize.x, 1.f / renderSize.y));

        m_fxaaShader.get_uniform<float>(blurConstraintId).set_value(8.f);
        m_fxaaShader.get_uniform<float>(reductionScaleId).set_value(1.f/8.f);
        m_fxaaShader.get_uniform<float>(reductionConstraintId).set_value(1.f/128.f);
        m_fxaaShader.get_uniform_with_location<texture_handle>(SV_SCENECOLOR).set_value(color_texture);

        renderQuad();
        m_fxaaShader.release();
        fbo.release();
        
    }
}
