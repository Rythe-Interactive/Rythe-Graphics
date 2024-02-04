#pragma once
#include <application/application.hpp>
#include <graphics/components/camera.hpp>
#include <graphics/pipeline/base/pipelinebase.hpp>

#define setup_priority 64
#define opaque_priority 32
//      default_priority 0
#define transparent_priority -16
#define volumetric_priority -32
#define post_fx_priority -48
#define ui_priority -64
#define submit_priority -96

namespace rythe::rendering
{
	class RenderPipelineBase;

	class RenderStageBase
	{
		friend class Renderer;

		template <typename>
		friend class RenderPipeline;

	private:
		bool m_isInitialized = false;

	protected:
		virtual void setup(app::window& context) = 0;

		virtual void _shutdown_impl() = 0;

	public:
		static RenderPipelineBase* m_pipeline;

		bool isInitialized() { return m_isInitialized; }

		void init(app::window& context)
		{
			m_isInitialized = true;
			setup(context);
		}

		virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) = 0;
		virtual rsl::priority_type priority() { return default_priority; }

	protected:
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
	};

	template <typename SelfType>
	class RenderStage : public RenderStageBase, protected System<SelfType>
	{
		void _shutdown_impl() override
		{
			if constexpr (rsl::has_shutdown_v<SelfType, void()>)
			{
				static_cast<SelfType*>(this)->shutdown();
			}
		}
	};
} // namespace rythe::rendering

#include <graphics/pipeline/base/renderstage.inl>
