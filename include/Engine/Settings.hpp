//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_SETTINGS_HPP
#define MINECRAFTCLONE_SETTINGS_HPP

#endif //MINECRAFTCLONE_SETTINGS_HPP

class Settings {
    public:
    static Settings& getInstance() {
        static Settings instance;
        return instance;
    }

     int screenWidth;
     int screenHeight;
     int frameRate;

    int renderDistance; // Rendering Chunks
    int fov;

    private:
    Settings() {
        screenWidth = 1280;
        screenHeight = 720;
        this->frameRate = 60;
        this->fov = 45;
        this->renderDistance = 5;
    }
};