#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "Camera.h"
#include "Graphics.h"
#include "Player.h"
#include "Scene.h"
#include "Time.h"
#include "SphereRender.h"
#include "PlaneRender.h"

bool GameCycle()
{
    if (Input::GetKeyDown(Input::Key::Escape))
        return false;

    Scene::current->Update();

    Screen::SetTitle("Console 3D - FPS: " + std::to_string(1 / Time::GetDeltaTime()));

    Graphics::RenderOnScreen();

    Time::Update();

    return true;
}

int main()
{
    Vector2i screenResolution = Vector2i(100, 30);

    Screen::Set(screenResolution.x(), screenResolution.y());
    Screen::SetTitle("Console 3D");
    Screen::HideCursor();

    Scene currentScene = Scene();

    float aspectRatio = (float)Screen::GetPixelSize().x() / Screen::GetPixelSize().y();
    Camera mainCamera = Camera(60, aspectRatio, 1000);

    Player player(mainCamera);
    player.SetPosition(Vector3f(0, 1, 0));
    currentScene.Add(player);

    Graphics::PathTracing::Material mat1 =
    {
        Vector3f(0.3f, 0.3f, 0),
        Vector3f::Constant(0.5f),
        0.5f
    };

    Graphics::PathTracing::Material mat2 =
    {
        Vector3f::Constant(0),
        Vector3f(1, 1, 1),
        1
    };

    Graphics::PathTracing::SphereRender sphere1(Vector3f(1.5f, 1, -3), 1, mat1);
    Graphics::PathTracing::SphereRender sphere2(Vector3f(-1, 1, -3), 1, mat2);
    currentScene.Add(sphere1);
    currentScene.Add(sphere2);

    Graphics::PathTracing::PlaneRender groundPlane(Vector3f::UnitY(), 0, mat1);
    currentScene.Add(groundPlane);

    Graphics::Init();
    Input::Start();
    Time::Start();
    currentScene.Start();

    bool gameIsRun = true;

    while (gameIsRun)
    {
        gameIsRun = GameCycle();

        if (gameIsRun == false)
            break;

        while (!_kbhit())
        {
            Input::Clear();

            gameIsRun = GameCycle();

            if (gameIsRun == false)
                break;
        }

        Input::Update();
        //std::cout << (int)Input::GetInput() << '\t';
    }

    return 0;
}
