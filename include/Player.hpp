//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_PLAYER_HPP
#define MINECRAFTCLONE_PLAYER_HPP
#include <raylib.h>
#include "Engine/Renderer.hpp"


class Player {
    public:
    Player();

    void update(Camera3D* camera_3d);
    void draw();

    private:
    void controlCamera(Camera3D* camera_3d);
    void move();

    private: //variables
    Vector3 position = {0,0,0};
    Camera3D camera = Renderer::getCamera();
};


#endif //MINECRAFTCLONE_PLAYER_HPP