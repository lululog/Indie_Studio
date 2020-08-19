/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map_Parser
*/

#include "Map_Parser.hpp"

Map_Parser::Map_Parser(MAP_SIZE _map_size)
{
    std::ifstream file;

    if (_map_size == MAP_SIZE::SMALL)
        file.open("map/small.txt");
    else if (_map_size == MAP_SIZE::MEDIUM)
        file.open("map/medium.txt");
    else if (_map_size == MAP_SIZE::LARGE)
        file.open("map/large.txt");
    if (!file.is_open()) {
        std::cerr << "Can't open map file" << std::endl;
        exit(84);
    }
    _text_map.assign((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
}

std::string Map_Parser::getMap(void) const
{
    return (_text_map);
}

Map_Parser::~Map_Parser()
{
}
