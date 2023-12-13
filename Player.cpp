#include "Player.h"
#include <sstream>

using namespace std;

// Constructor initializing player with a location.
Player::Player(const string& currLocation)
    : health_(100), location_(currLocation) {}

// Destructor for Player class.
Player::~Player() { /* No cleanup needed */ }

// Returns the player's health.
int Player::getHealth() const { return health_; }

// Sets the player's health.
void Player::setHealth(int health) { health_ = health; }

// Sets the player's current location.
void Player::setLocation(const string& location) { location_ = location; }

// Gets the player's current location.
string Player::getLocation() const { return location_; }

// Retrieves an object based on ID from player's inventory.
Object* Player::getObject(const string& objectId) {
    auto it = objects_.find(objectId);
    if (it != objects_.end()) {
        return it->second;
    }
    return nullptr;
}

// Returns a map of all objects in player's inventory.
map<string, Object*> Player::getObjects() const { return objects_; }

// Adds an object to player's inventory.
void Player::addObject(Object* object) { objects_[object->getId()] = object; }

// Removes an object from the room.
void Player::removeObject(Object* object) { objects_.erase(object->getId()); }

// Checks if the player has any objects in inventory.
bool Player::hasObjects() const { return !objects_.empty(); }

// Provides a status summary of the player.
string Player::check() const {
    std::stringstream ss;

    ss << "----------------------------------------------" << endl;
    ss << "Player :: Health (" << health_ << ")" << endl;
    ss << "          Current Location (" << location_ << ")" << endl;
    ss << "          Objects (" << endl;
    for (const auto& objectPair : objects_) {
        Object* object = objectPair.second;
        ss << "              " << objectPair.first << "(" << object->getDurability() << ")" << endl;
    }
    ss << "          )" << endl;

    ss << "----------------------------------------------" << endl;

    return ss.str();
}
