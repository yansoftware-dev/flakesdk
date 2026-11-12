#pragma once 

#include <flake_engine/flake_engine.h>

namespace Flakeditor
{
    class EUIEditorSettings
    {   public:
        void handleEditorSettings()
        {
            ImGui::Begin("EditorSettings", nullptr, ImGuiWindowFlags_NoDocking);

            // - Implement

            ImGui::End();
        }
    };
}