#include "eui_editor_about.h"

#include <flake_engine/flake_engine.h>

inline Flake::GlobalServer globalServer;

using namespace Flakeditor;

void EUIAboutPage::handleAboutPage()
{
    bool show = true;
    show = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_ABOUT"));
    
    ImGui::Begin("About", &show, ImGuiWindowFlags_NoDocking);  
    ImGui::Text("The Flake editor is an editor!");
    ImGui::End();

    globalServer.setVariable("EDITOR_SHOW_ABOUT", show);
}