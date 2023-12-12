#include "Room.h"
#include <algorithm>
#include <sstream>

Room::Room(const string& id, const string& description)
    : id_(id), description_(description) {}

Room::~Room() { /* Cleanup code, if any(currently not needed */ }

Room* Room::getExit(const string& direction) {
    auto it = exits_.find(direction);
    if (it != exits_.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::setExit(const string& direction, Room* room) { exits_[direction] = room; }

Object* Room::getObject(const string& enemyId) {
    auto it = objects_.find(enemyId);
    if (it != objects_.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that id is found
}


void Room::addObject(Object* object) {
    if (object) {
        objects_[object->getId()] = object; // Use object id as key
    }
    // TODO: throw error
}

bool Room::hasObjects() const { return !objects_.empty(); }

void Room::removeObject(Object* object) { objects_.erase(object->getId()); }

map<string, Object*> Room::getObjects() const { return objects_; }

Enemy* Room::getEnemy(const string& enemyId) {
    auto it = enemies_.find(enemyId);
    if (it != enemies_.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that id is found
}

void Room::addEnemy(Enemy* enemy) {
    if (enemy) {
        enemies_[enemy->getId()] = enemy; // Use enemy id as key
    }
    // TODO: throw error
}

bool Room::hasEnemy() const { return !enemies_.empty(); }

void Room::removeEnemy(Enemy* enemy) { enemies_.erase(enemy->getId()); }

map<string, Enemy*> Room::getEnemies() const { return enemies_; }

string Room::getDescription() const {
    return description_;
}

string Room::look() {
    stringstream ss;

    ss << description_ << "\n";

    // Describe objects
    for (const auto& object : objects_) {
        ss << "You see a " << object.first << "." << endl;
    }

    // Describe exits
    for (const auto& exit : exits_) {
        ss << "There is an exit to the " << exit.first << "." << endl;
    }

    // Describe enemies
    for (const auto& enemy : enemies_) {
        ss << "There is a " << enemy.first << " here." << endl;
    }

    return ss.str();
}

string Room::lookAround() {
    stringstream ss;
    for (const auto& exitPair : exits_) {
        Room* connectedRoom = exitPair.second;
        if (connectedRoom) {
            ss << "Looking towards the " << exitPair.first << ", you see: ";
            ss << connectedRoom->look() << endl << endl;
        }
    }
    return ss.str();
}
