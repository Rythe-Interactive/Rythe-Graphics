#pragma once
#include <graphics/data/vertexarray.hpp>
#include <graphics/data/buffer.hpp>


#include <graphics/data/framebuffer.hpp>
#include <graphics/data/shader.hpp>

#include <graphics/data/screen_quad.hpp>

#include <graphics/pipeline/base/pipelinebase.hpp>

namespace rythe::rendering
{
    class PostProcessingEffectBase
    {
    public:
        std::vector<rsl::delegate<void(framebuffer&, RenderPipelineBase*, camera&, const camera::camera_input&, rsl::span)>> renderPasses;
        virtual rsl::id_type getId() const = 0;
        virtual const std::string& getName() const = 0;
        void init(app::window& context)
        {
            m_initialized = true;
            m_quad = screen_quad(nullptr);
            setup(context);
        }

        bool isInitialized() const { return m_initialized; }

    protected:
        virtual void setup(app::window& context) = 0;
        void renderQuad()
        {
            m_quad.render();
        }
    private:
        bool m_initialized = false;
        screen_quad m_quad;
    };

    struct framebuffer;
    /**
     * @class PostProcessingEffect
     * @brief A base class for post processing effect.
     */

    template<typename Self>
    class PostProcessingEffect : public PostProcessingEffectBase
    {
    public:
        virtual rsl::id_type getId() const override { return id; }
        virtual const std::string& getName() const override { return name; }
        static const rsl::id_type id;
        static const std::string name;

    protected:
        template<void(Self::* func_type)(framebuffer&, RenderPipelineBase* ,camera&, const camera::camera_input&, rsl::span)>
        void addRenderPass()
        {
            auto temp = rsl::delegate<void(framebuffer&, RenderPipelineBase*, camera&, const camera::camera_input&, rsl::span)>::template create<Self, func_type>(*reinterpret_cast<Self*>(this));
            renderPasses.push_back(rsl::force_cast<rsl::delegate<void(framebuffer&, RenderPipelineBase*, camera&, const camera::camera_input&, rsl::span)>>(temp));
        }
    };

    template<typename Self>
    const rsl::id_type PostProcessingEffect<Self>::id = rsl::typeHash<Self>();

    template<typename Self>
    const std::string PostProcessingEffect<Self>::name = rsl::nameOfType<Self>();

}
