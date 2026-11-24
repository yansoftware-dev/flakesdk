#include "shortcuts.h"

#include <flake_engine/flake_engine.h>
#include <any>

inline Flake::GlobalServer globalServer;
inline Flake::InputServer inputServer;

using namespace Flakeditor;


///---------

void event_quit() { globalServer.setVariable("EDITOR_SHOULD_CLOSE", true); }
void event_editor_settings() { globalServer.setVariable("EDITOR_SHOW_SETTINGS", true); }

///---------

void EditorShortcuts::initialize_shortcuts()
{
    Flake::InputEvent e_quit;
    {
        e_quit.event_name = "Quit";
        e_quit.device = Flake::InputDevice::KEYBOARD;
        e_quit.glfw_key = GLFW_KEY_END;
        e_quit.mod.alt = true;
        e_quit.action = event_quit;
    }
    Flake::InputEvent e_editor_settings;                        
    {                                                    
        e_editor_settings.event_name = "EditorSettings";                  
        e_editor_settings.device = Flake::InputDevice::KEYBOARD;
        e_editor_settings.glfw_key = GLFW_KEY_COMMA;              
        e_editor_settings.mod.alt = true;                   
        e_editor_settings.action = event_editor_settings;                        
    }
    
    inputServer.addEvent(e_quit);
    inputServer.addEvent(e_editor_settings);
}