#include <string>
#include "Object.h"

using namespace std;

const string Object::DEFAULT_DESCRIPTION = "A Random Weapon.";
const string Object::DEFAULT_LOCATION = "player";
const int Object::DEFAULT_DURABILITY = 100;

Object::Object(const string& id, const string& description, const string& location, int durability)
    : id_(id), description_(description), location_(location), durability_(durability) {}

Object::~Object() { /* No cleanup needed */ }

string Object::getId() const { return id_; }

string Object::getDescription() const { return description_; }

int Object::getDurability() const { return durability_; }

void Object::setLocation(const string& location) { location_ = location; }
string Object::getLocation() const { return location_; }
