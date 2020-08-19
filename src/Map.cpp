/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Map
*/

#include "../include/Map.hpp"
#include "../include/Map_Parser.hpp"

Map::Map(IVideoDriver *_driver, ISceneManager *_scene_manager, MAP_SIZE size)
{
    _map_size = size;
    driver = _driver;
    scene_manager = _scene_manager;
    Map_Parser parser(_map_size);
    cube = _scene_manager->addCubeSceneNode();
    wall = _scene_manager->addCubeSceneNode();
    block = _scene_manager->addAnimatedMeshSceneNode(_scene_manager->getMesh("./assets/3D_models/Block.b3d"));

    cube->setScale(vector3df(1, 0.5, 1));
    wall->setScale(vector3df(1, 1, 1));
    block->setScale(vector3df(10, 10, 10));

    wall->setID(0);
    block->setID(1);
    cube->setMaterialTexture(0, _driver->getTexture("./assets/green.jpg"));
    wall->setMaterialTexture(0, _driver->getTexture("./assets/wall.jpg"));
    block->setMaterialTexture(0, _driver->getTexture("./assets/3D_models/Block.png"));
    this->generateMap(parser.getMap());
    srand (time(NULL));
}

MAP_SIZE Map::get_map_size(void) const
{
    return (_map_size);
}

void Map::generateMap(std::string _map)
{
    int posX = -50;
    int posY = 185;
    int posZ = -20;
    std::string::iterator i_it;
    std::vector<std::pair<ISceneNode*, vector3df>>::iterator i;

    for (i_it = _map.begin(); i_it <= _map.end(); i_it++) {
        if (*i_it == 'm') {
            this->_list_mesh.push_back(std::make_pair(this->wall->clone(), vector3df(posX, posY, posZ)));
        } else if (*i_it == 'b') {
            this->_list_mesh.push_back(std::make_pair(this->block->clone(), vector3df(posX, posY, posZ)));
        } else if (*i_it == '\n') {
            posX = -50;
            posZ += 10;
            continue;
        } else {
            this->_list_mesh.push_back(std::make_pair(nullptr, vector3df(posX, posY, posZ)));
        }
        this->_list_mesh.push_back(std::make_pair(this->cube->clone(), vector3df(posX, posY - 7.5, posZ)));
        posX += 10;
    }
    for(i = _list_mesh.begin(); i < _list_mesh.end(); i++) {
        if (i->first)
            i->first->setPosition(i->second);
    }
}

bool Map::is_vector_in_list(vector3df vect)
{
    std::vector<std::pair<ISceneNode*, vector3df>>::iterator itt;

    for (itt = _list_mesh.begin(); itt <= _list_mesh.end(); itt++) {
        if (itt->second.X == vect.X) {
            if (itt->second.Z == vect.Z)
                return (true);
        }
    }
    return (false);
}

vector3df Map::get_vector_of_point(int x, int z)
{
    int x_s = -50;
    int y_s = 185;
    int z_s = -20;
    int x_block = x_s + (10 * x);
    int z_block = z_s + (10 * z);

    if (is_vector_in_list(vector3df(x_block, y_s, z_block)))
        return (vector3df(x_block, y_s, z_block));
    return (vector3df(-1,-1,-1));
}

std::pair<int, int> Map::get_point_of_vector(vector3df vect)
{
    int x_s = -50;
    int y_s = 185;
    int z_s = -20;
    int x = 0;
    int z = 0;

    if (is_vector_in_list(vect)) {
        while (vect.X != x_s) {
            vect.X -= 10;
            x++;
        }
        while (vect.Z != z_s) {
            vect.Z -= 10;
            z++;
        }
        return (std::make_pair(x, z));
    }
    return (std::make_pair(-1, -1));
}

std::vector<std::pair<ISceneNode*, vector3df>> Map::get_list_block(void) const
{
    return (_list_mesh);
}

std::vector<std::pair<IAnimatedMeshSceneNode *, int>>  Map::getBonusList(void)
{
    return (bonus);
}

void Map::bonus_spawn(vector3df pos)
{
    IAnimatedMeshSceneNode *new_bonus;
    int rand_nbr = 0;
    if (rand()%100 >= 85) {
        new_bonus = scene_manager->addAnimatedMeshSceneNode(scene_manager->getMesh("./assets/3D_models/Bonus.b3d"));
        pos.Z = pos.Z - 2;
        new_bonus->setPosition(pos);
        new_bonus->setRotation(vector3df(45, 0, 0));
        new_bonus->setScale(vector3df(2, 2, 2));
        srand(time(NULL));
        rand_nbr = rand()%3;
        if (rand_nbr == 0)
            new_bonus->setMaterialTexture(0, driver->getTexture("./assets/3D_models/bomb_bonus.png"));
        if (rand_nbr == 1)
            new_bonus->setMaterialTexture(0, driver->getTexture("./assets/3D_models/flame_bonus.png"));
        if (rand_nbr == 2)
            new_bonus->setMaterialTexture(0, driver->getTexture("./assets/3D_models/speed_bonus.png"));
        bonus.push_back(std::make_pair(new_bonus, rand_nbr));
    }
}

int Map::delete_block(int x, int z)
{
    vector3df block_v = get_vector_of_point(x, z);
    if (block_v.X == -1) {
        if (block_v.Z == -1)
            return (-1);
    }
    std::vector<std::pair<ISceneNode*, vector3df>>::iterator itt;

    for (itt = _list_mesh.begin(); itt <= _list_mesh.end(); itt++) {
        if (block_v == itt->second)
            break;
    }
    if (!itt->first) {
        Flame flame(driver, scene_manager, block_v);
        _list_flame.push_back(flame);
        return (0);
    }
    if (!is_breakable_block(x, z))
        return (-1);
    bonus_spawn(block_v);
    itt->first->remove();
    itt->first = nullptr;
    Flame flame(driver, scene_manager, block_v);
    _list_flame.push_back(flame);
    return (0);
}

bool Map::is_breakable_block(int x, int z)
{
    if (get_block_id(x, z) == 1)
        return (true);
    return (false);
}

int Map::get_block_id(int x, int z)
{
    vector3df vect = get_vector_of_point(x, z);
    std::vector<std::pair<ISceneNode*, vector3df>>::iterator itt;

    if (vect.X == -1) {
        if (vect.Z == -1)
            return (-1);
    }

    for (itt = _list_mesh.begin(); itt <= _list_mesh.end(); itt++) {
        if (vect == itt->second)
            break;
    }

    if (!itt->first)
        return (-1);
    return (itt->first->getID());
}

bool Map::manage_flame(vector3df player_pos)
{
    for (int i = 0; i < _list_flame.size(); i++)
    {
        if (_list_flame[i].get_flame_position().X == (round((player_pos.X) / 10) * 10)) {
            if (_list_flame[i].get_flame_position().Z == (round(player_pos.Z / 10) * 10))
                return (true);
        }
        if (((clock() - _list_flame[i].get_timer())) > 200000) {
            _list_flame[i].destroy();
            _list_flame.erase(_list_flame.begin() + i);
        }
    }
    return (false);
}

Map::~Map()
{
}
