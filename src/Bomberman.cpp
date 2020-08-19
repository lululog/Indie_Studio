/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Bomberman
*/

#include "../include/Bomberman.hpp"
#include "../include/enum_indie_studio.hpp"

Bomberman::Bomberman()
{
    init_game();
}

void Bomberman::init_game()
{
    vector3df small_cam(0, 300, -20);

    event = new Event_Manager();

    _device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1950, 1200), 32, false, false, false, event);
    if (!_device)
        exit (84);
    _device->setWindowCaption(L"Indie Studio");
    if (!_music.openFromFile("assets/music/super-bomberman-r-music-battle-1.ogg"))
        exit (84);
    _driver = _device->getVideoDriver();
    _scene_manager = _device->getSceneManager();
    _guienv = _device->getGUIEnvironment();
    _font = _guienv->getFont("assets/sprite_menu/main_font.bmp");
    if (!_font)
        exit (84);
    _scene_manager->addCameraSceneNode(0, vector3df(0,0,0), vector3df(0,0,0));
    _scene_manager->setAmbientLight (irr::video::SColorf(0.5,0.5,0.5,0.0));
    camera = _scene_manager->addCameraSceneNode(0, small_cam);
    camera->setTarget(vector3df(0, 80, 70));
    player = new Player(_device, event, vector3df(-40, 185, -10), 1);
    _button_pause = _guienv->addButton(rect<irr::s32>(100,50,450,150), 0, -1, L"Pause");
    _button_pause->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _background = _driver->getTexture("assets/background_game.jpg");
    _set_game = false;
    _statut_pause = false;
    _set_size_map = false;
    _statut_end_game = false;
}

void Bomberman::set_run(Data new_data)
{
    vector3df small_cam(0, 300, -20);
    vector3df medium_cam(0, 300, 20);
    vector3df large_cam(0, 360, 80);

    if (_set_game == false) {
        _data = new_data;
        if (_data.get_multi() == 0)
            _data.set_name_player_two("bot");
        if (_data.get_map() == SMALL && _set_size_map == false) {
            camera = _scene_manager->addCameraSceneNode(0, small_cam);
            map = new Map(_driver, _scene_manager, SMALL);
            player_two = new Player(_device, event, vector3df(40, 185, 90), 2);
            _data.set_time();
            _data.set_score(0);
            _set_size_map = true;
        }
        if (_data.get_map() == MEDIUM && _set_size_map == false) {
            camera = _scene_manager->addCameraSceneNode(0, medium_cam);
            map = new Map(_driver, _scene_manager, MEDIUM);
            player_two = new Player(_device, event, vector3df(80, 185, 130), 2);
            _data.set_time();
            _data.set_score(0);
            _set_size_map = true;
        }
        if (_data.get_map() == LARGE && _set_size_map == false) {
            camera = _scene_manager->addCameraSceneNode(0, large_cam);
            map = new Map(_driver, _scene_manager, LARGE);
            player_two = new Player(_device, event, vector3df(120, 185, 170), 2);
            _data.set_time();
            _data.set_score(0);
            _set_size_map = true;
        }
        _music.setVolume(_data.get_volume());
        _music.setLoop(true);
        _music.play();
        _set_game = true;
    }
}

void Bomberman::run()
{
    _driver->beginScene(true, true, video::SColor(255,0,0,255));
    _driver->draw2DImage(_background, position2d<irr::s32>(0,0), rect<irr::s32>(0,0,1950,1200),
    0, SColor (255,255,255,255), true);
    player->update(map, player_two);
    if (_data.get_multi() == 1)
        player_two->update(map, player);
    if (player->check_is_dead()) {
        _statut_end_game = true;
        _data.set_is_win(PLAYER_TWO);
        _music.stop();
    }
    if (player_two->check_is_dead()) {
        _statut_end_game = true;
        _data.set_is_win(PLAYER_ONE);
        _music.stop();
    }
    if (((clock() - _data.get_time()) / (CLOCKS_PER_SEC / 4)) > 1) {
        _data.set_score(_data.get_score() + 1);
        _data.set_time();
    }
    _font->draw(stringw(_data.get_name_player().c_str()), rect<s32>(300,800,400,850), SColor(255,255,255,225));
    _font->draw(L"Score :", rect<s32>(100,500,200,600), SColor(255,255,255,225));
    _font->draw(stringw(_data.get_score()), rect<s32>(300,500,400,600), SColor(255,255,255,225));
    if (_data.get_map() == SMALL)
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(1400,200,1500,250), SColor(255,255,255,225));
    if (_data.get_map() == MEDIUM)
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(1600,100,1700,150), SColor(255,255,255,225));
    if (_data.get_map() == LARGE)
        _font->draw(stringw(_data.get_name_player_two().c_str()), rect<s32>(1600,100,1700,150), SColor(255,255,255,225));
    _scene_manager->drawAll();
    _button_pause->draw();
    if (_button_pause->isPressed()) {
        _statut_pause = true;
    }
    _driver->endScene();
}

IrrlichtDevice *Bomberman::get_device()
{
    return _device;
}

bool Bomberman::give_statut_pause()
{
    return _statut_pause;
}

bool Bomberman::give_statut_end_game()
{
    return _statut_end_game;
}

void Bomberman::set_pause_run(bool var_run_pause)
{
    _statut_pause = var_run_pause;
}

Data Bomberman::get_data()
{
    return _data;
}

Bomberman::~Bomberman()
{
}