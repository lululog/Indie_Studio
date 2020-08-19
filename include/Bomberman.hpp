/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Bomberman
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include <iostream>
#include "enum_indie_studio.hpp"
#include "menu.hpp"
#include "Pause.hpp"
#include "Map.hpp"
#include "Player.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bomberman {
    public:
        Bomberman();
        void run();
        IrrlichtDevice *get_device();
        bool give_statut_pause();
        bool give_statut_end_game();
        void set_pause_run(bool var_run_pause);
        void set_run(Data new_data);
        void init_game();
        Data get_data();
        ~Bomberman();
    protected:
    private:
        IrrlichtDevice *_device;
        IVideoDriver *_driver;
        ISceneManager *_scene_manager;
        IGUIEnvironment *_guienv;
        IGUIFont *_font;
        Map *map;
        Player *player;
        Player *player_two;
        std::vector<EKEY_CODE> key_player;
        ICameraSceneNode* camera;
        IGUIButton *_button_pause;
        Event_Manager *event;
        sf::Music _music;
        Data _data;
        ITexture *_background;
        bool _set_game;
        bool _statut_pause;
        bool _set_size_map;
        bool _statut_end_game;
        int _score;
};

#endif /* !BOMBERMAN_HPP_ */
