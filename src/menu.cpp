/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** menu.cpp
*/

#include "../include/menu.hpp"

Bomberman_menu::Bomberman_menu(IrrlichtDevice *device_game)
{
    init_menu(device_game);
}

void Bomberman_menu::init_menu(IrrlichtDevice *device_game)
{
    _is_running = true;
    _statut = 0;
    _button.reserve(15);
    _data.set_volume(50);
    _data.set_multi(0);
    _data.set_map(MEDIUM);
    if (!_music_menu.openFromFile("assets/music/super-bomberman-r-music-menu-theme.ogg"))
        exit (84);
    _music_menu.play();
    _music_menu.setVolume(_data.get_volume());
    _music_menu.setLoop(true);
    _driver = device_game->getVideoDriver();
    _scene_manager = device_game->getSceneManager()->createNewSceneManager();
    _env = device_game->getGUIEnvironment();
    _skin = _env->getSkin();
    _font = _env->getFont("assets/sprite_menu/main_font.bmp");
    if (_font)
        _skin->setFont(_font);
    _skin->setFont(_env->getBuiltInFont(), EGDF_TOOLTIP);
    _image = _driver->getTexture("assets/sprite_menu/background_menu.jpg");
    _image_font = _driver->getTexture("assets/sprite_menu/pannel.png");
    player_danse = _scene_manager->addAnimatedMeshSceneNode(_scene_manager->getMesh("./assets/3D_models/Bomberman.b3d"));
    _textbox_player_1 = _env->addEditBox(L"Player 1", rect<irr::s32>(550,50,725,115), false);
    _textbox_player_2 = _env->addEditBox(L"Player 2", rect<irr::s32>(1150,50,1325,115), false);
    _scene_manager->setAmbientLight (irr::video::SColorf(0.8,0.8,0.8,0.0));
    if (player_danse) {
        player_danse->setRotation(vector3df(0, 50, 0));
        player_danse->setPosition(vector3df(0.3, -0.2, 0));
        player_danse->setFrameLoop (460, 603);
        player_danse->setAnimationSpeed(40);
        player_danse->setScale(vector3df(1.f / 2,1.f / 2,1.f / 2));
    }
    _stop_game = false;
    init_button();
    init_score();
}

void Bomberman_menu::init_button()
{
    _button[BUTTON_PLAY] = _env->addButton(rect<irr::s32>(200,270,550,360), 0, -1, L"Play");
    _button[BUTTON_SETTINGS] = _env->addButton(rect<irr::s32>(200,400,550,490), 0, -1, L"Settings");
    _button[BUTTON_SCORE] = _env->addButton(rect<irr::s32>(200,530,550,620), 0, -1, L"Score");
    _button[BUTTON_QUIT] = _env->addButton(rect<irr::s32>(200,660,550,750), 0, -1, L"Quit");
    _button[BUTTON_RETURN] = _env->addButton(rect<irr::s32>(850,735,1200,825), 0, -1, L"Return");
    _button[BUTTON_MAP_LITTLE] = _env->addButton(rect<irr::s32>(450,400,800,490), 0, -1, L"Easy");
    _button[BUTTON_MAP_NORMAL] = _env->addButton(rect<irr::s32>(850,400,1200,490), 0, -1, L"Normal");
    _button[BUTTON_MAP_BIG] = _env->addButton(rect<irr::s32>(1250,400,1600,490), 0, -1, L"Hard");
    _button[BUTTON_MOINS_VOLUME] = _env->addButton(rect<irr::s32>(900,190,950,240), 0, -1);
    _button[BUTTON_PLUS_VOLUME] = _env->addButton(rect<irr::s32>(1100,190,1150,240), 0, -1);
    _button[BUTTON_CONFIRM] = _env->addButton(rect<irr::s32>(900,300,950,350), 0, -1);
    _button[BUTTON_DELETE] = _env->addButton(rect<irr::s32>(1100,300,1150,350), 0, -1);
    _button[BUTTON_CONFIRM_TWO] = _env->addButton(rect<irr::s32>(1100,900,1450,990), 0, -1, L"Enter");
    _button[BUTTON_DELETE_TWO] = _env->addButton(rect<irr::s32>(500,900,850,990), 0, -1, L"Return");
    _button[BUTTON_RETURN_TWO] = _env->addButton(rect<irr::s32>(850,900,1200,990), 0, -1, L"Return");
    for (int i = 0; i != BUTTON_MAP_BIG + 1; i++) {
        if (i == BUTTON_MAP_NORMAL)
             _button[i]->setImage(_driver->getTexture("assets/sprite_menu/green_button05.png"));
        else
            _button[i]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _button[i]->setPressedImage(_driver->getTexture("assets/sprite_menu/green_button05.png"));
    }
    _button[BUTTON_SCORE]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button[BUTTON_RETURN_TWO]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button[BUTTON_MOINS_VOLUME]->setImage(_driver->getTexture("assets/sprite_menu/button_moins.png"));
    _button[BUTTON_PLUS_VOLUME]->setImage(_driver->getTexture("assets/sprite_menu/button_plus.png"));
    _button[BUTTON_CONFIRM]->setImage(_driver->getTexture("assets/sprite_menu/button_confirm.png"));
    _button[BUTTON_DELETE]->setImage(_driver->getTexture("assets/sprite_menu/button_delete.png"));
    _button[BUTTON_CONFIRM_TWO]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
    _button[BUTTON_DELETE_TWO]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
}

