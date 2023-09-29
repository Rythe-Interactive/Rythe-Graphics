#pragma once
#include <graphics/pipeline/base/renderstage.hpp>

namespace rythe::rendering
{
    class ImGuiStage : public RenderStage<ImGuiStage>
    {
    public:
        void setup(app::window& context) override;
        void render(app::window& context, camera& cam, const camera::camera_input& camInput, rsl::span deltaTime) override;
        rsl::priority_type priority() override;

        template <class T,void(T::*Func)(app::window&, camera&, const camera::camera_input&, rsl::span)>
        static void addGuiRender(T* ptr)
        {
            m_onGuiRender.push_back(Func);
        }


    private:

        /** @brief to render imgui things add a function here
         */
        static rsl::multicast_delegate<void(app::window&, camera&, const camera::camera_input&, rsl::span)> m_onGuiRender;
    };
}
