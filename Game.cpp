#include "Game.h"
#include "Player.h"
#include <sstream>

using namespace std;

Game::Game(const json& jsonData)
{
	initializeObjective_(jsonData);
	initializeRooms_(jsonData);
	initializePlayer_(jsonData);
	initializeObjects_(jsonData);
	initializeEnemies_(jsonData);
}

bool Game::isGameOver() const {
	return isGameOver_;
}

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

string Game::performCommand(const string& action, const string& value1, const string& value2) {

	if (action == "exit") {
		isGameOver_ = true;
		return "You quit the game!\n";
	}

	if (action == "status") {
		return actionStatus_();
	}

	if (!value1.empty() && action == "look") {
		return actionLook_(value1, value2);
	}

	if (!value1.empty() && action == "pick") {
		return actionPick_(value1);
	}

	if (!value1.empty() && action == "drop") {
		return actionDrop_(value1);
	}

	if (!value1.empty() && action == "goto") {
		return actionGoto_(value1);
	}

	if (!value1.empty() && !value2.empty() && action == "attack") {
		return actionAttack_(value1, value2);
	}

	return "Invalid Command for " + action + "\n";
}

void Game::initializeObjective_(const json& jsonData) {
	string objectiveType = jsonData["objective"]["type"].get<string>();
	string objectiveRoomId = jsonData["objective"]["what"].get<string>(); // Get the first element of the array
	objective_ = new Objective(objectiveType, objectiveRoomId);
}

void Game::initializePlayer_(const json& jsonData) {
	string initialRoom = jsonData["player"]["initialroom"].get<string>();
	player_ = new Player(initialRoom);
}

