#include "flake_application.h"

#include <flake_engine/flake_engine.h>

#include "core/window.h"
#include "ui/flakeditor_ui.h"

inline Flake::GlobalServer globalServer;
inline Flake::InputServer inputServer;

using namespace Flakeditor;

void start_up_globals();
void start_up_shortcuts();

void quit()
{
    globalServer.setVariable("EDITOR_SHOULD_CLOSE", true);
}

int FlakeApplication::run()
{   
    start_up_globals();
    start_up_shortcuts();

    EditorWindow window;
    EUI editorUserInterface;

    window.create(std::string("Flakeditor - alpha 0.1"), 1280, 720, true);

    editorUserInterface.initialize();

    while (!window.shouldClose())
    {   
        editorUserInterface.update();
        inputServer.processInput(glfwGetCurrentContext());
        window.update();

        if (std::any_cast<bool>(globalServer.getVariable("EDITOR_SHOULD_CLOSE"))) 
        {
            window.setShouldClose(true);
        }
    }

    editorUserInterface.terminate();

    window.close();

    return 0;
}

void start_up_globals()
{   
    globalServer.setVariable("EDITOR_SHOULD_CLOSE", false);

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

void open_editor_settings() { globalServer.setVariable("EDITOR_SHOW_SETTINGS", true); }

void start_up_shortcuts()
{
    Flake::InputEvent event_quit;
    {
        event_quit.event_name = "Quit";
        event_quit.device = Flake::InputDevice::KEYBOARD;
        event_quit.glfw_key = GLFW_KEY_END;
        event_quit.mod.alt = true;
        event_quit.action = quit;
    }

    Flake::InputEvent event_editor_settings;                        
    {                                                    
        event_editor_settings.event_name = "EditorSettings";                  
        event_editor_settings.device = Flake::InputDevice::KEYBOARD;
        event_editor_settings.glfw_key = GLFW_KEY_COMMA;              
        event_editor_settings.mod.ctrl = true;                       
        event_editor_settings.action = open_editor_settings;                        
    }                                                    

    inputServer.addEvent(event_quit);
    inputServer.addEvent(event_editor_settings);
}