/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Data.hpp
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef DATA_HPP_
#define DATA_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "enum_indie_studio.hpp"
#include "Map.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Data {
    public:
        Data() {};
        void set_volume(int new_volume) { _volume = new_volume; };
        void set_name_player(std::string new_name_player) { _name_player = new_name_player; };
        void set_name_player_two(std::string new_name_player) { _name_player_two = new_name_player; };
        void set_multi(int multi) { _multi = multi; };
        void set_is_win(bool is_win) { _is_win = is_win; };
        void set_map(int map) { _map = map; };
        void set_time() { _timer = clock(); };
        void set_score(int score) { _score = score; };
        void set_time(clock_t time) { _timer = time; };
        int get_volume() { return _volume; };
        std::string get_name_player() { return _name_player; };
        std::string get_name_player_two() { return _name_player_two; };
        int get_multi() { return _multi; };
        bool get_is_win() { return _is_win; };
        int get_map() { return _map; };
        std::clock_t get_time() { return _timer; };
        int get_score() { return _score; };
        ~Data() {};
    protected:
    private:
        std::string _name_player;
        std::string _name_player_two;
        int _volume;
        int _multi;
        int _map;
        int _score;
        bool _is_win;
        std::clock_t _timer;
};

#endif /* !DATA_HPP_ */