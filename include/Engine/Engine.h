//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_ENGINE_H
#define MINECRAFTCLONE_ENGINE_H
#include <raylib.h>

#include "Player.hpp"
#include "Settings.hpp"
#include "../World/Block.hpp"
#include "Renderer.hpp"


class Engine {
    public:
    Engine();

    void loop();

private: // Engine Functions

    void draw() const;
    void update();

    void drawCamera() const;

    private: // Initializers
    Camera3D initialCamera();
    void initializeWindow() const;
    void initializeAudioDevice() const;

    private: // variables
    Player player = Player();
    Camera3D camera = Renderer::getCamera();
    Settings settings = Settings::getInstance();
    Block block = {
        {0,0,0},
        {1,1,1,},
        GREEN
    };
};


#endif //MINECRAFTCLONE_ENGINE_H