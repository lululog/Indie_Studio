/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Pause.cpp
*/

#include "../include/Pause.hpp"

Pause::Pause(IrrlichtDevice *device_game)
{
    _button.reserve(3);
    _driver = device_game->getVideoDriver();
    _scene_manager = device_game->getSceneManager()->createNewSceneManager();
    _env = device_game->getGUIEnvironment();
    _skin = _env->getSkin();
    _font = _env->getFont("assets/sprite_menu/main_font.bmp");
    if (_font)
        _skin->setFont(_font);
    _skin->setFont(_env->getBuiltInFont(), EGDF_TOOLTIP);
    _image = _driver->getTexture("assets/sprite_menu/background_pause.jpg");
    _button[0] = _env->addButton(rect<irr::s32>(850,500,1200,600), 0, -1, L"Return");
    _button[1] = _env->addButton(rect<irr::s32>(850,650,1200,750), 0, -1, L"Save");
    _button[2] = _env->addButton(rect<irr::s32>(850,800,1200,900), 0, -1, L"Quit");
    _button[0]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button[1]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button[2]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _is_running = false;
    run_game = false;
}

void Pause::set_run(Data new_data)
{
    _data = new_data;
}

void Pause::run()
{
    _driver->beginScene(true, true, SColor(255,255,255,255));
    _driver->draw2DImage(_image, position2d<irr::s32>(0,0), rect<irr::s32>(0,0,1950,1200),
    0, SColor (255,255,255,255), true);
    _button[0]->draw();
    _button[1]->draw();
    _button[2]->draw();
    _driver->endScene();
}

bool Pause::manage_event()
{
    if (_button[2]->isPressed())
        return false;
    if (_button[0]->isPressed()) {
        _is_running = false;
        run_game = true;
    }
    return true;
}

bool Pause::is_running()
{
    return _is_running;
}

bool Pause::game_running()
{
    return run_game;
}

void Pause::set_running(bool var_running)
{
    _is_running = var_running;
}

Pause::~Pause()
{
}