#include <string>
#include "Object.h"
#include <sstream>

using namespace std;

// Default values for Object class static members
const string Object::DEFAULT_DESCRIPTION = "A Random Weapon.";
const string Object::DEFAULT_LOCATION = "player";
const int Object::DEFAULT_DURABILITY = 100;

// Constructor: Initializes an Object with specific attributes.
Object::Object(const string& id, const string& description, const string& location, int durability)
    : id_(id), description_(description), location_(location), durability_(durability) {}

// Destructor: Cleans up the Object's resources.
Object::~Object() {
    // Cleanup logic here (if needed).
}

// getId: Returns the ID of the object.
string Object::getId() const { 
    return id_; 
}

// getDescription: Returns the description of the object.
string Object::getDescription() const { 
    return description_; 
}

// getDurability: Returns the durability of the object.
int Object::getDurability() const { 
    return durability_; 
}

// setDurability: Sets the durability of the object.
void Object::setDurability(int durability) { 
    durability_ = durability; 
}

// setLocation: Sets the location of the object.
void Object::setLocation(const string& location) { 
    location_ = location; 
}

// getLocation: Gets the current location of the object.
string Object::getLocation() const { 
    return location_; 
}

// look: Provides a detailed description of the object.
string Object::look() const {
    stringstream ss;

    ss << "        Object :: " << id_ << " : " << description_ << endl;
    ss << "            Current status :: Durability(" << durability_ << ")" << endl;
    ss << "                              Location(" << location_ << ")" << endl;

    return ss.str();
}
