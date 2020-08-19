/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** End_Game.hpp
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef END_GAME_HPP_
#define END_GAME_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "enum_indie_studio.hpp"
#include "Data.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class End_Game {
    public:
        End_Game(IrrlichtDevice *device_game);
        void set_run(Data new_data);
        void run();
        bool manage_event();
        bool menu_running();
        void init_end_game(IrrlichtDevice *device_game);
        ~End_Game();
    protected:
    private:
        IVideoDriver *_driver;
        ISceneManager *_scene_manager;
        IGUIEnvironment *_env;
        IGUIFont *_font;
        IGUISkin *_skin;
        ITexture *_background;
        IAnimatedMeshSceneNode* player_win;
        IAnimatedMeshSceneNode* player_lose;
        IGUIButton *_button_menu;
        IGUIButton *_button_finish;
        sf::Music _music;
        bool _set_end;
        bool run_menu;
        Data _data;
};
void save(Data _data);

#endif /* !END_GAME_HPP_ */