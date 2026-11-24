#include "flake_application.h"

#include <flake_engine/flake_engine.h>

#include "core/window.h"
#include "ui/flakeditor_ui.h"
#include "input/editor_input.h"

inline Flake::GlobalServer globalServer;
inline Flake::InputServer inputServer;
inline Flake::RenderServer renderServer;

using namespace Flakeditor;

inline EditorInputManager editorInputManager;

void start_up_globals();

int FlakeApplication::run()
{   
    start_up_globals();
    editorInputManager.initialize();

    EditorWindow window;
    EUI editorUserInterface;

    window.create(std::string("Flakeditor - alpha 0.1"), 1280, 720, true);

    editorUserInterface.initialize();

    Datatypes::Mesh mesh;
    Datatypes::MeshObject object;
    Datatypes::Material material;
    Datatypes::Shader shader;
    Datatypes::Camera camera;
    camera.setFreeCamera(true);
    
    mesh.makeCube();
    Flake::File shaderVert;
    Flake::File shaderFrag;

    shaderVert.path = "src/flake_engine/graphics/shaders/default_vertex_shader.glsl";
    shaderFrag.path = "src/flake_engine/graphics/shaders/default_fragment_shader.glsl";

    shader.fragment_shader_file = shaderFrag;
    shader.vertex_shader_file = shaderVert;
    shader.load();

    material.shader = shader;

    object.mesh = mesh;
    object.material = material;

    renderServer.initialize();

    renderServer.addToQueue(object);

    while (!window.shouldClose())
    {   
        editorUserInterface.update();
        editorInputManager.update();
        window.update();

        camera.update();
        renderServer.setCameraProjection(camera.getProjection());
        renderServer.setCameraTransform(camera.getViewMatrix());
        if (std::any_cast<bool>(globalServer.getVariable("RENDERER_WIREFRAME_MODE"))) {
            renderServer.setRenderMode(Flake::RenderMode::WIREFRAME);
        } else {
            renderServer.setRenderMode(Flake::RenderMode::NORMAL);
        }
        renderServer.render();

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

    globalServer.setVariable("RENDERER_WIREFRAME_MODE", false);
}