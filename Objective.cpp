#include "Objective.h"
#include <sstream>

using namespace std;

// Constructor: Initializes an Objective with a specific type and target room ID.
// type: The type of the objective (e.g., "room", "kill", "collect").
// targetId: The ID of the target associated with the objective.
Objective::Objective(const string& type, const string& targetId) 
    : type_(type), targetId_(targetId) {}

// Destructor: Cleans up the Objective's resources (if any).
Objective::~Objective() {
    // Cleanup logic here (if needed).
}

// getTargetId: Retrieves the ID of the target associated with the objective.
string Objective::getTargetId() {
    return targetId_;
}

// check: Provides a status summary or description of the objective.
string Objective::check() {
    stringstream ss;
    ss << "----------------------------------------------" << endl;
    
    // Displaying the objective based on its type
    if (type_ == "room") {
        ss << "Objective :: Reach room \"" << targetId_ << "\"." << endl;
    } else if (type_ == "kill") {
        ss << "Objective :: Kill enemy \"" << targetId_ << "\"." << endl;
    } else if (type_ == "collect") {
        ss << "Objective :: Collect object \"" << targetId_ << "\"." << endl;
    } else {
        // Default case for unspecified objective type
        ss << "Objective :: Survival." << endl;
    }

    ss << "----------------------------------------------" << endl;
    return ss.str();
}
