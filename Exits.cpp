#include "Exits.h"
#include <string>

using namespace std;

Room* Exits::get(const string& direction) {
    if (direction == "east") return _east;
    if (direction == "west") return _west;
    if (direction == "north") return _north;
    if (direction == "south") return _south;

    return nullptr;
}

void Exits::set(const string& direction, Room* room) {
    if (direction == "east") _east = room;
    else if (direction == "west") _west = room;
    else if (direction == "north") _north = room;
    else if (direction == "south") _south = room;
}
