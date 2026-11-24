#include "editor_input.h"
#include "shortcuts/shortcuts.h"

#include <flake_engine/flake_engine.h>

inline Flake::InputServer inputServer;

using namespace Flakeditor;

inline EditorShortcuts editorShortcuts;

void EditorInputManager::initialize()
{
    editorShortcuts.initialize_shortcuts();
}

void EditorInputManager::update()
{
    inputServer.processInput(glfwGetCurrentContext());
}