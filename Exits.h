#pragma once
#include "Room.h"

// Exits.h
#ifndef EXITS_H
#define EXITS_H

class Exits {
private:
    Room* _east;
    Room* _west;
    Room* _north;
    Room* _south;

public:
    Exits() : _east(nullptr), _west(nullptr), _north(nullptr), _south(nullptr) {}

    Room* get(const std::string& direction);
    void set(const std::string& direction, Room* room);
};

#endif // EXITS_H
