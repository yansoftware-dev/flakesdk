#include "flakeditor_ui.h"

#include <flake_engine/flake_engine.h>

#include "editor_ui_elements/eui_main_menu_bar.h"
#include "editor_ui_elements/eui_scene_tree.h"
#include "editor_ui_elements/eui_inspector.h"
#include "editor_ui_elements/eui_asset_viewer.h"

#include "editor_ui_elements/eui_editor_settings.h"

inline Flake::UIServer uiServer;

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
    sceneTree.handleSceneTree();
    inspector.handleInspector();
    assetViewer.handleAssetViewer();

    editorSettings.handleEditorSettings();

    uiServer.ui_end();
}   
void EUI::terminate()
{
    uiServer.ui_destroy();
}