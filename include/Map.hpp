/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "../Irrlicht/include/irrlicht.h"
#include "../include/enum_indie_studio.hpp"
#include "../include/Flame.hpp"
#include <time.h>
#include <vector>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Map {
    public:
        Map(IVideoDriver *_driver, ISceneManager *_scene_manager, MAP_SIZE size);
        MAP_SIZE get_map_size(void) const;
        void generateMap(std::string _map);
        bool is_vector_in_list(vector3df vect);
        vector3df get_vector_of_point(int x, int y);
        std::pair<int, int> get_point_of_vector(vector3df vect);
        std::vector<std::pair<ISceneNode*, vector3df>> get_list_block(void) const;
        std::vector<std::pair<IAnimatedMeshSceneNode *, int>> getBonusList(void);
        bool is_breakable_block(int x, int z);
        int get_block_id(int x, int z);
        bool manage_flame(vector3df player_pos);
        //map modification//
        int delete_block(int x, int z);
        void bonus_spawn(vector3df pos);
        std::vector<std::pair<IAnimatedMeshSceneNode *, int>> bonus;

        ~Map();

    protected:
    private:
        IVideoDriver *driver;
        ISceneManager *scene_manager;
        IMeshSceneNode *cube;
        IMeshSceneNode *wall;
        IAnimatedMeshSceneNode  *block;
        MAP_SIZE _map_size;
        std::vector<std::pair<ISceneNode*, vector3df>> _list_mesh;
        std::vector<Flame> _list_flame;
};

#endif /* !MAP_HPP_ */
