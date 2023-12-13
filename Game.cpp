#include "Game.h"
#include "Player.h"
#include <sstream>

using namespace std;

// Constructor: Initializes the game with JSON data
Game::Game(const json& jsonData)
{
	initializeObjective_(jsonData);
	initializeRooms_(jsonData);
	initializePlayer_(jsonData);
	initializeObjects_(jsonData);
	initializeEnemies_(jsonData);
}

Game::~Game() {
	// Delete the player instance
	if (player_ != nullptr) {
		delete player_;
		player_ = nullptr;
	}

	// Delete the objective instance
	if (objective_ != nullptr) {
		delete objective_;
		objective_ = nullptr;
	}

	// Delete all dynamically allocated enemies
	for (auto& enemyPair : enemies_) {
		delete enemyPair.second;
	}
	enemies_.clear();

	// Delete all dynamically allocated rooms
	for (auto& roomPair : rooms_) {
		delete roomPair.second;
	}
	rooms_.clear();

	// Delete all dynamically allocated objects
	for (auto& objectPair : objects_) {
		delete objectPair.second;
	}
	objects_.clear();
}

// Checks if the game is over
bool Game::isGameOver() const {
	return isGameOver_;
}

// Displays a list of available actions to the player
string Game::displayActions() const {
	std::stringstream ss;

	ss << "Available Actions:\n";
	ss << "1. Status - Check the current status of the game.\n";
	ss << "   Usage: Type 'status' to get a summary of the current gameplay.\n";
	ss << "2. Look - Check your surroundings or inspect specific items or enemies.\n";
	ss << "   Usage: Type 'look room' to look at the current room.\n";
	ss << "          Type 'look around' to see nearby areas.\n";
	ss << "          Type 'look player' to check the player's status.\n";
	ss << "          Type 'look object [object ID]' for details about an object.\n";
	ss << "          Type 'look enemy [enemy ID]' for details about an enemy.\n";
	ss << "3. Pick - Pick up an object in the current room.\n";
	ss << "   Usage: Type 'pick [object ID]' to pick up an object.\n";
	ss << "4. Drop - Drop an object from your inventory.\n";
	ss << "   Usage: Type 'drop [object ID]' to drop an object.\n";
	ss << "5. Goto - Move to a different room, if possible.\n";
	ss << "   Usage: Type 'goto [direction]' to move to a different room.\n";
	ss << "6. Attack - Attack an enemy using an object from your inventory.\n";
	ss << "   Usage: Type 'attack [enemy ID] [object ID]' to attack an enemy.\n";
	ss << "7. Exit - Exit the game.\n";
	ss << "   Usage: Type 'exit' to leave the game.\n";
	ss << "Note: All the commands are case sensitive.\n";
	return ss.str();
}

// Executes a command based on player input
string Game::performCommand(const string& action, const string& value1, const string& value2) {
	// Handle 'exit' command
	if (action == "exit") {
		isGameOver_ = true;
		return "You quit the game!\n";
	}

	// Handle 'status' command
	if (action == "status") {
		return actionStatus_();
	}

	// Handle 'look' command
	if (!value1.empty() && action == "look") {
		return actionLook_(value1, value2);
	}

	// Handle 'pick' command
	if (!value1.empty() && action == "pick") {
		return actionPick_(value1);
	}

	// Handle 'drop' command
	if (!value1.empty() && action == "drop") {
		return actionDrop_(value1);
	}

	// Handle 'goto' command
	if (!value1.empty() && action == "goto") {
		return actionGoto_(value1);
	}

	// Handle 'attack' command
	if (!value1.empty() && !value2.empty() && action == "attack") {
		return actionAttack_(value1, value2);
	}

	// Default case for invalid commands
	return "Invalid Command for " + action + "\n";
}

