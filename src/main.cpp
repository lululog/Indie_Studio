/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** main.cpp
*/

#include "../include/Bomberman.hpp"
#include "../include/menu.hpp"
#include "../include/End_Game.hpp"

int main ()
{
    Bomberman game;
    Bomberman_menu menu(game.get_device());
    Pause pause(game.get_device());
    End_Game end(game.get_device());

    while (game.get_device()->run()) {
        if (menu.is_running()) {
            menu.run();
            if (menu.get_stop_game())
                break;
        }
        else if (pause.is_running()) {
            pause.set_run(game.get_data());
            pause.run();
            if (!pause.manage_event())
                break;
        }
        else {
            if (game.give_statut_end_game()) {
                end.set_run(game.get_data());
                end.run();
                if (!end.manage_event())
                    break;
                if (end.menu_running()) {
                    game.get_device()->drop();
                    game.init_game();
                    menu.init_menu(game.get_device());
                    end.init_end_game(game.get_device());
                }
            } else {
                game.set_run(menu.get_data());
                game.run();
                pause.set_running(game.give_statut_pause());
            }
        }
        if (pause.game_running())
            game.set_pause_run(false);
    }
    game.get_device()->drop();
    return 0;
}

