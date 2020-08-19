/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Player
*/

#include "../include/Player.hpp"
#include <stdio.h>

Player::Player(IrrlichtDevice *_device, Event_Manager *_event, vector3df pos, int statut)
{
    device = _device;
    IVideoDriver *_driver = _device->getVideoDriver();
    ISceneManager *smgr = _device->getSceneManager();
    player_model = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./assets/3D_models/Bomberman.b3d"));
    event = _event;
    if (player_model)
    {
        player_model->setPosition(pos);
        player_model->setFrameLoop (0, 350);
        player_model->setAnimationSpeed(120);
        player_model->setScale(vector3df(7.f,7.f,7.f));
    }
    last_time = device->getTimer()->getTime();
    movement_speed = 20;
    is_move = false;
    _bomber.reserve(2);
    key_player.reserve(6);
    if (statut == 1) {
        key_player[_KEY_UP] = KEY_KEY_Z;
        key_player[_KEY_RIGHT] = KEY_KEY_D;
        key_player[_KEY_LEFT] = KEY_KEY_Q;
        key_player[_KEY_BACK] = KEY_KEY_S;
        key_player[_KEY_BOMB] = KEY_KEY_A;
    } else {
        key_player[_KEY_UP] = KEY_UP;
        key_player[_KEY_RIGHT] = KEY_RIGHT;
        key_player[_KEY_LEFT] = KEY_LEFT;
        key_player[_KEY_BACK] = KEY_DOWN;
        key_player[_KEY_BOMB] = KEY_KEY_M;
    }
    max_bomb = 1;
    bomb_power = 1;
    is_dead = false;
}

Player::~Player()
{
}

vector3df Player::getPosition()
{
    return (player_model->getPosition());
}

IAnimatedMeshSceneNode* Player::getMesh()
{
    return player_model;
}

void Player::move_animation()
{
    if (event->IsKeyDown(key_player[_KEY_UP]) || event->IsKeyDown(key_player[_KEY_BACK])
    || event->IsKeyDown(key_player[_KEY_RIGHT]) || event->IsKeyDown(key_player[_KEY_LEFT])) {
        if (is_move == false) {
            player_model->setFrameLoop (355, 378);
            player_model->setAnimationSpeed(40);
            is_move = true;
        }
    }
    else {
        if (is_move == true) {
            player_model->setFrameLoop (0, 350);
            player_model->setAnimationSpeed(120);
            is_move = false;
        }
    }
}

void Player::manage_rotation()
{
    if (event->IsKeyDown(key_player[_KEY_UP]))
        player_model->setRotation(vector3df(0, 180, 0));
    if (event->IsKeyDown(key_player[_KEY_BACK]))
        player_model->setRotation(vector3df(0, 0, 0));
    if (event->IsKeyDown(key_player[_KEY_LEFT]))
        player_model->setRotation(vector3df(0, 90, 0));
    if (event->IsKeyDown(key_player[_KEY_RIGHT]))
        player_model->setRotation(vector3df(0, -90, 0));
    if (event->IsKeyDown(key_player[_KEY_UP]) && event->IsKeyDown(key_player[_KEY_RIGHT]))
        player_model->setRotation(vector3df(0, -135, 0));
    if (event->IsKeyDown(key_player[_KEY_UP]) && event->IsKeyDown(key_player[_KEY_LEFT]))
        player_model->setRotation(vector3df(0, 135, 0));
    if (event->IsKeyDown(key_player[_KEY_BACK]) && event->IsKeyDown(key_player[_KEY_RIGHT]))
        player_model->setRotation(vector3df(0, -45, 0));
    if (event->IsKeyDown(key_player[_KEY_BACK]) && event->IsKeyDown(key_player[_KEY_LEFT]))
        player_model->setRotation(vector3df(0, 45, 0));
}


bool Player::check_collision(std::vector<std::pair<ISceneNode*, vector3df>> block_list, Map *game_map, Player *enemy)
{
    std::vector<vector3df> player_rect = create_rect(player_model->getPosition(), 2);
    std::vector<vector3df> block_rect;
    bool rep = false;

    for (int i = 0; i != block_list.size(); i++) {
        if (block_list[i].first != NULL) {
            block_rect = create_rect(block_list[i].first->getPosition(), 5);
            if (is_intersect(player_rect, block_rect) == true &&
            game_map->get_block_id(game_map->get_point_of_vector(block_list[i].first->getPosition()).first, game_map->get_point_of_vector(block_list[i].first->getPosition()).second) != -1)
                rep = true;
        }
    }
    for (int i = 0; i != enemy->getBombList().size(); i++) {
        block_rect = create_rect(enemy->getBombList()[i].getPosition(), 4);
        if (is_intersect(player_rect, block_rect) == true)
            rep = true;
    }
    return rep;
}

std::vector<vector3df> Player::create_rect(vector3df pos, float size)
{
    std::vector<vector3df> rect;
    rect.push_back(vector3df(pos.X - size, pos.Y, pos.Z + size));
    rect.push_back(vector3df(pos.X + size, pos.Y, pos.Z + size));
    rect.push_back(vector3df(pos.X - size, pos.Y, pos.Z - size));
    rect.push_back(vector3df(pos.X + size, pos.Y, pos.Z - size));
    return rect;
}

bool Player::is_intersect(std::vector<vector3df> rect1, std::vector<vector3df> rect2)
{
    for (int i = 0; i != 4; i++)
        if (rect1[i].X > rect2[2].X && rect1[i].X < rect2[1].X
        && rect1[i].Z > rect2[2].Z && rect1[i].Z < rect2[1].Z)
            return true;
    return false;
}

