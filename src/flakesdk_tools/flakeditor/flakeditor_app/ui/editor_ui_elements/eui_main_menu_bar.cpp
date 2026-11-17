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
            //Quit
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

        }

        ImGui::EndMenu();
    } 
    ImGui::EndMainMenuBar();
}