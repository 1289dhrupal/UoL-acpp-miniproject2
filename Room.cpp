#include "Room.h"
#include <algorithm>

Room::Room(const std::string& name, const std::string& description)
    : _name(name), _description(description) {}

Room::Room(const std::string& name, const std::string& description, const Exits& exits,
    const std::vector<Object>& objects, const std::vector<Enemy>& enemies)
    : _name(name), _description(description), _exits(exits), _objects(objects), _enemies(enemies) {}

Room* Room::getExit(const std::string& direction) {
    return _exits.get(direction);
}

void Room::setExit(const std::string& direction, Room* room) {
    _exits.set(direction, room);
}

void Room::addObject(const Object& object) {
    _objects.push_back(object);
}

bool Room::hasObjects() const {
    return !_objects.empty();
}

void Room::removeObject(const Object& object) {
    auto it = std::find(_objects.begin(), _objects.end(), object);
    if (it != _objects.end()) {
        _objects.erase(it);
    }
}

std::string Room::getDescription() const {
    return _description;
}

void Room::look() {
    std::cout << _description << "\n";
    // Describe items
    for (const auto& object : _objects) {
        std::cout << "You see a " << object.getName() << ".\n";
    }
    // Add logic to describe exits and enemies
}

void Room::lookAround() {
    // Add logic for looking around the room
}
