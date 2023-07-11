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
        std::vector<delegate<void(framebuffer&, RenderPipelineBase*, camera&, const camera::camera_input&, rsl::span)>> renderPasses;
        virtual id_type getId() const RYTHE_PURE;
        virtual const std::string& getName() const RYTHE_PURE;
        void init(app::window& context)
        {
            m_initialized = true;
            m_quad = screen_quad(nullptr);
            setup(context);
        }

        bool isInitialized() const { return m_initialized; }

    protected:
        virtual void setup(app::window& context) RYTHE_PURE;
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
        virtual id_type getId() const override { return id; }
        virtual const std::string& getName() const override { return name; }
        static const id_type id;
        static const std::string name;

    protected:
        template<void(Self::* func_type)(framebuffer&, RenderPipelineBase* ,camera&, const camera::camera_input&, rsl::span)>
        void addRenderPass()
        {
            renderPasses.push_back(delegate<void(framebuffer&, RenderPipelineBase*, camera&, const camera::camera_input&, rsl::span)>::from<Self, func_type>(reinterpret_cast<Self*>(this)));
        }
    };

    template<typename Self>
    const id_type PostProcessingEffect<Self>::id = typeHash<Self>();

    template<typename Self>
    const std::string PostProcessingEffect<Self>::name = nameOfType<Self>();

}