// Initializes the game objective from JSON data
void Game::initializeObjective_(const json& jsonData) {
	// Extracting objective details from JSON
	string objectiveType = jsonData["objective"]["type"].get<string>();
	string objectiveRoomId = jsonData["objective"]["what"].get<string>();

	// Creating a new Objective instance
	objective_ = new Objective(objectiveType, objectiveRoomId);
}

// Initializes the player from JSON data
void Game::initializePlayer_(const json& jsonData) {
	// Extracting initial room of the player from JSON
	string initialRoom = jsonData["player"]["initialroom"].get<string>();

	// Creating a new Player instance
	player_ = new Player(initialRoom);
}

// Initializes the game rooms from JSON data
void Game::initializeRooms_(const json& jsonData) {
	// Check if JSON contains room data
	if (jsonData.contains("rooms") && jsonData["rooms"].is_array()) {
		// Initialize each room
		for (const auto& roomData : jsonData["rooms"]) {
			const string roomId = roomData["id"].get<string>();
			const string roomDescription = roomData["desc"].get<string>();
			Room* room = new Room(roomId, roomDescription);
			rooms_[roomId] = room;
		}

		// Setup exits for each room
		for (const auto& roomData : jsonData["rooms"]) {
			const string currentRoomId = roomData["id"].get<string>();
			Room* currentRoom = rooms_[currentRoomId];

			// Check for exits in the room data
			if (roomData.contains("exits") && roomData["exits"].is_object()) {
				for (auto it = roomData["exits"].begin(); it != roomData["exits"].end(); ++it) {
					const string exitDirection = it.key();
					const string exitId = it.value().get<string>();

					Room* exitRoom = rooms_[exitId];
					currentRoom->setExit(exitDirection, exitRoom);
				}
			}
		}
	}
}

// Initializes game objects from JSON data
void Game::initializeObjects_(const json& jsonData) {
	if (jsonData.contains("objects") && jsonData["objects"].is_array()) {
		for (const auto& objectData : jsonData["objects"]) {
			string objectId = objectData["id"].get<string>();

			string objectDescription = Object::DEFAULT_DESCRIPTION;
			if (objectData.contains("desc") && objectData["desc"].is_string()) {
				objectDescription = objectData["desc"].get<string>();
			}

			string initialLocationId = Object::DEFAULT_LOCATION;
			if (objectData.contains("initialroom") && objectData["initialroom"].is_string()) {
				initialLocationId = objectData["initialroom"].get<string>();
			}

			int durability = Object::DEFAULT_DURABILITY;
			if (objectData.contains("durability") && objectData["durability"].is_number_integer()) {
				durability = objectData["durability"].get<int>();
			}

			Object* newObject = new Object(objectId, objectDescription, initialLocationId, durability);
			objects_[objectId] = newObject;

			// Allocate objects to rooms or player
			if (rooms_.find(initialLocationId) != rooms_.end()) {
				Room* initialRoom = rooms_[initialLocationId];
				initialRoom->addObject(newObject);
			}
			else {
				player_->addObject(newObject);  // To player if no room found
			}
		}
	}
}

// Initializes enemies from JSON data
void Game::initializeEnemies_(const json& jsonData) {
	if (jsonData.contains("enemies") && jsonData["enemies"].is_array()) {
		for (const auto& enemyData : jsonData["enemies"]) {
			string enemyId = enemyData["id"].get<string>();
			string enemyDescription = Enemy::DEFAULT_DESCRIPTION;
			if (enemyData.contains("desc") && enemyData["desc"].is_string()) {
				enemyDescription = enemyData["desc"].get<string>();
			}

			int enemyAggressiveness = Enemy::DEFAULT_AGGRESSIVENESS;
			if (enemyData.contains("aggressiveness") && enemyData["aggressiveness"].is_number_integer()) {
				enemyAggressiveness = enemyData["aggressiveness"].get<int>();
			}

			string canBeKilledBy = Enemy::DEFAULT_KILLED_BY;
			if (enemyData.contains("killedby") && enemyData["killedby"].is_string()) {
				canBeKilledBy = enemyData["killedby"].get<string>();
			}

			Enemy* newEnemy = new Enemy(enemyId, enemyDescription, canBeKilledBy, enemyAggressiveness);
			enemies_[enemyId] = newEnemy;

			// Add enemies to their initial room
			if (enemyData.contains("initialroom") && enemyData["initialroom"].is_string()) {
				string initialRoomId = enemyData["initialroom"].get<string>();
				Room* room = rooms_[initialRoomId];
				room->addEnemy(newEnemy);
			}

			// Automatically removes the boss from the game if the room is not found.
		}
	}
}

