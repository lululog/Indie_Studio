/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Save and load functions
*/
#include "Data.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <ctime>

void save(Data _data)
{
    std::ofstream saveFile;
    saveFile.open("score.txt", std::fstream::app);
    time_t now = time(0);
    std::string date = ctime(&now);
    saveFile << _data.get_name_player() << "," << _data.get_score() << "," << date;
    saveFile.close();
}