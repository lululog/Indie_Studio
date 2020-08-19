/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** menu.hpp
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "enum_indie_studio.hpp"
#include "Data.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bomberman_menu {
    public:
        Bomberman_menu(IrrlichtDevice *device_game);
        void init_button();
        void init_score();
        void run();
        void manage_event();
        void manage_event_settings();
        bool is_running();
        bool get_stop_game();
        Data get_data();
        void init_menu(IrrlichtDevice *device_game);
        void draw_score();
        ~Bomberman_menu();
    protected:
    private:
        IVideoDriver * _driver;
        ISceneManager *_scene_manager;
        IGUIEnvironment * _env;
        IGUIFont *_font;
        IGUISkin *_skin;
        ITexture *_image;
        ITexture *_image_font;
        std::vector<IGUIButton *> _button;
        std::vector<IGUIFont *> _text;
        bool _is_running;
        int _statut;
        sf::Music _music_menu;
        stringw volume;
        std::vector<std::tuple<std::string, int, std::string>> _score;
        IAnimatedMeshSceneNode* player_danse;
        Data _data;
        IGUIEditBox *_textbox_player_1;
        IGUIEditBox *_textbox_player_2;
        bool _stop_game;
};
bool sortbysec(const std::tuple<std::string, int, std::string>& a, const std::tuple<std::string, int, std::string>& b);
#endif /* !MENU_HPP_ */