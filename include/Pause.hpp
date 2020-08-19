/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Pause.hpp
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "enum_indie_studio.hpp"
#include "Data.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <SFML/Audio.hpp>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Pause {
    public:
        Pause(IrrlichtDevice *device_game);
        void run();
        bool manage_event();
        bool is_running();
        bool game_running();
        void set_run(Data new_data);
        void set_running(bool var_running);
        ~Pause();
    protected:
    private:
        IVideoDriver * _driver;
        ISceneManager *_scene_manager;
        IGUIEnvironment * _env;
        IGUIFont *_font;
        IGUISkin *_skin;
        ITexture *_image;
        std::vector<IGUIButton *> _button;
        std::vector<IGUIFont *> _text;
        bool _is_running;
        bool run_game;
        Data _data;
};

#endif /* !PAUSE_HPP_ */