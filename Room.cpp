#include "Room.h"
#include <algorithm>
#include <sstream>

using namespace std;

// Constructor: Initializes a Room with a specific ID and description.
Room::Room(const string& id, const string& description)
    : id_(id), description_(description) {}

// Destructor: Cleans up the Room's resources.
Room::~Room() {
	// Delete all dynamically allocated objects
	for (auto& objectPair : objects_) {
		if (objectPair.second != nullptr) {
			delete objectPair.second;
		}
	}
	objects_.clear();

	// Delete all dynamically allocated enemies
	for (auto& enemyPair : enemies_) {
		if (enemyPair.second != nullptr) {
			delete enemyPair.second;
		}
	}
	enemies_.clear();
}

// getId: Returns the room ID.
string Room::getId() {
    return id_;
}

// getExit: Retrieves an exit from the room based on the specified direction.
Room* Room::getExit(const string& direction) {
    auto it = exits_.find(direction);
    return it != exits_.end() ? it->second : nullptr;
}

// setExit: Sets an exit for the room in a specified direction.
void Room::setExit(const string& direction, Room* room) {
    exits_[direction] = room;
}

// hasExits: Checks if the room has any exits.
bool Room::hasExits() {
    return !exits_.empty();
}

// getObject: Retrieves an object by ID from the room.
Object* Room::getObject(const string& objectId) {
    auto it = objects_.find(objectId);
    return it != objects_.end() ? it->second : nullptr;
}

// addObject: Adds an object to the room.
void Room::addObject(Object* object) {
    if (object) {
        objects_[object->getId()] = object;
    }
    // TODO: Add error handling if necessary
}

// hasObjects: Checks if the room has any objects.
bool Room::hasObjects() const {
    return !objects_.empty();
}

// removeObject: Removes an object from the room.
void Room::removeObject(Object* object) {
    objects_.erase(object->getId());
}

// getObjects: Returns a map of all objects in the room.
map<string, Object*> Room::getObjects() const {
    return objects_;
}

// getEnemy: Retrieves an enemy by ID from the room.
Enemy* Room::getEnemy(const string& enemyId) {
    auto it = enemies_.find(enemyId);
    return it != enemies_.end() ? it->second : nullptr;
}

// addEnemy: Adds an enemy to the room.
void Room::addEnemy(Enemy* enemy) {
    if (enemy) {
        enemies_[enemy->getId()] = enemy;
    }
    // TODO: Add error handling if necessary
}

// hasEnemy: Checks if the room has any enemies.
bool Room::hasEnemy() const {
    return !enemies_.empty();
}

// removeEnemy: Removes an enemy from the room.
void Room::removeEnemy(Enemy* enemy) {
    enemies_.erase(enemy->getId());
}

// getEnemies: Returns a map of all enemies in the room.
map<string, Enemy*> Room::getEnemies() const {
    return enemies_;
}

// getDescription: Returns the description of the room.
string Room::getDescription() const {
    return description_;
}

// look: Provides a detailed description of the room and its contents.
string Room::look() {
    stringstream ss;
    ss << "----------------------------------------------" << endl;
    ss << "Room :: " << id_ << " : " << description_ << endl;

    // Describing objects in the room
    if (!objects_.empty()) {
        ss << "    Objects in the room:\n";
        for (const auto& objectPair : objects_) {
            Object* object = objectPair.second;
            ss << object->look() << endl;
        }
    }

    // Describing enemies in the room
    if (!enemies_.empty()) {
        ss << "    Enemies in the room:\n";
        for (const auto& enemyPair : enemies_) {
            Enemy* enemy = enemyPair.second;
            ss << enemy->look() << endl;
        }
    }

    // Describing exits from the room
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

// lookAround: Provides an overview of the room's surroundings.
string Room::lookAround() {
    stringstream ss;
    for (const auto& exitPair : exits_) {
        Room* connectedRoom = exitPair.second;
        if (connectedRoom) {
            ss << "\n\nLooking towards the " << exitPair.first << ", you see: \n";
            ss << "    Direction : " << exitPair.first << endl;
            ss << connectedRoom->look() << endl << endl;
        }
    }
    return ss.str();
}
