#include "Enemy.h"
#include "Objective.h"
#include <sstream>

using namespace std;

const string Enemy::DEFAULT_DESCRIPTION = "Random Enemy.";
const int Enemy::DEFAULT_AGGRESSIVENESS = 50;

// Constructor initializing Enemy with ID, description, aggressiveness, and location.
Enemy::Enemy(const string& id, const string& description, int aggressiveness)
    : id_(id), description_(description), aggressiveness_(aggressiveness){}

// Destructor for Enemy class.
Enemy::~Enemy() { /* No cleanup needed */ }

// Returns the ID of the enemy.
string Enemy::getId() const { return id_; }

// Returns the description of the enemy.
string Enemy::getDescription() const { return description_; }

// Returns the aggressiveness level of the enemy.
int Enemy::getAggressiveness() const { return aggressiveness_; }

// Sets the aggressiveness level of the enemy.
void Enemy::setAggressiveness(int aggressiveness) { aggressiveness_ = aggressiveness; }

// Provides a detailed description of the object.
string Enemy::look() const {
    stringstream ss;

    ss << "----------------------------------------------" << endl;
    ss << "Enemy :: " << id_ << " : " << description_ << endl;
    ss << "    Current status :: Aggressiveness_ (" << aggressiveness_ << ")" << endl;
    ss << "----------------------------------------------" << endl;

    return ss.str();
}