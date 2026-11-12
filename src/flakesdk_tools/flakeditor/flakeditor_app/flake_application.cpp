#include "flake_application.h"

#include <flake_engine/flake_engine.h>

#include "core/window.h"
#include "ui/flakeditor_ui.h"

using namespace Flakeditor;

int FlakeApplication::run()
{   
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