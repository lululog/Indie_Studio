/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include "Event_Manager.hpp"
#include "Bomber.hpp"
#include "Map.hpp"

class Player {
    public:
        Player(IrrlichtDevice *_device, Event_Manager *_event, vector3df pos, int statut);
        ~Player();
        vector3df getPosition();
        IAnimatedMeshSceneNode* getMesh();
        void update(Map *game_map, Player *enemy);
        bool check_is_dead();
        std::vector<Bomber> getBombList();
    protected:
        void move(Map *game_map, Player *enemy);
        void manage_rotation();
        void move_animation();
        bool check_collision(std::vector<std::pair<ISceneNode*, vector3df>> block_list, Map *game_map, Player *enemy);
        void manage_bomb(Map *game_map, Player *enemy);
        void manage_bonus(Map *game_map);
        void bomb_explosion(Bomber bomb, Map *game_map);
        bool verif_Bomb_Pos(Bomber new_bomb, Player *enemy, Map *game_map);
        void add_bonus(int bonus_id);
        std::vector<vector3df> create_rect(vector3df pos, float size);
        bool is_intersect(std::vector<vector3df> rect1, std::vector<vector3df> rect2);
    private:
        IrrlichtDevice *device;
        IAnimatedMeshSceneNode* player_model;
        Event_Manager *event;
        std::vector<Bomber> _bomber;
        std::vector<EKEY_CODE> key_player;
        int last_time;
        float movement_speed;
        bool is_move;
        int max_bomb;
        int bomb_power;
        bool is_dead;
};

#endif /* !PLAYER_HPP_ */
