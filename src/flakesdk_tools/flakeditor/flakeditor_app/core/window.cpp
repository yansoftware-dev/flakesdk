#include "window.h"

#include <flake_engine/flake_engine.h>

inline Flake::WindowServer windowServer;

using namespace Flakeditor;

void EditorWindow::create(std::string& name, uint32_t width, uint32_t height, bool maximized)
{   

    Flake::WindowState state;
    if (maximized){state = Flake::WindowState::maximized;}
    else { state = Flake::WindowState::windowed;}

    {
        window.title = name;
        window.width = width;
        window.height = height;
        window.state = state;    
    }

    windowServer.createWindow(window);
}

void EditorWindow::update()
{
    windowServer.updateWindow(window);
}

void EditorWindow::close()
{
    windowServer.closeWindow(window);
}

void EditorWindow::setTitle(std::string& title)
{
    windowServer.changeWindowTitle(title, window);
}

bool EditorWindow::shouldClose()
{
    return windowServer.shouldWindowClose(window);
}

void EditorWindow::setShouldClose(bool value)
{
    windowServer.setWindowShouldClose(window, value);
}