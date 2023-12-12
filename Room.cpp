#include "Room.h"
#include <algorithm>

Room::Room(const string& name, const string& description)
    : _name(name), _description(description) {}

Room::~Room() { /* Cleanup code, if any(currently not needed */ }

Room* Room::getExit(const std::string& direction) {
    auto it = _exits.find(direction);
    if (it != _exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::setExit(const string& direction, Room* room) {
    _exits[direction] = room; // Use object name as key
}

Object* Room::getObject(const string& name) {
    auto it = _objects.find(name);
    if (it != _objects.end()) {
        return &(it->second);
    }
    return nullptr;  // Return nullptr if no enemy with that name is found
}


void Room::addObject(const Object& object) {
    _objects[object.getName()] = object; // Use object name as key
}

bool Room::hasObjects() const {
    return !_objects.empty();
}

void Room::removeObject(const Object& object) {
    _objects.erase(object.getName()); // Erase by key
}

Enemy* Room::getEnemy(const string& name) {
    auto it = _enemies.find(name);
    if (it != _enemies.end()) {
        return &(it->second);
    }
    return nullptr;  // Return nullptr if no enemy with that name is found
}

void Room::addEnemy(const Enemy& enemy) {
    _enemies[enemy.getName()] = enemy; // Use enemy name as key
}

bool Room::hasEnemy() const {
    return !_enemies.empty();
}

void Room::removeEnemy(const Enemy& enemy) {
    _enemies.erase(enemy.getName()); // Erase by key
}

std::string Room::getDescription() const {
    return _description;
}

void Room::look() {
    std::cout << _description << "\n";
    for (const auto& pair : _objects) { // pair is a std::pair<const std::string, Object>
        std::cout << "You see a " << pair.first << ".\n"; // pair.first accesses the Object
    }
    // Add logic for exits and enemies
}

void Room::lookAround() {
    // Add logic for looking around the room
}
