/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Bomber.hpp
*/

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef BOMBER_HPP_
#define BOMBER_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "enum_indie_studio.hpp"
#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
#include <string>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bomber {
    public:
        Bomber(IrrlichtDevice *_device_player, vector3df position_player);
        void set_position();
        void destroy();
        void set_position(vector3df pos);
        std::clock_t get_timer();
        vector3df getPosition();
        ~Bomber();
    protected:
    private:
        IAnimatedMeshSceneNode* bomber_model;
        vector3df pos;
        std::clock_t timer;
};

#endif /* !BOMBER_HPP_ */