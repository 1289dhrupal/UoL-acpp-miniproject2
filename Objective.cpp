#include "Objective.h"
#include <sstream>

using namespace std;

// Constructor initializing Objective with a type and room ID.
Objective::Objective(const string& type, const string& targetId) : type_(type), targetId_(targetId) {}

// Destructor for Objective class.
Objective::~Objective() { /* No cleanup needed */ }

string Objective::getTargetId(){
    return targetId_;
}

string Objective::check() {
    std::stringstream ss;
    ss << "----------------------------------------------" << endl;
    if (type_ == "room") {
        ss << "Objective :: Reach room \"" << targetId_ << "\"." << endl;
    }
    else if (type_ == "kill") {
        ss << "Objective :: Kill enemy \"" << targetId_ << "\"." << endl;
    }
    else if (type_ == "collect") {
        ss << "Objective :: Coolect object \"" << targetId_ << "\"." << endl;
    }
    else {
        ss << "Objective :: Survival." << endl;
    }
    ss << "----------------------------------------------" << endl;
    return ss.str();

}