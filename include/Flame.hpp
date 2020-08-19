/*
** EPITECH PROJECT, 2020
** indie
** File description:
** Flame
*/

#ifndef FLAME_HPP_
#define FLAME_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include <vector>
#include <ctime>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Flame {
    public:
        Flame(IVideoDriver *_driver, ISceneManager *_scene_manager, vector3df block_pos);
        std::clock_t get_timer(void);
        vector3df get_flame_position(void);
        void destroy(void);
        ~Flame();

    protected:
    private:
        IAnimatedMeshSceneNode* flame_model;
        vector3df fire_pos;
        std::clock_t timer;
};


#endif /* !FLAME_HPP_ */