void Game::initializeRooms_(const json& jsonData) {
	if (jsonData.contains("rooms") && jsonData["rooms"].is_array()) {
		for (const auto& roomData : jsonData["rooms"]) {
			const string roomId = roomData["id"].get<string>();
			const string roomDescription = roomData["desc"].get<string>();
			Room* room = new Room(roomId, roomDescription);
			rooms_[roomId] = room;
		}

		for (const auto& roomData : jsonData["rooms"]) {
			const string currentRoomId = roomData["id"].get<string>();
			Room* currentRoom = rooms_[currentRoomId];

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

void Game::initializeObjects_(const json& jsonData) {
	if (jsonData.contains("objects") && jsonData["objects"].is_array()) {
		for (const auto& objectData : jsonData["objects"]) {
			string objectId = objectData["id"].get<string>();

			string objectDescription = Object::DEFAULT_DESCRIPTION; // Use a default value
			if (objectData.contains("desc") && objectData["desc"].is_string()) {
				objectDescription = objectData["desc"].get<string>();
			}

			string initialLocationId = Object::DEFAULT_LOCATION; // Use a default value
			if (objectData.contains("initialroom") && objectData["initialroom"].is_string()) {
				initialLocationId = objectData["initialroom"].get<string>();
			}

			int durability = Object::DEFAULT_DURABILITY; // Use a default value
			if (objectData.contains("durability") && objectData["durability"].is_number_integer()) {
				durability = objectData["durability"].get<int>();
			}

			Object* newObject = new Object(objectId, objectDescription, initialLocationId, durability);
			objects_[objectId] = newObject;

			// Add the object to the player or a room based on initial location
			if (rooms_.find(initialLocationId) != rooms_.end()) {
				Room* initialRoom = rooms_[initialLocationId];
				initialRoom->addObject(newObject);
				continue;
			}

			// If room does not exists the object is automatically handed to the player
			player_->addObject(newObject);
		}
	}
}

void Game::initializeEnemies_(const json& jsonData) {
	if (jsonData.contains("enemies") && jsonData["enemies"].is_array()) {
		for (const auto& enemyData : jsonData["enemies"]) {
			string enemyId = enemyData["id"].get<string>();

			string enemyDescription = Enemy::DEFAULT_DESCRIPTION; // Use a default value
			if (enemyData.contains("desc") && enemyData["desc"].is_string()) {
				enemyDescription = enemyData["desc"].get<string>();
			}

			int enemyAggressiveness = Enemy::DEFAULT_AGGRESSIVENESS; // Use a default value
			if (enemyData.contains("aggressiveness") && enemyData["aggressiveness"].is_number_integer()) {
				enemyAggressiveness = enemyData["aggressiveness"].get<int>();
			}

			string canBeKilledBy = Enemy::DEFAULT_KILLED_BY; // Use a default value
			if (enemyData.contains("killedby") && enemyData["killedby"].is_string()) {
				canBeKilledBy = enemyData["killedby"].get<string>();
			}

			Enemy* newEnemy = new Enemy(enemyId, enemyDescription, canBeKilledBy, enemyAggressiveness);
			enemies_[enemyId] = newEnemy;

			// Add the enemy to its initial room
			if (enemyData.contains("initialroom") && enemyData["initialroom"].is_string()) {
				string initialRoomId = enemyData["initialroom"].get<string>();
				Room* room = rooms_[initialRoomId];
				room->addEnemy(newEnemy);
			}

			// Automatically removes the boss from the game if the room is not found.
		}
	}
}

string Game::actionLook_(const string& value1, const string& value2)
{
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	if (value1 == "room") {
		return currentRoom->look();
	}

	if (value1 == "around") {
		return currentRoom->lookAround();
	}

	if (value1 == "player") {
		return player_->check();
	}

	if (value1 == "objective") {
		return objective_->check();
	}

	if (!value2.empty()) {
		return "Invalid Command for looking " + value1 + "\n";
	}

	if (value1 == "enemy") {
		map<string, Enemy*> currentEnemies = currentRoom->getEnemies();
		if (currentEnemies.find(value2) == currentEnemies.end()) {
			return "Invalid enemyId\n";
		}

		Enemy* currentEnemy = currentEnemies[value2];
		return currentEnemy->look();
	}

	if (value1 == "object") {
		map<string, Object*> currentObjects = currentRoom->getObjects();
		if (currentObjects.find(value2) != currentObjects.end()) {
			Object* currentObject = currentObjects[value2];
			return currentObject->look();
		}

		map<string, Object*> currentPickedObjects = player_->getObjects();
		if (currentPickedObjects.find(value1) != currentPickedObjects.end()) {
			Object* currentPickedObject = currentPickedObjects[value1];
			return currentPickedObject->look();
		}

		return "Invalid objectId\n";
	}
	if (value1 == "enemy") {
		map<string, Enemy*> currentEnemies = currentRoom->getEnemies();
		if (currentEnemies.find(value2) == currentEnemies.end()) {
			return "Invalid enemyId\n";
		}

		Enemy* currentEnemy = currentEnemies[value2];
		return currentEnemy->look();
	}

	if (value1 == "object") {
		map<string, Object*> currentObjects = currentRoom->getObjects();
		if (currentObjects.find(value2) != currentObjects.end()) {
			Object* currentObject = currentObjects[value2];
			return currentObject->look();
		}

		map<string, Object*> currentPickedObjects = player_->getObjects();
		if (currentPickedObjects.find(value1) != currentPickedObjects.end()) {
			Object* currentPickedObject = currentPickedObjects[value1];
			return currentPickedObject->look();
		}

		return "Invalid objectId\n";
	}

	return "Invalid commmand for look\n";
}

string Game::actionPick_(const string& objectId)
{
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	map<string, Object*> currentObjects = currentRoom->getObjects();
	if (currentObjects.find(objectId) == currentObjects.end()) {
		return "Invalid ObjectId\n";
	}

	Object* currentObject = currentObjects[objectId];
	currentRoom->removeObject(currentObject);
	player_->addObject(currentObject);

	if (objectId == objective_->getTargetId()) {
		isGameOver_ = true;
		return "You have found the required object " + objectId + "!!";
	}

	return "Picked up object.\n";
}

string Game::actionDrop_(const string& objectId)
{
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	map<string, Object*> currentObjects = player_->getObjects();
	if (currentObjects.find(objectId) == currentObjects.end()) {
		return "Invalid ObjectId\n";
	}

	Object* currentObject = currentObjects[objectId];
	player_->removeObject(currentObject);
	currentRoom->addObject(currentObject);
	return "Dropped object.\n";
}

string Game::actionGoto_(const string& direction)
{
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];
	Room* exitRoom = currentRoom->getExit(direction);

	if (exitRoom == nullptr) {
		return "Current room does not have exit to " + direction + "\n";
	}

	string roomId = exitRoom->getId();
	if (rooms_.find(roomId) == rooms_.end()) {
		return "Invalid roomId\n";
	}

	std::stringstream ss;

	if (currentRoom->hasEnemy()) {
		int totalAggressiveness = 0;
		for (const auto& enemyPair : currentRoom->getEnemies()) {
			Enemy* enemy = enemyPair.second;
			int enemyAgressiveness = enemy->getAggressiveness();
			totalAggressiveness += enemy->getAggressiveness();
			ss << "Health reduced by " << enemyAgressiveness << " as this room had enemy " << enemyPair.first << endl;
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

	Room* gotoRoom = rooms_[roomId];
	player_->setLocation(roomId);
	ss << "Moved to Room " + roomId << endl;

	if (!gotoRoom->hasExits()) {
		ss << "You have entered a trap room with no exits." << endl;
		isGameOver_ = true;
		return ss.str();
	}
	
	if (roomId == objective_->getTargetId()) {
		if (!gotoRoom->hasEnemy()) {
			ss << "You have reached the targeted room." << endl;
			ss << "You have cleared the objective as there are no enemies in the room! " << endl;;
			isGameOver_ = true;
			return ss.str();
		}

		ss << "You have reached the targeted room. Please kill the remaining enemies to win the game." << endl;;
	}

	return ss.str();
}

string Game::actionAttack_(const string& enemyId, const string& objectId)
{
	string currentRoomId = player_->getLocation();
	Room* currentRoom = rooms_[currentRoomId];

	map<string, Enemy*> currentEnemies = currentRoom->getEnemies();
	if (currentEnemies.find(enemyId) == currentEnemies.end()) {
		return "No enemy with ID " + enemyId + " in the current room.\n";
	}

	map<string, Object*> currentPickedObjects = player_->getObjects();
	if (currentPickedObjects.find(objectId) == currentPickedObjects.end()) {
		return "No object with ID " + objectId + " in player's possession.\n";
	}

	Enemy* currentEnemy = currentEnemies[enemyId];
	Object* currentPickedObject = currentPickedObjects[objectId];

	int enemyAggressiveness = currentEnemy->getAggressiveness();
	int objectDurability = currentPickedObject->getDurability();

	// Attack logic
	int updatedAgressiveness = std::max(0, enemyAggressiveness - objectDurability);
	int updatedDurability = std::max(0, objectDurability - enemyAggressiveness);

	currentEnemy->setAggressiveness(updatedAgressiveness);
	currentPickedObject->setDurability(updatedDurability);

	std::stringstream ss;

	if (currentEnemy->getAggressiveness() <= 0) {
		currentRoom->removeEnemy(currentEnemy);
		delete currentEnemy;  // Assuming dynamic allocation of enemies
		ss << "Enemy " << enemyId << " has been defeated!" << endl;
		if (objective_->getTargetId() == currentRoomId) {
			isGameOver_ = true;
		}
	}
	else {
		ss << "Enemy has been attacked and aggressiveness is reduced to " << updatedAgressiveness << endl;
	}

	if (currentPickedObject->getDurability() <= 0) {
		player_->removeObject(currentPickedObject);
		delete currentPickedObject;  // Assuming dynamic allocation of objects
		ss << "Object " << objectId << " has been destroyed!" << endl;
	}
	else {
		ss << "Object has been used and durability is reduced to " << updatedDurability << endl;
	}

	return ss.str();
}

string Game::actionStatus_() {
	std::stringstream ss;
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
