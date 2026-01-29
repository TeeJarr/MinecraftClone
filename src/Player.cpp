//
// Created by Tristan on 1/28/26.
//

#include <raylib.h>
#include "../include/Player.hpp"

Player::Player() {
   position = {0,0, 0 };
}

void Player::draw() {

}

void Player::update(Camera3D* camera_3d) {
    this->controlCamera(camera_3d);
    this->move();
}

void Player::controlCamera(Camera3D* camera_3d) {
    UpdateCameraPro(camera_3d,
            (Vector3){
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
                (IsKeyDown(KEY_SPACE)*0.1f - IsKeyDown(KEY_LEFT_SHIFT)*0.2f)                                                // Move up-down
            },
            (Vector3){
                GetMouseDelta().x*0.05f,                            // Rotation: yaw
                GetMouseDelta().y*0.05f,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            },
            GetMouseWheelMove()*2.0f);                              // Move to target (zoom)
}

void Player::move() {
}
