#include "flake_engine/flake_engine.h"

#include <any>

Flake::WindowServer windowServer;
Flake::RenderServer renderServer;
Flake::UIServer uiServer;
Flake::InputServer inputServer;
Flake::FileServer fileServer;
inline Flake::GlobalServer globalServer;

//------------------------------------\\

Flake::WindowObject mainWindow;
Flake::InputEvent forceQuit;

void forceQuitAction() {
    windowServer.setWindowShouldClose(mainWindow, true);
}

int main(void)
{   
    {
        mainWindow.width = 1280;
        mainWindow.height = 720;
        mainWindow.title = "Flake Editor";
        mainWindow.state = Flake::WindowState::windowed;
    }
    windowServer.createWindow(mainWindow);
    {
        forceQuit.event_name = std::string("force_quit");
        forceQuit.device = Flake::InputDevice::KEYBOARD;
        forceQuit.glfw_key = GLFW_KEY_END;
        forceQuit.mod.alt = true;
        forceQuit.action = forceQuitAction;
    }
    inputServer.addEvent(forceQuit);

    uiServer.ui_init(); 
    uiServer.ui_set_style(Flake::UIStyle::DARK);

    //Set up rendering

    renderServer.initialize();
    renderServer.setRenderMode(Flake::RenderMode::WIREFRAME);

    //Create a mesh with a material
    Datatypes::MeshObject mesh;
    Datatypes::MeshObject mesh2;
    Datatypes::MeshObject mesh3;
    Datatypes::Material material;
    Datatypes::Camera camera;

    //Setup material
    mesh.material = material;
    mesh2.material = material;
    mesh3.material = material;

    //Setup mesh
    mesh2.mesh.makeTriangle();
    mesh.mesh.makeQuad();
    mesh3.mesh.makeTriangle();
    //Add mesh to render queue
    
    renderServer.addToQueue(mesh2);
    renderServer.addToQueue(mesh);
    renderServer.addToQueue(mesh3);

    //Sliders
    bool wir = 0;

    camera.setPosition(0.0f, 0.0f, 1.0f); // Move camera 1 meter back.
    camera.setFieldOfView(90.0f); // Set FOV.
    camera.setFreeCamera(true); // False by default
    camera.setFreeCameraSpeed(2.5f); // Set FreeCam speed
    camera.setFreeCameraSensitivity(0.25f); // Set Sens

    while (!windowServer.shouldWindowClose(mainWindow)) {
        inputServer.processInput(mainWindow.glfw_window);

        camera.update();

        renderServer.setCameraProjection(camera.getProjection());
        renderServer.setCameraTransform(camera.getViewMatrix());
        renderServer.render();

        uiServer.ui_begin();

        ImGui::Begin("Settings");
        ImGui::Checkbox("Wireframe", &wir);
        ImGui::SeparatorText("Camera");
        ImGui::DragFloat3("Position", &camera.position.x, 1.0f, -10.0f, 10.0f);
        ImGui::Separator();
        if (ImGui::Button("Quit")) {
            forceQuitAction();
        }
        ImGui::End();

        uiServer.ui_end();
        windowServer.updateWindow(mainWindow);

        if (wir) { renderServer.setRenderMode(Flake::RenderMode::WIREFRAME); }
        else { renderServer.setRenderMode(Flake::RenderMode::NORMAL); }
    }

    uiServer.ui_destroy();
    windowServer.closeWindow(mainWindow);

    return 0;
}