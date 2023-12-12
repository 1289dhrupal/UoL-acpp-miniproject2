#include <string>
#include "Object.h"

using namespace std;

const string Object::DEFAULT_DESCRIPTION = "A Random Weapon.";
const string Object::DEFAULT_LOCATION = "player";
const int Object::DEFAULT_DURABILITY = 100;

Object::Object(const string& name, const string& description, const string& location, int durability)
    : _name(name), _description(description), _location(location), _durability(durability) {}

Object::~Object() { /* No cleanup needed */ }

string Object::getName() const { return _name; }

string Object::getDescription() const { return _description; }

int Object::getDurability() const { return _durability; }

void Object::setLocation(const string& location) { _location = location; }

string Object::getLocation() const { return _location; }
