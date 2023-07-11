#pragma once
#include <graphics/data/framebuffer.hpp>
#include <graphics/data/buffer.hpp>
#include <graphics/components/camera.hpp>
#include <application/application.hpp>

#include <memory>
#include <any>

namespace rythe::rendering
{
    class RenderPipelineBase
    {
        friend class Renderer;
    protected:
        sparse_map<id_type, framebuffer> m_framebuffers;
        sparse_map<id_type, std::any> m_metadata;

        bool m_abort;

        static std::atomic_bool m_exiting;

    public:
        static void exit();

        void abort();

        template<typename T>
        R_NODISCARD bool has_meta(const std::string& name);

        template<typename T, typename... Args>
        T* create_meta(const std::string& name, Args&&... args);

        template<typename T>
        R_NODISCARD T* get_meta(const std::string& name);

        template<typename T>
        R_NODISCARD bool has_meta(id_type nameHash);

        template<typename T, typename... Args>
        T* create_meta(id_type nameHash, Args&&... args);

        template<typename T>
        R_NODISCARD T* get_meta(id_type nameHash);

        framebuffer* addFramebuffer(const std::string& name, GLenum target = GL_FRAMEBUFFER);
        R_NODISCARD bool hasFramebuffer(const std::string& name, GLenum target = GL_FRAMEBUFFER);
        R_NODISCARD framebuffer* getFramebuffer(const std::string& name);
        framebuffer* addFramebuffer(id_type nameHash, GLenum target = GL_FRAMEBUFFER);
        R_NODISCARD bool hasFramebuffer(id_type nameHash, GLenum target = GL_FRAMEBUFFER);
        R_NODISCARD framebuffer* getFramebuffer(id_type nameHash);

        virtual void init(app::window& context) RYTHE_PURE;

        virtual void shutdown();

        virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) RYTHE_PURE;
    };

}
