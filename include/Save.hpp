/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Save and load functions
*/
#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <iostream>
#include <vector>
#include <tuple>

class Save {
    public:
        Save() {};
        Save(std::string player_name, std::tuple<float, float> player_pos);
        ~Save(){};
        std::vector<std::tuple<std::string, std::tuple<float,float>, std::string>> Load();
};

#endif /*SAVE_HPP*/