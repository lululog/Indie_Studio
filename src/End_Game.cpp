/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** End_Game.cpp
*/

#include "../include/End_Game.hpp"

End_Game::End_Game(IrrlichtDevice *device_game)
{
    init_end_game(device_game);
}

void End_Game::init_end_game(IrrlichtDevice *device_game)
{
    if (!_music.openFromFile("assets/music/super-bomberman-r-music-title-screen-extended.ogg"))
        exit (84);
    _music.setLoop(true);
    _driver = device_game->getVideoDriver();
    _scene_manager = device_game->getSceneManager()->createNewSceneManager();
    _env = device_game->getGUIEnvironment();
    _skin = _env->getSkin();
    _font = _env->getFont("assets/sprite_menu/main_font.bmp");
    if (_font)
        _skin->setFont(_font);
    _skin->setFont(_env->getBuiltInFont(), EGDF_TOOLTIP);
    _background = _driver->getTexture("assets/background_game.jpg");
    _scene_manager->setAmbientLight (irr::video::SColorf(0.8,0.8,0.8,0.0));
    _set_end = false;
    player_win = _scene_manager->addAnimatedMeshSceneNode(_scene_manager->getMesh("./assets/3D_models/Bomberman.b3d"));
    player_lose = _scene_manager->addAnimatedMeshSceneNode(_scene_manager->getMesh("./assets/3D_models/Bomberman.b3d"));
    if (player_win) {
        player_win->setRotation(vector3df(0, 50, 0));
        player_win->setPosition(vector3df(-0.4, -0.3, 0));
        player_win->setFrameLoop (460, 603);
        player_win->setAnimationSpeed(40);
        player_win->setScale(vector3df(1.f / 2,1.f / 2,1.f / 2));
    }
    if (player_lose) {
        player_lose->setRotation(vector3df(0, 50, 0));
        player_lose->setPosition(vector3df(0.4, -0.3, 0));
        player_lose->setLoopMode(false);
        player_lose->setFrameLoop (383, 450);
        player_lose->setAnimationSpeed(40);
        player_lose->setScale(vector3df(1.f / 2,1.f / 2,1.f / 2));
    }
    _button_menu = _env->addButton(rect<irr::s32>(1300,800,1550,890), 0, -1, L"Return menu");
    _button_finish = _env->addButton(rect<irr::s32>(200,800,550,890), 0, -1, L"Quit");
    _button_menu->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button_finish->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    run_menu = false;
}

void End_Game::set_run(Data new_data)
{
    if (!_set_end) {
        _data = new_data;
        if (_data.get_multi() == 0)
            _data.set_name_player_two("bot");
        save(_data);
        _music.play();
        _music.setVolume(_data.get_volume());
        _set_end = true;
    }
}

void End_Game::run()
{
    _driver->beginScene(true, true, video::SColor(255,0,0,255));
    _driver->draw2DImage(_background, position2d<irr::s32>(0,0), rect<irr::s32>(0,0,1950,1200),
    0, SColor (255,255,255,255), true);
    _font->draw(stringw(L"Score of"), rect<s32>(700,900,800,1000), SColor(255,255,255,225));
    if (_data.get_is_win() == PLAYER_ONE) {
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(1300,200,1400,350), SColor(255,255,255,225));
        _font->draw(stringw(_data.get_name_player().c_str()), rect<s32>(500,200,600,350), SColor(255,255,255,225));
        _font->draw(stringw(_data.get_name_player().c_str()), rect<s32>(860,900,960,1000), SColor(255,255,255,225));
    }
    if (_data.get_is_win() == PLAYER_TWO) {
        _font->draw(stringw(_data.get_name_player().c_str()), rect<s32>(1300,200,1400,350), SColor(255,255,255,225));
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(500,200,600,350), SColor(255,255,255,225));
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(860,900,960,1000), SColor(255,255,255,225));
    }
    _font->draw(stringw(_data.get_score()), rect<s32>(1100,900,1100,1200), SColor(255,255,255,225));
    _button_menu->draw();
    _button_finish->draw();
    _scene_manager->drawAll();
    _driver->endScene();
}

bool End_Game::manage_event()
{
    if (_button_finish->isPressed())
        return false;
    if (_button_menu->isPressed()) {
        run_menu = true;
        _music.pause();
    }
    return true;
}

bool End_Game::menu_running()
{
    return run_menu;
}

End_Game::~End_Game()
{
}