// Handles the 'look' action
string Game::actionLook_(const string& value1, const string& value2) {
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	// Look inside the current room
	if (value1 == "room") {
		return currentRoom->look();
	}

	// Look around in the current location
	if (value1 == "around") {
		return currentRoom->lookAround();
	}

	// Check the player's status
	if (value1 == "player") {
		return player_->check();
	}

	// Check the game objective
	if (value1 == "objective") {
		return objective_->check();
	}

	// Handling look for enemies and objects
	if (value1 == "enemy" || value1 == "object") {
		map<string, Enemy*> currentEnemies = currentRoom->getEnemies();
		map<string, Object*> currentObjects = currentRoom->getObjects();
		map<string, Object*> currentPickedObjects = player_->getObjects();

		// Look at a specific enemy
		if (value1 == "enemy" && currentEnemies.find(value2) != currentEnemies.end()) {
			return currentEnemies[value2]->look();
		}

		// Look at a specific object in the room
		if (value1 == "object" && currentObjects.find(value2) != currentObjects.end()) {
			return currentObjects[value2]->look();
		}

		// Look at a specific object in player's possession
		if (value1 == "object" && currentPickedObjects.find(value2) != currentPickedObjects.end()) {
			return currentPickedObjects[value2]->look();
		}

		// Invalid object or enemy ID
		return "Invalid " + value1 + "Id\n";
	}

	// Default case for invalid commands
	return "Invalid command for look\n";
}

// Handles the 'pick' action
string Game::actionPick_(const string& objectId) {
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	map<string, Object*> currentObjects = currentRoom->getObjects();

	// Check if the object is present in the current room
	if (currentObjects.find(objectId) == currentObjects.end()) {
		return "Invalid ObjectId\n";
	}

	Object* currentObject = currentObjects[objectId];
	// Remove the object from the room and add it to the player's inventory
	currentRoom->removeObject(currentObject);
	player_->addObject(currentObject);

	// Check if the picked object is the objective's target
	if (objectId == objective_->getTargetId()) {
		isGameOver_ = true;
		return "You have found the required object " + objectId + "!!";
	}

	return "Picked up object.\n";
}

// Handles the 'drop' action
string Game::actionDrop_(const string& objectId) {
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	map<string, Object*> currentObjects = player_->getObjects();

	// Check if the object is in the player's possession
	if (currentObjects.find(objectId) == currentObjects.end()) {
		return "Invalid ObjectId\n";
	}

	Object* currentObject = currentObjects[objectId];
	// Remove the object from the player's inventory and add it to the current room
	player_->removeObject(currentObject);
	currentRoom->addObject(currentObject);

	return "Dropped object.\n";
}

