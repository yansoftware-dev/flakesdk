#include "flakeditor_ui.h"

#include <flake_engine/flake_engine.h>
#include <any>

#include "editor_ui_elements/eui_main_menu_bar.h"
#include "editor_ui_elements/eui_scene_tree.h"
#include "editor_ui_elements/eui_inspector.h"
#include "editor_ui_elements/eui_asset_viewer.h"

#include "editor_ui_elements/eui_editor_settings.h"

inline Flake::UIServer uiServer;
inline Flake::GlobalServer globalServer;

using namespace Flakeditor;

EUIMainMenuBar mainMenuBar;
EUISceneTree sceneTree;
EUIInspector inspector;
EUIAssetViewer assetViewer;

EUIEditorSettings editorSettings;

void EUI::initialize()
{
    uiServer.ui_init();
}
void EUI::update()
{
    uiServer.ui_begin();

    mainMenuBar.handleMainMenuBar();

    bool panelsSceneTree = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_SCENE_TREE"));
    bool panelsAssetViewer = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_ASSET_VIEWER"));
    bool panelsInspector = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_INSPECTOR"));

    bool windowEditorSettings = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_SETTINGS"));

    if (panelsSceneTree)
       sceneTree.handleSceneTree();
    if (panelsInspector)
        inspector.handleInspector();
    if (panelsAssetViewer)
        assetViewer.handleAssetViewer();

    if (windowEditorSettings)
        editorSettings.handleEditorSettings();

    uiServer.ui_end();
}   
void EUI::terminate()
{
    uiServer.ui_destroy();
}