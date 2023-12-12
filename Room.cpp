#include "Room.h"
#include <algorithm>
#include <sstream>


Room::Room(const string& name, const string& description)
    : _name(name), _description(description) {}

Room::~Room() { /* Cleanup code, if any(currently not needed */ }

Room* Room::getExit(const string& direction) {
    auto it = _exits.find(direction);
    if (it != _exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::setExit(const string& direction, Room* room) {
    _exits[direction] = room; // Use object name as key
}

Object* Room::getObject(const string& enemy) {
    auto it = _objects.find(enemy);
    if (it != _objects.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that name is found
}


void Room::addObject(Object* object) {
    if (object) {
        _objects[object->getName()] = object; // Use object name as key
    }
    // TODO: throw error
}

bool Room::hasObjects() const {
    return !_objects.empty();
}

void Room::removeObject(Object* object) {
    _objects.erase(object->getName()); // Erase by key
}

Enemy* Room::getEnemy(const string& enemy) {
    auto it = _enemies.find(enemy);
    if (it != _enemies.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that name is found
}

void Room::addEnemy(Enemy* enemy) {
    if (enemy) {
        _enemies[enemy->getName()] = enemy; // Use enemy name as key
    }
    // TODO: throw error
}

bool Room::hasEnemy() const {
    return !_enemies.empty();
}

void Room::removeEnemy(Enemy* enemy) {
    _enemies.erase(enemy->getName()); // Erase by key
}

string Room::getDescription() const {
    return _description;
}

string Room::look() {
    stringstream ss;

    ss << _description << "\n";

    // Describe objects
    for (const auto& object : _objects) {
        ss << "You see a " << object.first << "." << endl;
    }

    // Describe exits
    for (const auto& exit : _exits) {
        ss << "There is an exit to the " << exit.first << "." << endl;
    }

    // Describe enemies
    for (const auto& enemy : _enemies) {
        ss << "There is a " << enemy.first << " here." << endl;
    }

    return ss.str();
}

string Room::lookAround() {
    stringstream ss;
    for (const auto& exitPair : _exits) {
        Room* connectedRoom = exitPair.second;
        if (connectedRoom) {
            ss << "Looking towards the " << exitPair.first << ", you see: ";
            ss << connectedRoom->look() << endl << endl;
        }
    }
    return ss.str();
}
