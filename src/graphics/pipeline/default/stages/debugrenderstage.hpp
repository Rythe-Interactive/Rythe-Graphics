#pragma once
#include <graphics/pipeline/base/renderstage.hpp>
#include <graphics/pipeline/base/pipeline.hpp>
#include <graphics/debuggraphics.hpp>

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
        virtual priority_type priority() override;
    };
}
