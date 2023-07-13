#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>

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

    R_NODISCARD bool RenderStageBase::hasFramebuffer(const std::string& name, GLenum target)
    {
        return m_pipeline->hasFramebuffer(name, target);
    }

    R_NODISCARD framebuffer* RenderStageBase::getFramebuffer(const std::string& name)
    {
        return m_pipeline->getFramebuffer(name);
    }

    framebuffer* RenderStageBase::addFramebuffer(id_type nameHash, GLenum target)
    {
        return m_pipeline->addFramebuffer(nameHash, target);
    }

    R_NODISCARD bool RenderStageBase::hasFramebuffer(id_type nameHash, GLenum target)
    {
        return m_pipeline->hasFramebuffer(nameHash, target);
    }

    R_NODISCARD framebuffer* RenderStageBase::getFramebuffer(id_type nameHash)
    {
        return m_pipeline->getFramebuffer(nameHash);
    }

}
