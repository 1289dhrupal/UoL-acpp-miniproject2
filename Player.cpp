#include "Player.h"
#include <sstream>

using namespace std;

// Constructor: Initializes a player with a specific location.
// currLocation: The initial location of the player in the game.
Player::Player(const string& currLocation)
    : health_(100), location_(currLocation) {
    // Health is initialized to 100 by default.
}

// Destructor: Cleans up the player's resources (if any).
Player::~Player() {
    for (auto& objectPair : objects_) {
        delete objectPair.second;
    }
    objects_.clear();
}

// getHealth: Returns the current health of the player.
int Player::getHealth() const {
    return health_;
}

// setHealth: Sets the player's health.
// health: The new health value for the player.
void Player::setHealth(int health) {
    health_ = health;
}

// setLocation: Sets the current location of the player.
// location: The new location of the player.
void Player::setLocation(const string& location) {
    location_ = location;
}

// getLocation: Gets the player's current location.
string Player::getLocation() const {
    return location_;
}

// getObject: Retrieves an object from the player's inventory by its ID.
// objectId: The ID of the object to retrieve.
Object* Player::getObject(const string& objectId) {
    auto it = objects_.find(objectId);
    return it != objects_.end() ? it->second : nullptr;
}

// getObjects: Returns a map of all objects in the player's inventory.
map<string, Object*> Player::getObjects() const {
    return objects_;
}

// addObject: Adds an object to the player's inventory.
// object: The object to add to the inventory.
void Player::addObject(Object* object) {
    if (object) {
        objects_[object->getId()] = object;
    }
}

// removeObject: Removes an object from the player's inventory.
// object: The object to remove from the inventory.
void Player::removeObject(Object* object) {
    if (object) {
        objects_.erase(object->getId());
    }
}

// hasObjects: Checks if the player has any objects in their inventory.
bool Player::hasObjects() const {
    return !objects_.empty();
}

// Provides a status summary of the player.
string Player::check() const {
    std::stringstream ss;

    // Header for status summary
    ss << "----------------------------------------------" << endl;

    // Displaying the player's health
    ss << "Player :: Health (" << health_ << ")" << endl;

    // Displaying the player's current location
    ss << "          Current Location (" << location_ << ")" << endl;

    // Listing all objects in the player's inventory
    ss << "          Objects (" << endl;
    for (const auto& objectPair : objects_) {
        Object* object = objectPair.second;
        ss << "              " << objectPair.first << "(" << object->getDurability() << ")" << endl;
    }
    ss << "          )" << endl;

    // Footer for status summary
    ss << "----------------------------------------------" << endl;

    return ss.str();
}
