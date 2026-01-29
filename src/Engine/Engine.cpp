//
// Created by Tristan on 1/28/26.
//

#include "../../include/Engine/Engine.h"
#include <raylib.h>

Engine::Engine() {
    this->initializeWindow();
    this->initializeAudioDevice();
    this->camera = initialCamera();
}

void Engine::loop() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
    CloseWindow();
}

void Engine::draw() const {
    BeginDrawing();
    ClearBackground(BLACK);
    this->drawCamera();
    DrawFPS(10,10);
    EndDrawing();
}

void Engine::update() {
    player.update(&camera);
}

Camera3D Engine::initialCamera() {
    Camera3D initialCam = { 0 };
    initialCam.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    initialCam.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    initialCam.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    initialCam.fovy = 45.0f;                                // Camera field-of-view Y
    initialCam.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    return initialCam;
}

void Engine::drawCamera() const {
    BeginMode3D(this->camera);
        Renderer::drawBlock(block);
    EndMode3D();
}

void Engine::initializeWindow() const {
    InitWindow(settings.screenWidth, settings.screenHeight, "Minecraft Clone");
    SetTargetFPS(settings.frameRate);
    HideCursor();
    DisableCursor();

}

void Engine::initializeAudioDevice() const {
    InitAudioDevice();
}
