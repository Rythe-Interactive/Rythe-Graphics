#pragma once
#include <application/application.hpp>
#include <graphics/components/camera.hpp>
#include <graphics/data/buffer.hpp>
#include <graphics/data/framebuffer.hpp>

#include <any>
#include <memory>

namespace rythe::rendering
{
	class RenderPipelineBase
	{
		friend class Renderer;

	protected:
		sparse_map<rsl::id_type, framebuffer> m_framebuffers;
		sparse_map<rsl::id_type, std::any> m_metadata;

		bool m_abort;

		static std::atomic_bool m_exiting;

	public:
		static void exit();

		void abort();

		template <typename T>
		[[nodiscard]] bool has_meta(const std::string& name);

		template <typename T, typename... Args>
		T* create_meta(const std::string& name, Args&&... args);

		template <typename T>
		[[nodiscard]] T* get_meta(const std::string& name);

		template <typename T>
		[[nodiscard]] bool has_meta(rsl::id_type nameHash);

		template <typename T, typename... Args>
		T* create_meta(rsl::id_type nameHash, Args&&... args);

		template <typename T>
		[[nodiscard]] T* get_meta(rsl::id_type nameHash);

		framebuffer* addFramebuffer(const std::string& name, GLenum target = GL_FRAMEBUFFER);
		[[nodiscard]] bool hasFramebuffer(const std::string& name, GLenum target = GL_FRAMEBUFFER);
		[[nodiscard]] framebuffer* getFramebuffer(const std::string& name);
		framebuffer* addFramebuffer(rsl::id_type nameHash, GLenum target = GL_FRAMEBUFFER);
		[[nodiscard]] bool hasFramebuffer(rsl::id_type nameHash, GLenum target = GL_FRAMEBUFFER);
		[[nodiscard]] framebuffer* getFramebuffer(rsl::id_type nameHash);

		virtual void init(app::window& context) = 0;

		virtual void shutdown();

		virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) = 0;
	};

} // namespace rythe::rendering