void Bomberman_menu::init_score()
{
    std::string saveFilePath = "score.txt";
    std::ifstream saveFile(saveFilePath);
    std::string line;
    std::vector<std::tuple<std::string, int, std::string>> result;

    if (_score.size() != 0)
        _score.clear();
    if(saveFile.is_open())
    {
        while(std::getline(saveFile, line))
        {
            std::stringstream buffer(line);
            std::vector<std::string> linebuffer;
            while(buffer.good())
            {
                std::string subline;
                getline(buffer, subline, ',');
                linebuffer.push_back(subline);
            }
            std::string player_name = linebuffer[0];
            int score = std::stoi(linebuffer[1]);
            std::string date = linebuffer[2];
            _score.push_back(std::make_tuple(player_name, score, date));
        }
    };
    std::sort(_score.begin(), _score.end(), sortbysec);
}

void Bomberman_menu::run()
{
    _driver->beginScene(true, true, SColor(255,255,255,255));
    _driver->draw2DImage(_image, position2d<irr::s32>(0,0), rect<irr::s32>(0,0,1950,1200),
    0, SColor (255,255,255,255), true);
    _driver->draw2DImage(_image_font, position2d<irr::s32>(150,150), rect<irr::s32>(0,0,1700, 700),
    0, SColor (230,0,0,255), true);
    if (_statut == MENU) {
        _button[BUTTON_PLAY]->draw();
        _button[BUTTON_SETTINGS]->draw();
        _button[BUTTON_SCORE]->draw();
        _button[BUTTON_QUIT]->draw();
        _scene_manager->drawAll();
        manage_event();
    } else if (_statut == SETTINGS_MENU) {
        _button[BUTTON_MOINS_VOLUME]->draw();
        _button[BUTTON_PLUS_VOLUME]->draw();
        _button[BUTTON_CONFIRM]->draw();
        _button[BUTTON_DELETE]->draw();
        _button[BUTTON_MAP_LITTLE]->draw();
        _button[BUTTON_MAP_NORMAL]->draw();
        _button[BUTTON_MAP_BIG]->draw();
        _button[BUTTON_RETURN]->draw();
        _font->draw(L"MUSIC :", rect<s32>(720,200,860,260), SColor(255,255,255,225));
        _font->draw(stringw(_data.get_volume()), rect<s32>(1000,200,1050,260), SColor(255,255,255,225));
        _font->draw(L"MULTIPLAYER :", rect<s32>(600,310,700,260), SColor(255,255,255,225));
        if (_data.get_multi() == 0)
            _font->draw(L"Single", rect<s32>(970,310,1100,260), SColor(255,255,255,225));
        else
            _font->draw(L"Multi", rect<s32>(970,310,1100,260), SColor(255,255,255,225));
        manage_event();
    } else if (_statut == PLAYER_MENU) {
        _textbox_player_1->draw();
        if (_data.get_multi() == 1)
            _textbox_player_2->draw();
        std::wstring wp1(_textbox_player_1->getText());
        std::string strp1(wp1.begin(), wp1.end());
        std::wstring wp2(_textbox_player_2->getText());
        std::string strp2(wp2.begin(), wp2.end());
        if (strp1.empty())
            strp1 = "Player 1";
        if (strp2.empty())
            strp2 = "Player 2";
        _data.set_name_player(strp1);
        _data.set_name_player_two(strp2);
        _button[BUTTON_CONFIRM_TWO]->draw();
        _button[BUTTON_DELETE_TWO]->draw();
        _scene_manager->drawAll();
        manage_event();
    } else if (_statut == SCORE_MENU) {
        _font->draw(L"Best Score :", rect<s32>(900,250,1000,300), SColor(255,255,255,225));
        draw_score();
        _button[BUTTON_RETURN_TWO]->draw();
        manage_event();
    }
    _driver->endScene();
}