// Handles the 'goto' action
string Game::actionGoto_(const string& direction) {
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];
	Room* exitRoom = currentRoom->getExit(direction);

	// Check if the current room has an exit in the specified direction
	if (exitRoom == nullptr) {
		return "Current room does not have exit to " + direction + "\n";
	}

	string roomId = exitRoom->getId();
	// Check for the validity of the room ID
	if (rooms_.find(roomId) == rooms_.end()) {
		return "Invalid roomId\n";
	}

	stringstream ss;

	// Handle encounters with enemies in the current room
	if (currentRoom->hasEnemy()) {
		int totalAggressiveness = 0;
		for (const auto& enemyPair : currentRoom->getEnemies()) {
			Enemy* enemy = enemyPair.second;
			totalAggressiveness += enemy->getAggressiveness();
			ss << "Health reduced by " << enemy->getAggressiveness() << " as this room had enemy " << enemyPair.first << endl;
		}

		int currentHealth = player_->getHealth();
		currentHealth -= totalAggressiveness; // Reduce player's health
		if (currentHealth <= 0) {
			isGameOver_ = true;
			ss << "Player is dead." << endl;
			return ss.str();
		}

		player_->setHealth(currentHealth);
		ss << "Health reduced as this room had enemies :: current health (" << currentHealth << ")" << endl;
	}

	// Update player's location
	player_->setLocation(roomId);
	ss << "Moved to Room " + roomId << endl;

	// Check if the new room is a trap
	if (!exitRoom->hasExits()) {
		ss << "You have entered a trap room with no exits." << endl;
		isGameOver_ = true;
		return ss.str();
	}

	// Check if the player has reached the target room
	if (roomId == objective_->getTargetId()) {
		if (!exitRoom->hasEnemy()) {
			ss << "You have reached the targeted room." << endl;
			ss << "You have cleared the objective as there are no enemies in the room!" << endl;
			isGameOver_ = true;
			return ss.str();
		}

		ss << "You have reached the targeted room. Please kill the remaining enemies to win the game." << endl;
	}

	return ss.str();
}

// Handles the 'attack' action
string Game::actionAttack_(const string& enemyId, const string& objectId) {
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	// Check if the enemy is in the current room
	map<string, Enemy*> currentEnemies = currentRoom->getEnemies();
	if (currentEnemies.find(enemyId) == currentEnemies.end()) {
		return "No enemy with ID " + enemyId + " in the current room.\n";
	}

	// Check if the player has the object
	map<string, Object*> currentPickedObjects = player_->getObjects();
	if (currentPickedObjects.find(objectId) == currentPickedObjects.end()) {
		return "No object with ID " + objectId + " in player's possession.\n";
	}

	// Perform attack calculations
	Enemy* currentEnemy = currentEnemies[enemyId];
	Object* currentPickedObject = currentPickedObjects[objectId];
	int enemyAggressiveness = currentEnemy->getAggressiveness();
	int objectDurability = currentPickedObject->getDurability();
	int updatedAggressiveness = std::max(0, enemyAggressiveness - objectDurability);
	int updatedDurability = std::max(0, objectDurability - enemyAggressiveness);

	// Update enemy and object states
	currentEnemy->setAggressiveness(updatedAggressiveness);
	currentPickedObject->setDurability(updatedDurability);

	stringstream ss;
	// Handle outcomes of the attack
	if (currentEnemy->getAggressiveness() <= 0) {
		currentRoom->removeEnemy(currentEnemy);
		delete currentEnemy;
		ss << "Enemy " << enemyId << " has been defeated!" << endl;
	}
	else {
		ss << "Enemy has been attacked and aggressiveness is reduced to " << updatedAggressiveness << endl;
	}

	if (currentPickedObject->getDurability() <= 0) {
		player_->removeObject(currentPickedObject);
		delete currentPickedObject;
		ss << "Object " << objectId << " has been destroyed!" << endl;
	}
	else {
		ss << "Object has been used and durability is reduced to " << updatedDurability << endl;
	}

	return ss.str();
}

// Provides the current status of the game
string Game::actionStatus_() {
	stringstream ss;
	// Retrieve and format various game status elements
	string playerInfo = actionLook_("player");
	string objectiveInfo = actionLook_("objective");
	string roomInfo = actionLook_("room");

	ss << "----------------------------- Current Status -----------------------------" << endl;
	ss << playerInfo << endl;
	ss << objectiveInfo << endl;
	ss << roomInfo << endl;
	ss << "--------------------------------------------------------------------------" << endl;

	return ss.str();
}
