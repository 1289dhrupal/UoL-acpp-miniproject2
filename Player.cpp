#include "Player.h"
#include <sstream>

using namespace std;

Player::Player(Room* currLocation)
    : location_(currLocation), object_(nullptr) {
}

Player::~Player() {}

void Player::setLocation(Room* location) {
    location_ = location;
}

void Player::setObject(Object* object)
{
    object_ = object;
}

Object* Player::getObject()
{
    return object_;
}

Room* Player::getLocation() {
    return location_;
}

string Player::check() const {
    std::stringstream ss;

    ss << "----------------------------------------------" << endl;
    ss << "          Current Location (" << location_ << ")" << endl;
    ss << "----------------------------------------------" << endl;

    return ss.str();
}
