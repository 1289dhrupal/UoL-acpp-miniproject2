#include "Player.h"
#include <sstream> // Include for stringstream

Player::Player(const string& currLocation)
    : _health(100), _location(currLocation) {}

Player::~Player() {
    // Cleanup code (if any)
}

int Player::getHealth() const {
    return _health;
}

void Player::setHealth(int health) {
    _health = health;
}

void Player::setLocation(const string& location) { _location = location; }

string Player::getLocation() const { return _location; }

Object* Player::getObject(const string& enemyName) {
    auto it = _objects.find(enemyName);
    if (it != _objects.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that name is found
}

map<string, Object*> Player::getObjects() const {
    return _objects;
}

void Player::addObject(Object* object) {
    _objects[object->getName()] = object;
}

bool Player::hasObjects() const {
    return !_objects.empty();
}

string Player::check() const {
    std::stringstream ss;
    ss << "Current Location: " << _location << endl;
    ss << "Health: " << _health << endl;
    ss << "Objects: ";
    if (_objects.empty()) {
        ss << "None" << endl;
    }
    else {
        for (const auto& objectPair : _objects) {
            Object* object = objectPair.second;
            ss << "  " << objectPair.first << "(" << object->getDurability() << ")" << endl;
        }
    }
    return ss.str();
}