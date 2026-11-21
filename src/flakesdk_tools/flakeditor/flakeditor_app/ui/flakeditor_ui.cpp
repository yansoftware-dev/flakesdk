#include "flakeditor_ui.h"

#include <flake_engine/flake_engine.h>
#include <any>

#include "editor_ui_elements/eui_main_menu_bar.h"
#include "editor_ui_elements/eui_scene_tree.h"
#include "editor_ui_elements/eui_inspector.h"
#include "editor_ui_elements/eui_asset_viewer.h"

#include "editor_ui_elements/eui_editor_settings.h"
#include "editor_ui_elements/eui_editor_about.h"

inline Flake::UIServer uiServer;
inline Flake::GlobalServer globalServer;
inline Flake::OutputServer outputServer;

using namespace Flakeditor;

EUIMainMenuBar mainMenuBar;
EUISceneTree sceneTree;
EUIInspector inspector;
EUIAssetViewer assetViewer;

EUIEditorSettings editorSettings;
EUIAboutPage aboutPage;

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
    unsigned int editor_theme = std::any_cast<int>(globalServer.getVariable("EDITOR_COLOR_THEME"));
    bool windowAbout = std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOW_ABOUT"));

    if (panelsSceneTree)
       sceneTree.handleSceneTree();
    if (panelsInspector)
        inspector.handleInspector();
    if (panelsAssetViewer)
        assetViewer.handleAssetViewer();

    if (windowEditorSettings)
        editorSettings.handleEditorSettings();

    if (windowAbout)
        aboutPage.handleAboutPage();

    if (editor_theme == 0) ImGui::StyleColorsDark();
    else if (editor_theme == 1) ImGui::StyleColorsLight();
    else if (editor_theme == 2) ImGui::StyleColorsClassic();
    else outputServer.printErr("Unknown editor theme!");

    uiServer.ui_end();
}   
void EUI::terminate()
{
    uiServer.ui_destroy();
}