void Player::move(Map *game_map, Player *enemy)
{
    const int now = device->getTimer()->getTime();
    const float frameDeltaTime = (float)(now - last_time) / 1000.f;
    last_time = now;
    vector3df position = player_model->getPosition();
    vector3df save_pos = player_model->getPosition();
    vector3df save_rotation = player_model->getRotation();

    if (event->IsKeyDown(key_player[_KEY_UP]))
        position.Z += movement_speed * frameDeltaTime;
    else if (event->IsKeyDown(key_player[_KEY_BACK]))
        position.Z -= movement_speed * frameDeltaTime;
    if (event->IsKeyDown(key_player[_KEY_RIGHT]))
        position.X += movement_speed * frameDeltaTime;
    else if (event->IsKeyDown(key_player[_KEY_LEFT]))
        position.X -= movement_speed * frameDeltaTime;
    move_animation();
    manage_rotation();
    player_model->setPosition(position);
    if (check_collision(game_map->get_list_block(), game_map, enemy))
        player_model->setPosition(vector3df(save_pos.X + ((save_pos.X - position.X)), position.Y, save_pos.Z + ((save_pos.Z - position.Z))));
}

void Player::bomb_explosion(Bomber bomb, Map *game_map)
{
    std::pair<int, int> bomb_pos = game_map->get_point_of_vector(bomb.getPosition());

    for (int i = 0; i != bomb_power + 1; i++) {
        if (game_map->get_block_id(bomb_pos.first + i, bomb_pos.second) >= 0) {
            game_map->delete_block(bomb_pos.first + i, bomb_pos.second);
            break;
        }
        game_map->delete_block(bomb_pos.first + i, bomb_pos.second);
    }
    for (int i = 0; i != bomb_power + 1; i++) {
        if (game_map->get_block_id(bomb_pos.first - i, bomb_pos.second) >= 0) {
            game_map->delete_block(bomb_pos.first - i, bomb_pos.second);
            break;
        }
        game_map->delete_block(bomb_pos.first - i, bomb_pos.second);
    }
    for (int i = 0; i != bomb_power + 1; i++) {
        if (game_map->get_block_id(bomb_pos.first, bomb_pos.second + i) >= 0) {
            game_map->delete_block(bomb_pos.first, bomb_pos.second + i);
            break;
        }
        game_map->delete_block(bomb_pos.first, bomb_pos.second + i);
    }
    for (int i = 0; i != bomb_power + 1; i++) {
        if (game_map->get_block_id(bomb_pos.first, bomb_pos.second - i) >= 0) {
            game_map->delete_block(bomb_pos.first, bomb_pos.second - i);
            break;
        }
        game_map->delete_block(bomb_pos.first, bomb_pos.second - i);
    }
}

std::vector<Bomber> Player::getBombList()
{
    return _bomber;
}

void Player::manage_bomb(Map *game_map, Player *enemy)
{
    if (event->IsKeyDown(key_player[_KEY_BOMB]) && _bomber.size() < max_bomb) {
        Bomber new_bomb(device, player_model->getPosition());
        if (verif_Bomb_Pos(new_bomb, enemy, game_map))
            _bomber.push_back(new_bomb);
        else
            new_bomb.destroy();
    }
    for (int i = 0; i < _bomber.size(); i++)
    {
        if (((clock() - _bomber[i].get_timer()) / (CLOCKS_PER_SEC/2)) > 2) {
            bomb_explosion(_bomber[i], game_map);
            _bomber[i].destroy();
            _bomber.erase(_bomber.begin() + i);
        }
    }
}

void Player::manage_bonus(Map *game_map)
{
    vector3df player_pos = player_model->getPosition();
    vector3df bonus_pos;

    for (int i = 0; i != game_map->getBonusList().size(); i++) {
        bonus_pos = game_map->getBonusList()[i].first->getPosition();
        if (bonus_pos.X == (round((player_pos.X) / 10) * 10)) {
            if (bonus_pos.Z == (round((player_pos.Z) / 10) * 10) - 2) {
                game_map->bonus[i].first->setPosition(vector3df(1000,1000,1000));
                add_bonus(game_map->bonus[i].second);
                continue;
            }
        }
    }
}

void Player::add_bonus(int bonus_id)
{
    if (bonus_id == 0) {
        max_bomb += 1;
    } else if (bonus_id == 1) {
        bomb_power += 1;
    } else if (bonus_id == 2) {
        movement_speed += 2.5;
    }
}

bool Player::verif_Bomb_Pos(Bomber new_bomb, Player *enemy, Map *game_map)
{
    std::vector<vector3df> bomb_rect = create_rect(new_bomb.getPosition(), 5);
    std::vector<vector3df> player_rect = create_rect(enemy->getMesh()->getPosition(), 2);
    if (is_intersect(player_rect, bomb_rect))
        return false;
    for (int i = 0; i != _bomber.size(); i++) {
        if (new_bomb.getPosition() == _bomber[i].getPosition())
            return false;
    }
    return true;
}

bool Player::check_is_dead()
{
    return is_dead;
}

void Player::update(Map *game_map, Player *enemy)
{
    move(game_map, enemy);
    manage_bomb(game_map, enemy);
    is_dead = game_map->manage_flame(player_model->getPosition());
    manage_bonus(game_map);
}