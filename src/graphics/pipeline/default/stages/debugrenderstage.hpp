#pragma once
#include <graphics/debuggraphics.hpp>
#include <graphics/pipeline/base/pipeline.hpp>
#include <graphics/pipeline/base/renderstage.hpp>

namespace rythe::rendering
{
	class DebugRenderStage : public RenderStage<DebugRenderStage>
	{
	private:
		static async::spinlock debugLinesLock;
		static thread_local std::unordered_set<debug::debug_line_event>* localLines;
		static std::unordered_map<std::thread::id, std::unordered_set<debug::debug_line_event>*> debugLines;

	public:
		static void startDebugDomain();
		static void endDebugDomain();

		void drawDebugLine(events::event_base& event);

		virtual void setup(app::window& context) override;
		virtual void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
		virtual rsl::priority_type priority() override;
	};
} // namespace rythe::rendering
