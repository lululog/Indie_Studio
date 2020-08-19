/*
** EPITECH PROJECT, 2020
** indie
** File description:
** Flame
*/

#include "Flame.hpp"

Flame::Flame(IVideoDriver *_driver, ISceneManager *_scene_manager, vector3df block_pos)
{
    fire_pos = block_pos;
    flame_model = _scene_manager->addAnimatedMeshSceneNode(_scene_manager->getMesh("./assets/3D_models/fire.b3d"));
    flame_model->setMaterialTexture(0, _driver->getTexture("./assets/3D_models/Fire.png"));
    flame_model->setScale(vector3df(2, 2, 2));
    flame_model->setPosition(fire_pos);
    timer = clock();
}

void Flame::destroy(void)
{
    if (flame_model) {
        flame_model->remove();
        flame_model = nullptr;
    }
}

clock_t Flame::get_timer(void)
{
    return (timer);
}

vector3df Flame::get_flame_position(void)
{
    return (fire_pos);
}

Flame::~Flame()
{
}
