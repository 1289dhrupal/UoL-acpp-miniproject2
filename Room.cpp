#include "Room.h"
#include <algorithm>
#include <sstream>

using namespace std;

// Constructor initializing Room with ID and description.
Room::Room(const string& id, const string& description)
    : id_(id), description_(description) {}

// Destructor for Room class.
Room::~Room() { /* No cleanup needed */ }

string Room::getId()
{
    return id_;
}

// Gets an exit from the room based on the specified direction.
Room* Room::getExit(const string& direction) {
    auto it = exits_.find(direction);
    if (it != exits_.end()) {
        return it->second;
    }
    return nullptr;
}

// Sets an exit for the room in a specified direction.
void Room::setExit(const string& direction, Room* room) { exits_[direction] = room; }

// Retrieves an object by ID from the room.
Object* Room::getObject(const string& objectId) {
    auto it = objects_.find(objectId);
    if (it != objects_.end()) {
        return it->second;
    }
    return nullptr;
}

// Adds an object to the room.
void Room::addObject(Object* object) {
    if (object) {
        objects_[object->getId()] = object;
    }
    // TODO: throw error
}

// Checks if the room has any objects.
bool Room::hasObjects() const { return !objects_.empty(); }

// Removes an object from the room.
void Room::removeObject(Object* object) { objects_.erase(object->getId()); }

// Returns a map of all objects in the room.
map<string, Object*> Room::getObjects() const { return objects_; }

// Retrieves an enemy by ID from the room.
Enemy* Room::getEnemy(const string& enemyId) {
    auto it = enemies_.find(enemyId);
    if (it != enemies_.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that id is found
}

// Adds an enemy to the room.
void Room::addEnemy(Enemy* enemy) {
    if (enemy) {
        enemies_[enemy->getId()] = enemy; // Use enemy id as key
    }
    // TODO: throw error
}

// Checks if the room has any enemies.
bool Room::hasEnemy() const { return !enemies_.empty(); }

// Removes an enemy from the room.
void Room::removeEnemy(Enemy* enemy) { enemies_.erase(enemy->getId()); }

// Returns a map of all enemies in the room.
map<string, Enemy*> Room::getEnemies() const { return enemies_; }

string Room::getDescription() const {
    return description_;
}


// Provides a detailed description of the room and its contents.
string Room::look() {
    stringstream ss;

    ss << "----------------------------------------------" << endl;
    ss << "Room :: " << id_ << " : " << description_ << endl;

    // Describe objects
    if (!objects_.empty()) {
        ss << "    Objects in the room:\n";
        for (const auto& objectPair : objects_) {
            Object* object = objectPair.second;
            ss << object->look() << endl;
        }
    }

    // Describe enemies
    if (!enemies_.empty()) {
        ss << "    Enemies in the room:\n";
        for (const auto& enemyPair : enemies_) {
            Enemy* enemy = enemyPair.second;
            ss << enemy->look() << endl;
        }
    }

    // Describe exits
    if (!exits_.empty()) {
        ss << "    Exits from the room:\n";
        for (const auto& exitPair : exits_) {
            Room* exit = exitPair.second;
            ss << "        Exit :: " << exitPair.first << " : " << exitPair.second->getId() << endl;
        }
    }
    ss << "----------------------------------------------" << endl;

    return ss.str();
}

// Provides an overview of the room's surroundings.
string Room::lookAround() {
    stringstream ss;
    for (const auto& exitPair : exits_) {
        Room* connectedRoom = exitPair.second;
        if (connectedRoom) {
            ss << "\n\nLooking towards the " << exitPair.first << ", you see: \n";
            ss << connectedRoom->look() << endl << endl;
        }
    }
    return ss.str();
}
