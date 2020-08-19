/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Event_Manager
*/

#include "../include/Event_Manager.hpp"

Event_Manager::Event_Manager()
{
    for (int i=0; i < KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

Event_Manager::~Event_Manager()
{
}

bool Event_Manager::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}

bool Event_Manager::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}