#include "Room.h"
#include <algorithm>
#include <sstream>

using namespace std;

Room::Room(const string& id, const string& description)
    : id_(id), description_(description) {}

Room::~Room() {
	for (auto& objectPair : objects_) {
		if (objectPair.second != nullptr) {
			delete objectPair.second;
		}
	}
	objects_.clear();

	for (auto& enemyPair : enemies_) {
		if (enemyPair.second != nullptr) {
			delete enemyPair.second;
		}
	}
	enemies_.clear();
}

string Room::getId() {
    return id_;
}

Room* Room::getExit(const string& direction) {
    auto it = exits_.find(direction);
    return it != exits_.end() ? it->second : nullptr;
}

void Room::setExit(const string& direction, Room* room) {
    exits_[direction] = room;
}

bool Room::hasExits() {
    return !exits_.empty();
}

Object* Room::getObject(const string& objectId) {
    auto it = objects_.find(objectId);
    return it != objects_.end() ? it->second : nullptr;
}

void Room::addObject(Object* object) {
    if (object) {
        objects_[object->getId()] = object;
    }
}

bool Room::hasObjects() const {
    return !objects_.empty();
}

void Room::removeObject(Object* object) {
    objects_.erase(object->getId());
}

Enemy* Room::getEnemy(const string& enemyId) {
    auto it = enemies_.find(enemyId);
    return it != enemies_.end() ? it->second : nullptr;
}

void Room::addEnemy(Enemy* enemy) {
    if (enemy) {
        enemies_[enemy->getId()] = enemy;
    }
}

bool Room::hasEnemy() const {
    return !enemies_.empty();
}

void Room::removeEnemy(Enemy* enemy) {
    enemies_.erase(enemy->getId());
}

string Room::getDescription() const {
    return description_;
}

string Room::look() {
    stringstream ss;
    ss << "----------------------------------------------" << endl;
    ss << "Room :: " << id_ << " : " << description_ << endl;

    if (!objects_.empty()) {
        ss << "    Objects in the room:\n";
        for (const auto& objectPair : objects_) {
            Object* object = objectPair.second;
            ss << object->look() << endl;
        }
    }

    if (!enemies_.empty()) {
        ss << "    Enemies in the room:\n";
        for (const auto& enemyPair : enemies_) {
            Enemy* enemy = enemyPair.second;
            ss << enemy->look() << endl;
        }
    }

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
