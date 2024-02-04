#include <graphics/pipeline/base/pipelinebase.hpp>

namespace rythe::rendering
{
	std::atomic_bool RenderPipelineBase::m_exiting = {false};

	void RenderPipelineBase::exit()
	{
		m_exiting.store(true, std::memory_order_release);
	}

	void RenderPipelineBase::abort()
	{
		m_abort = true;
	}

	framebuffer* RenderPipelineBase::addFramebuffer(const std::string& name, GLenum target)
	{
		rsl::id_type id = rsl::nameHash(name);

		if (m_framebuffers.contains(id))
		{
			if (m_framebuffers[id].target() == target)
				return &m_framebuffers[id];
			else
				return nullptr;
		}

		m_framebuffers[id] = framebuffer(target);

		return &m_framebuffers[id];
	}

	[[nodiscard]] bool RenderPipelineBase::hasFramebuffer(const std::string& name, GLenum target)
	{
		rsl::id_type id = rsl::nameHash(name);
		return m_framebuffers.contains(id) && m_framebuffers[id].target() == target;
	}

	[[nodiscard]] framebuffer* RenderPipelineBase::getFramebuffer(const std::string& name)
	{
		rsl::id_type id = rsl::nameHash(name);
		if (m_framebuffers.contains(id))
			return &m_framebuffers[id];
		return nullptr;
	}

	framebuffer* RenderPipelineBase::addFramebuffer(rsl::id_type nameHash, GLenum target)
	{
		if (m_framebuffers.contains(nameHash))
		{
			if (m_framebuffers[nameHash].target() == target)
				return &m_framebuffers[nameHash];
			else
				return nullptr;
		}

		m_framebuffers[nameHash] = framebuffer(target);

		return &m_framebuffers[nameHash];
	}

	[[nodiscard]] bool RenderPipelineBase::hasFramebuffer(rsl::id_type nameHash, GLenum target)
	{
		return m_framebuffers.contains(nameHash) && m_framebuffers[nameHash].target() == target;
	}

	[[nodiscard]] framebuffer* RenderPipelineBase::getFramebuffer(rsl::id_type nameHash)
	{
		if (m_framebuffers.contains(nameHash))
			return &m_framebuffers[nameHash];
		return nullptr;
	}

	void RenderPipelineBase::shutdown()
	{
		m_framebuffers.clear();
		m_metadata.clear();
		m_abort = false;
		m_exiting.store(false, std::memory_order_relaxed);
	}

} // namespace rythe::rendering
