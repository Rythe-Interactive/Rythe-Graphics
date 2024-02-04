#include <graphics/pipeline/default/stages/clearstage.hpp>

namespace rythe::rendering
{
	void ClearStage::setup(app::window& context)
	{
		app::context_guard guard(context);
		glClearDepth(1.0f);
	}

	void ClearStage::render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime)
	{
		(void)deltaTime;
		(void)camInput;

		static rsl::id_type mainId = rsl::nameHash("main");

		auto fbo = getFramebuffer(mainId);
		if (!fbo)
		{
			log::error("Main frame buffer is missing.");
			abort();
			return;
		}

		app::context_guard guard(context);

		auto [valid, message] = fbo->verify();
		if (!valid)
		{
			log::error("Main frame buffer isn't complete: {}", message);
			abort();
			return;
		}

		fbo->bind();

		rsl::uint attachment = FRAGMENT_ATTACHMENT;
		glDrawBuffers(1, &attachment);

		glClearColor(cam.clearColor.r, cam.clearColor.g, cam.clearColor.b, cam.clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		rsl::uint metaAttachments[3] = {NORMAL_ATTACHMENT, POSITION_ATTACHMENT, OVERDRAW_ATTACHMENT};
		glDrawBuffers(3, metaAttachments);

		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		rsl::uint attachments[4] = {FRAGMENT_ATTACHMENT, NORMAL_ATTACHMENT, POSITION_ATTACHMENT, OVERDRAW_ATTACHMENT};
		glDrawBuffers(4, attachments);

		fbo->release();
	}

	rsl::priority_type ClearStage::priority()
	{
		return setup_priority;
	}
} // namespace rythe::rendering
