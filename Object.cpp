#include <string>
#include "Object.h"
#include <sstream>

using namespace std;

const string Object::DEFAULT_DESCRIPTION = "A Random Weapon.";
const string Object::DEFAULT_LOCATION = "player";
const int Object::DEFAULT_DURABILITY = 100;

// Constructor initializing Object with ID, description, location, and durability.
Object::Object(const string& id, const string& description, const string& location, int durability)
    : id_(id), description_(description), location_(location), durability_(durability) {}

// Destructor for Object class.
Object::~Object() { /* No cleanup needed */ }

// Returns the ID of the object.
string Object::getId() const { return id_; }

// Returns the description of the object.
string Object::getDescription() const { return description_; }

// Returns the durability of the object.
int Object::getDurability() const { return durability_; }

// Sets the durability of the object.
void Object::setDurability(int durability) { durability_ = durability; }

// Sets the location of the object.
void Object::setLocation(const string& location) { location_ = location; }

// Gets the current location of the object.
string Object::getLocation() const { return location_; }

// Provides a detailed description of the object.
string Object::look() const {
    stringstream ss;

    ss << "        Object :: " << id_ << " : " << description_ << endl;
    ss << "            Current status :: Durability(" << durability_ << ")" << endl;
    ss << "                              Location(" << location_ << endl;

    return ss.str();
}