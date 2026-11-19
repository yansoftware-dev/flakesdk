#include "flake_application.h"

#include <flake_engine/flake_engine.h>

#include "core/window.h"
#include "ui/flakeditor_ui.h"

inline Flake::GlobalServer globalServer;

using namespace Flakeditor;

void start_up_globals();

int FlakeApplication::run()
{   
    start_up_globals();

    EditorWindow window;
    EUI editorUserInterface;

    window.create(std::string("Flakeditor - alpha 0.1"), 1280, 720, true);

    editorUserInterface.initialize();

    while (!window.shouldClose())
    {   
        editorUserInterface.update();
        window.update();
    }

    editorUserInterface.terminate();

    window.close();

    return 0;
}

void start_up_globals()
{
    globalServer.setVariable("EDITOR_SHOW_WELCOME", false);
    globalServer.setVariable("EDITOR_SHOW_SETTINGS", false);
    globalServer.setVariable("EDITOR_SHOW_NEW_PROJECT", true);
    globalServer.setVariable("EDITOR_SHOW_OPEN_PROJECT", true);

    globalServer.setVariable("EDITOR_SHOW_ABOUT", false);
    globalServer.setVariable("EDITOR_SHOW_SCENE_TREE", true);
    globalServer.setVariable("EDITOR_SHOW_ASSET_VIEWER", true);
    globalServer.setVariable("EDITOR_SHOW_INSPECTOR", true);

    globalServer.setVariable("EDITOR_COLOR_THEME", 0);
}
