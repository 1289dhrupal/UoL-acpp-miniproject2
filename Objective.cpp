#include "Objective.h"

// Constructor initializing Objective with a type and room ID.
Objective::Objective(const string& type, const string& roomId) : type_(type), roomId_(roomId) {}

// Destructor for Objective class.
Objective::~Objective() { /* No cleanup needed */ }
