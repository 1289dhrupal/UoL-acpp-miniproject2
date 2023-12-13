#include "Objective.h"
#include <sstream>

using namespace std;

Objective::Objective(const string& type, const vector<string> targetIds)
    : type_(type), targetIds_(targetIds) {}

Objective::~Objective() {}

bool Objective::isTargetId(const string& targetId) {
    return find(targetIds_.begin(), targetIds_.end(), targetId) != targetIds_.end();
}

string Objective::check() {
    stringstream ss;
    ss << "----------------------------------------------" << endl;

    if (type_ == "room") {
        ss << "Objective :: Reach rooms :: \"" << endl;
    }
    else if (type_ == "kill") {
        ss << "Objective :: Kill enemies :: \"" << endl;
    }
    else if (type_ == "collect") {
        ss << "Objective :: Collect objects :: \"" << endl;
    }
    else {
        ss << "Objective :: Survival." << endl;
    }

    ss << "----------------------------------------------" << endl;
    return ss.str();
}
