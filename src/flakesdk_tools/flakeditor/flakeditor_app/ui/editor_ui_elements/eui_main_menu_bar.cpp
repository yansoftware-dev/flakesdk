#include "eui_main_menu_bar.h"

#include <any>
#include <flake_engine/flake_engine.h>

inline Flake::GlobalServer globalServer;

using namespace Flakeditor;

void EUIMainMenuBar::handleMainMenuBar()
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Flake")) {
        if (ImGui::MenuItem("Quit", "Alt + End")) {
            globalServer.setVariable("EDITOR_SHOULD_CLOSE", true);
        }
        ImGui::EndMenu();
    } 
    if (ImGui::BeginMenu("Project")) {
        if (ImGui::MenuItem("New Project", "Ctrl + Shift + N")) {
        }
        if (ImGui::MenuItem("Open Project", "Ctrl + Shift + O")) {
        }
        ImGui::EndMenu();
    } 
    if (ImGui::BeginMenu("View")) {

        bool wireframeMode = std::any_cast<bool>(globalServer.getVariable("RENDERER_WIREFRAME_MODE"));
        if (ImGui::Checkbox("Wireframe Mode", &wireframeMode)) {
            if (std::any_cast<bool>(globalServer.getVariable("RENDERER_WIREFRAME_MODE"))) {
                wireframeMode = false;
            } else {
                wireframeMode = true;
            }
            globalServer.setVariable("RENDERER_WIREFRAME_MODE", wireframeMode);
        }

        ImGui::EndMenu();
        
    } 
    if (ImGui::BeginMenu("Editor")) {
        if (ImGui::MenuItem("Editor Settings", "Ctrl + ,")) {
            bool showEditorSettings;
            if (std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_SETTINGS"))) {
                showEditorSettings = false;
            } else {
                showEditorSettings = true;
            }
            globalServer.setVariable("EDITOR_SHOW_SETTINGS", showEditorSettings);
        }
        ImGui::EndMenu();
    } 
    if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("About")) {
            bool showAboutPage;
            if (std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_ABOUT"))) {
                showAboutPage = false;
            } else {
                showAboutPage = true;
            }
            globalServer.setVariable("EDITOR_SHOW_ABOUT", showAboutPage);
        }
        ImGui::EndMenu();
    } 
    ImGui::EndMainMenuBar();
}