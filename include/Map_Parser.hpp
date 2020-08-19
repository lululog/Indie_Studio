/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map_Parser
*/

#ifndef MAP_PARSER_HPP_
#define MAP_PARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "../include/enum_indie_studio.hpp"

class Map_Parser {
    public:
        Map_Parser(MAP_SIZE _map_size);
        ~Map_Parser();
        std::string getMap(void) const;

    protected:
    private:
        std::string _text_map;
};

#endif /* !MAP_PARSER_HPP_ */
