#include "eui_editor_settings.h"

#include <flake_engine/flake_engine.h>
#include <any>

inline Flake::GlobalServer globalServer;

using namespace Flakeditor;

bool panelsSceneTree = false;
bool panelsAssetViewer = false;
bool panelsInspector = false;

bool show = false;

void EUIEditorSettings::handleEditorSettings()
{   
    panelsSceneTree = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_SCENE_TREE"));
    panelsAssetViewer = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_ASSET_VIEWER"));
    panelsInspector = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_INSPECTOR"));

    show = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_SETTINGS"));

    ImGui::Begin("EditorSettings", &show, ImGuiWindowFlags_NoDocking);
    ImGui::SeparatorText("Editor-Panels");
    ImGui::Checkbox("Scene-Tree panel", &panelsSceneTree);
    ImGui::Checkbox("Asset-Viewer panel", &panelsAssetViewer);
    ImGui::Checkbox("Inspector panel", &panelsInspector);
    ImGui::End();

    globalServer.setVariable("EDITOR_SHOW_SCENE_TREE", panelsSceneTree);
    globalServer.setVariable("EDITOR_SHOW_ASSET_VIEWER", panelsAssetViewer);
    globalServer.setVariable("EDITOR_SHOW_INSPECTOR", panelsInspector);

    globalServer.setVariable("EDITOR_SHOW_SETTINGS", show);
}