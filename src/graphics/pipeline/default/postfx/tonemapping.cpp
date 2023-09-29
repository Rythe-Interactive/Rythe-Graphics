#include <graphics/pipeline/default/postfx/tonemapping.hpp>

namespace rythe::rendering
{
    std::atomic<rsl::id_type> Tonemapping::m_currentShader = { rsl::nameHash("aces tonemapping") };
    std::atomic_bool Tonemapping::m_autoExposure = { false };
    std::atomic<float> Tonemapping::m_exposure = { 2.f };

    void Tonemapping::setAlgorithm(tonemapping_type type) noexcept
    {
        static rsl::id_type acesId = rsl::nameHash("aces tonemapping");
        static rsl::id_type reinhardId = rsl::nameHash("reinhard tonemapping");
        static rsl::id_type reinhardJodieId = rsl::nameHash("reinhard jodie tonemapping");
        static rsl::id_type rytheId = rsl::nameHash("rythe tonemapping");
        static rsl::id_type unreal3Id = rsl::nameHash("unreal3 tonemapping");

        switch (type)
        {
        case tonemapping_type::aces:
            m_currentShader.store(acesId, std::memory_order_relaxed);
            break;
        case tonemapping_type::reinhard:
            m_currentShader.store(reinhardId, std::memory_order_relaxed);
            break;
        case tonemapping_type::reinhard_jodie:
            m_currentShader.store(reinhardJodieId, std::memory_order_relaxed);
            break;
        case tonemapping_type::rythe:
            m_currentShader.store(rytheId, std::memory_order_relaxed);
            break;
        case tonemapping_type::unreal3:
            m_currentShader.store(unreal3Id, std::memory_order_relaxed);
            break;
        default:
            m_currentShader.store(rytheId, std::memory_order_relaxed);
            break;
        }
    }

    void Tonemapping::enableAutoExposure(bool enable) noexcept
    {
        m_autoExposure.store(enable, std::memory_order_relaxed);
    }

    void Tonemapping::setExposure(float value) noexcept
    {
        m_exposure.store(value, std::memory_order_relaxed);
    }

    void Tonemapping::setup(app::window& context)
    {
        using namespace rythe::core::fs::literals;
        rendering::ShaderCache::create_shader("aces tonemapping", "engine://shaders/aces.shs"_view);
        rendering::ShaderCache::create_shader("reinhard tonemapping", "engine://shaders/reinhard.shs"_view);
        rendering::ShaderCache::create_shader("reinhard jodie tonemapping", "engine://shaders/reinhardjodie.shs"_view);
        rendering::ShaderCache::create_shader("rythe tonemapping", "engine://shaders/rythetonemap.shs"_view);
        rendering::ShaderCache::create_shader("unreal3 tonemapping", "engine://shaders/unreal3.shs"_view);
        addRenderPass<&Tonemapping::renderPass>();
    }

    void Tonemapping::renderPass(framebuffer& fbo, RenderPipelineBase* pipeline, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime)
    {
        //Try to get color attachment.
        auto color_attachment = fbo.getAttachment(FRAGMENT_ATTACHMENT);
        if (!std::holds_alternative<texture_handle>(color_attachment)) return;

        //Get color texture.
        auto color_texture = std::get<texture_handle>(color_attachment);

        static rsl::id_type exposureId = rsl::nameHash("exposure");

        auto exposure = m_exposure.load(std::memory_order_relaxed);
        auto doAutoExposure = m_autoExposure.load(std::memory_order_relaxed);
        static bool firstFrame = true;
        static rsl::id_type historyMetaId = rsl::nameHash("scene color history");
        texture_handle* historyTexture = pipeline->get_meta<texture_handle>(historyMetaId);

        if (doAutoExposure)
        {
            // Exposure here takes 6ms... including the mipmap generation at the end. needs to be replaced with gpu downsample and gpu exposure remixing.
            // If all of this is on gpu then it doesn't require a gpu-cpu sync and a gpu vram to cpu ram fetch.
            if (historyTexture && !firstFrame)
            {
                auto tex = historyTexture->get_texture();
                auto size = tex.size();

                rsl::size_type maxMip = log2(math::max(size.x, size.y));

                static std::vector<math::color> colors = { math::color() };


                glBindTexture(static_cast<GLenum>(tex.type), tex.textureId);
                glGetTexImage(static_cast<GLenum>(tex.type), maxMip, components_to_format[static_cast<int>(tex.channels)], GL_FLOAT, colors.data());
                glBindTexture(static_cast<GLenum>(tex.type), 0);


                float luminance = math::dot(rsl::math::float3(colors[0].r, colors[0].g, colors[0].b), rsl::math::float3(0.2126f, 0.7152f, 0.0722f));

                float newExposure = math::clamp(math::pow(math::max((1.0f - luminance), 0.f), 2.2f) * 10.f, 0.f, 10.f);

                if (newExposure < exposure)
                    exposure = math::lerp(exposure, newExposure, deltaTime.seconds());
                else
                    exposure = math::lerp(exposure, newExposure, deltaTime.seconds() * 0.5f);

                m_exposure.store(exposure, std::memory_order_relaxed);
            }
            else
                firstFrame = false;
        }

        auto shader = ShaderCache::get_handle(m_currentShader.load(std::memory_order_relaxed));

        fbo.bind();
        shader.bind();

        shader.get_uniform<float>(exposureId).set_value(exposure);

        shader.get_uniform_with_location<texture_handle>(SV_SCENECOLOR).set_value(color_texture);
        renderQuad();
        shader.release();
        fbo.release();

        if (doAutoExposure)
            if (historyTexture && !firstFrame)
                glGenerateTextureMipmap(historyTexture->get_texture().textureId);
    }
}
