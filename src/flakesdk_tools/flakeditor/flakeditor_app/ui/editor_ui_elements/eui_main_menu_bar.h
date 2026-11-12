#pragma once 

#include <flake_engine/flake_engine.h>

namespace Flakeditor
{
    class EUIMainMenuBar
    {   public:
        void handleMainMenuBar()
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
    };
}