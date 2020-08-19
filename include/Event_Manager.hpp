/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Event_Manager
*/

#ifndef EVENT_MANAGER_HPP_
#define EVENT_MANAGER_HPP_

#include "../Irrlicht/include/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Event_Manager : public IEventReceiver {
    public:
        Event_Manager();
        ~Event_Manager();
        bool OnEvent(const SEvent& event);
        bool IsKeyDown(EKEY_CODE keyCode) const;

    protected:
    private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif /* !EVENT_MANAGER_HPP_ */
