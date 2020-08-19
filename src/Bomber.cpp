/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Bomber.cpp
*/

#include "../include/Bomber.hpp"

Bomber::Bomber(IrrlichtDevice *_device_player, vector3df position_player)
{
    IVideoDriver *driver = _device_player->getVideoDriver();
    ISceneManager *smgr = _device_player->getSceneManager();
    bomber_model = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./assets/3D_models/Bomb.b3d"));
    float pos_x = round((position_player.X / 10));
    float pos_z = round((position_player.Z / 10));
    position_player.X = pos_x * 10;
    position_player.Z = pos_z * 10;
    if (bomber_model) {
        bomber_model->setMaterialTexture(0, driver->getTexture("./assets/3D_models/Bomb.png"));
        bomber_model->setPosition(position_player);
        bomber_model->setRotation(vector3df(0, 0, 0));
        bomber_model->setScale(vector3df(8.f,8.f,8.f));
    }
    timer = clock();
}

void Bomber::destroy()
{
    if (bomber_model) {
        bomber_model->remove();
        bomber_model = nullptr;
    }
}

void Bomber::set_position(vector3df pos)
{
    bomber_model->setPosition(pos);
}

std::clock_t Bomber::get_timer()
{
    return timer;
}

vector3df Bomber::getPosition()
{
    return bomber_model->getPosition();
}

Bomber::~Bomber()
{
}