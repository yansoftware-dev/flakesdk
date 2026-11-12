#pragma once 

#include <flake_engine/flake_engine.h>

namespace Flakeditor
{
    class EUIInspector
    {   public:
        void handleInspector()
        {
            ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoCollapse);

            // - Implement

            ImGui::End();
        }
    };
}