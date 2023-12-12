#include "Player.h"
#include <sstream> // Include for stringstream

Player::Player(const string& currLocation)
    : health_(100), location_(currLocation) {}

Player::~Player() {
    // Cleanup code (if any)
}

int Player::getHealth() const { return health_; }

void Player::setHealth(int health) { health_ = health; }

void Player::setLocation(const string& location) { location_ = location; }

string Player::getLocation() const { return location_; }

Object* Player::getObject(const string& enemyId) {
    auto it = objects_.find(enemyId);
    if (it != objects_.end()) {
        return it->second;
    }
    return nullptr;  // Return nullptr if no enemy with that id is found
}

map<string, Object*> Player::getObjects() const { return objects_; }

void Player::addObject(Object* object) { objects_[object->getId()] = object; }

bool Player::hasObjects() const { return !objects_.empty(); }

string Player::check() const {
    std::stringstream ss;
    ss << "Current Location: " << location_ << endl;
    ss << "Health: " << health_ << endl;
    ss << "Objects: ";
    if (objects_.empty()) {
        ss << "None" << endl;
    }
    else {
        for (const auto& objectPair : objects_) {
            Object* object = objectPair.second;
            ss << "  " << objectPair.first << "(" << object->getDurability() << ")" << endl;
        }
    }
    return ss.str();
}