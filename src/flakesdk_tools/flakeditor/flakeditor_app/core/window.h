#pragma once 

#include <string>
#include <flake_engine/flake_engine.h>

namespace Flakeditor 
{
    class EditorWindow
    {
    public:
        void create(std::string& name, uint32_t width, uint32_t height, bool maximized);
        void update();
        void close();
        void setTitle(std::string& title);

        bool shouldClose();
        void setShouldClose(bool value);
    private:
        Flake::WindowObject window;
    };
}