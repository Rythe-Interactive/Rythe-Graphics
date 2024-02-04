#include <graphics/pipeline/base/pipeline.hpp>
#include <graphics/pipeline/base/renderstage.hpp>

namespace rythe::rendering
{
	RenderPipelineBase* RenderStageBase::m_pipeline;

	void RenderStageBase::abort()
	{
		m_pipeline->abort();
	}

	framebuffer* RenderStageBase::addFramebuffer(const std::string& name, GLenum target)
	{
		return m_pipeline->addFramebuffer(name, target);
	}

	[[nodiscard]] bool RenderStageBase::hasFramebuffer(const std::string& name, GLenum target)
	{
		return m_pipeline->hasFramebuffer(name, target);
	}

	[[nodiscard]] framebuffer* RenderStageBase::getFramebuffer(const std::string& name)
	{
		return m_pipeline->getFramebuffer(name);
	}

	framebuffer* RenderStageBase::addFramebuffer(rsl::id_type nameHash, GLenum target)
	{
		return m_pipeline->addFramebuffer(nameHash, target);
	}

	[[nodiscard]] bool RenderStageBase::hasFramebuffer(rsl::id_type nameHash, GLenum target)
	{
		return m_pipeline->hasFramebuffer(nameHash, target);
	}

	[[nodiscard]] framebuffer* RenderStageBase::getFramebuffer(rsl::id_type nameHash)
	{
		return m_pipeline->getFramebuffer(nameHash);
	}

} // namespace rythe::rendering