void Bomberman_menu::draw_score()
{
    IGUIListBox *scoreListBox;
    int dy = 0;
    if (_score.size() != 0) {
        for (int i = 0; i != 10; i++, dy+= 25) {
            if (i == _score.size())
                break;
            std::string name = std::get<0>(_score[i]);
            std::string score = std::to_string(std::get<1>(_score[i]));
            std::string date = std::get<2>(_score[i]);
            _font->draw(stringw((name).c_str()), rect<s32>(500,350 + dy,600,400 + dy), SColor(255,255,255,225));
            _font->draw(stringw((score).c_str()), rect<s32>(800,350 + dy,900,400 + dy), SColor(255,255,0,225));
            _font->draw(stringw((date).c_str()), rect<s32>(1000,350 + dy,1100,400 + dy), SColor(255,255,255,225));
        }
    } else {
        std::string noScoreDisplay = ("No score, please play this game !");
        _font->draw(stringw(noScoreDisplay.c_str()), rect<s32>(700,400,800,450), SColor(255,255,255,225));
    }
}

void Bomberman_menu::manage_event()
{
    if (_statut == MENU) {
        if (_button[BUTTON_PLAY]->isPressed()) {
            _statut = PLAYER_MENU;
        }
        if (_button[BUTTON_SETTINGS]->isPressed())
            _statut = SETTINGS_MENU;
        if (_button[BUTTON_SCORE]->isPressed())
            _statut = SCORE_MENU;
        if (_button[BUTTON_QUIT]->isPressed()) {
            _music_menu.stop();
            _stop_game = true;
        }
    } else if (_statut == SETTINGS_MENU)
        manage_event_settings();
    else if (_statut == PLAYER_MENU) {
        if (_button[BUTTON_CONFIRM_TWO]->isPressed()) {
            _is_running = false;
            _music_menu.pause();
        }
        if (_button[BUTTON_DELETE_TWO]->isPressed())
            _statut = MENU;
    } else if (_statut == SCORE_MENU) {
        if (_button[BUTTON_RETURN_TWO]->isPressed())
            _statut = MENU;
    }
}

void Bomberman_menu::manage_event_settings()
{
    if (_button[BUTTON_RETURN]->isPressed())
        _statut = MENU;
    if (_button[BUTTON_MOINS_VOLUME]->isPressed() &&
        _data.get_volume() > 0) {
        _data.set_volume(_data.get_volume() - 1);
        _music_menu.setVolume(_data.get_volume());
    }
    if (_button[BUTTON_PLUS_VOLUME]->isPressed() &&
        _data.get_volume() < 100) {
        _data.set_volume(_data.get_volume() + 1);
        _music_menu.setVolume(_data.get_volume());
    }
    if (_button[BUTTON_CONFIRM]->isPressed())
        _data.set_multi(1);
    if (_button[BUTTON_DELETE]->isPressed())
        _data.set_multi(0);
    if (_button[BUTTON_MAP_LITTLE]->isPressed()) {
        _button[BUTTON_MAP_LITTLE]->setImage(_driver->getTexture("assets/sprite_menu/green_button05.png"));
        _button[BUTTON_MAP_NORMAL]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _button[BUTTON_MAP_BIG]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _data.set_map(SMALL);
    }
    if (_button[BUTTON_MAP_NORMAL]->isPressed()) {
        _button[BUTTON_MAP_NORMAL]->setImage(_driver->getTexture("assets/sprite_menu/green_button05.png"));
        _button[BUTTON_MAP_LITTLE]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _button[BUTTON_MAP_BIG]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _data.set_map(MEDIUM);
    }
    if (_button[BUTTON_MAP_BIG]->isPressed()) {
        _button[BUTTON_MAP_BIG]->setImage(_driver->getTexture("assets/sprite_menu/green_button05.png"));
        _button[BUTTON_MAP_LITTLE]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _button[BUTTON_MAP_NORMAL]->setImage(_driver->getTexture("assets/sprite_menu/blue_button04.png"));
        _data.set_map(LARGE);
    }
}

bool Bomberman_menu::is_running()
{
    return _is_running;
}

Data Bomberman_menu::get_data()
{
    return _data;
}

bool Bomberman_menu::get_stop_game()
{
    return _stop_game;
}

Bomberman_menu::~Bomberman_menu()
{
}

bool sortbysec(const std::tuple<std::string, int, std::string>& a, const std::tuple<std::string, int, std::string>& b)
{
    return (std::get<1>(a) > std::get<1>(b));
}