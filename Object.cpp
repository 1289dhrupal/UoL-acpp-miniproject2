#include <string>
#include "Object.h"
#include <sstream>

using namespace std;

Object::Object(const string& id, const string& description, const string& location)
    : id_(id), description_(description), location_(location) {}

Object::~Object() {}

string Object::getId() const { 
    return id_; 
}

string Object::getDescription() const { 
    return description_; 
}

void Object::setLocation(const string& location) { 
    location_ = location; 
}

string Object::getLocation() const { 
    return location_; 
}

string Object::look() const {
    stringstream ss;

    ss << "        Object :: " << id_ << " : " << description_ << endl;
    ss << "            Current status :: Location(" << location_ << ")" << endl;

    return ss.str();
}
