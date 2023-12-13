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

Game::~Game() {

	if (player_ != nullptr) {
		delete player_;
		player_ = nullptr;
	}

	if (objective_ != nullptr) {
		delete objective_;
		objective_ = nullptr;
	}

	for (auto& enemyPair : enemies_) {
		if (enemyPair.second != nullptr) {
			delete enemyPair.second;
		}
	}
	enemies_.clear();

	for (auto& roomPair : rooms_) {
		if (roomPair.second != nullptr) {
			delete roomPair.second;
		}
	}
	rooms_.clear();

	for (auto& objectPair : objects_) {
		if (objectPair.second != nullptr) {
			delete objectPair.second;
		}
	}
	objects_.clear();
}

bool Game::isGameOver() const {
	return isGameOver_;
}

string Game::performCommand(const string& action, const string& value1, const string& value2) {

	if (action == "exit") {
		isGameOver_ = true;
		return "You quit the game!\n";
	}

	if (action == "status") {
		return actionStatus_();
	}

	if (action == "commands") {
		return actionCommands_();
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

	// Default case for invalid commands
	return "Invalid Command for " + action + "\n";
}

// Displays a list of available actions to the player
string Game::actionCommands_() const {
	std::stringstream ss;

	ss << "Available Commands:\n";
	ss << "1. Commands - Shows the Action menu.\n";
	ss << "   Usage: Type 'commands' to get this list of commands.\n";
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

void Game::initializeObjective_(const json& jsonData) {
	string objectiveType = jsonData["objective"]["type"].get<string>();
	vector <string> objectiveRoomId = jsonData["objective"]["what"].get<vector<string>>();

	objective_ = new Objective(objectiveType, objectiveRoomId);
}

void Game::initializePlayer_(const json& jsonData) {
	string initialRoomId = jsonData["player"]["initialroom"].get<string>();
	Room* initialRoom = rooms_[initialRoomId];
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
			string objectDescription = objectData["desc"].get<string>();
			string initialLocationId = objectData["initialroom"].get<string>();
			Object* newObject = new Object(objectId, objectDescription, initialLocationId);

			objects_[objectId] = newObject;

			if (rooms_.find(initialLocationId) != rooms_.end()) {
				Room* initialRoom = rooms_[initialLocationId];
				initialRoom->addObject(newObject);
			}
		}
	}
}

void Game::initializeEnemies_(const json& jsonData) {
	if (jsonData.contains("enemies") && jsonData["enemies"].is_array()) {
		for (const auto& enemyData : jsonData["enemies"]) {

			string enemyId = enemyData["id"].get<string>();
			string enemyDescription = enemyData["desc"].get<string>();
			int enemyAggressiveness =  enemyData["aggressiveness"].get<int>();
			vector<string> canBeKilledBy = enemyData["killedby"].get<vector<string>>();
			Enemy* newEnemy = new Enemy(enemyId, enemyDescription, canBeKilledBy, enemyAggressiveness);
			enemies_[enemyId] = newEnemy;

			if (enemyData.contains("initialroom") && enemyData["initialroom"].is_string()) {
				string initialRoomId = enemyData["initialroom"].get<string>();
				Room* room = rooms_[initialRoomId];
				room->addEnemy(newEnemy);
			}
		}
	}
}

string Game::actionLook_(const string& value1, const string& value2) {

	if (value1 == "room") {
		return player_->getLocation()->look();
	}

	if (value1 == "around") {
		return player_->getLocation()->lookAround();
	}

	if (value1 == "player") {
		return player_->check();
	}

	if (value1 == "objective") {
		return objective_->check();
	}

	if (value1 == "enemy" || value1 == "object") {
		Enemy* currentEnemy = player_->getLocation()->getEnemy(value2);
		if (value1 == "enemy" && currentEnemy != nullptr) {
			return currentEnemy->look();
		}

		Object* currentObject = player_->getLocation()->getObject(value2);
		if (value1 == "object" && currentObject != nullptr) {
			return currentObject->look();
		}

		return "Invalid " + value1 + "Id\n";
	}

	return "Invalid command for look\n";
}

string Game::actionPick_(const string& objectId) {

	Object* currentObject = player_->getLocation()->getObject(objectId);
	if (currentObject  == nullptr) {
		return "Invalid ObjectId\n";
	}

	player_->setObject(currentObject);
	player_->getLocation()->removeObject(currentObject);

	if (objective_->isTargetId(objectId)) {
		isGameOver_ = true;
		return "You have found the required object " + objectId + "!!";
	}

	return "Picked up object.\n";
}

string Game::actionDrop_(const string& objectId) {
	string currentRoomId = player_->getLocation()->getId();
	Room* currentRoom = rooms_[currentRoomId];

	Object* currentObject = player_->getObject();

	currentRoom->removeObject(currentObject);
	player_->setObject(nullptr);

	return "Dropped object.\n";
}

string Game::actionGoto_(const string& direction) {
	string currentRoomId = player_->getLocation()->getId();
	Room* currentRoom = rooms_[currentRoomId];
	Room* exitRoom = currentRoom->getExit(direction);

	if (exitRoom == nullptr) {
		return "Current room does not have exit to " + direction + "\n";
	}

	string roomId = exitRoom->getId();
	if (rooms_.find(roomId) == rooms_.end()) {
		return "Invalid roomId\n";
	}

	player_->setLocation(exitRoom);

	if (!exitRoom->hasExits()) {
		isGameOver_ = true;
		return "You have moved to entered a trap room with no exits.\n";
	}

	if (objective_->isTargetId(roomId)) {
		isGameOver_ = true;
		return "You have reached the targeted room.\n";
	}

	return "You have moved to " + roomId;
}

string Game::actionAttack_(const string& enemyId, const string& objectId) {

	Enemy* currentEnemy = player_->getLocation()->getEnemy(enemyId);
	if (currentEnemy == nullptr) {
		return "No enemy with ID " + enemyId + " in the current room.\n";
	}

	if (objectId == "" && currentEnemy->getAggressiveness() <= 50) {
		return "You defeated the enemy with the fists";
	}

	Object* currentObject = player_->getLocation()->getObject(objectId);
	if (currentObject == nullptr) {
		currentObject = player_->getObject();
		if (currentObject == nullptr) {
			return "No object with ID " + objectId + " in player's possession.\n";
		}
	}

	if (currentEnemy->canBeKilledBy(objectId)) {
		player_->getLocation()->removeEnemy(currentEnemy);
		delete currentEnemy;

		player_->setObject(nullptr);
		delete currentObject;

		return "Enemy Killed!";
		if (objective_->isTargetId(enemyId)) {
			return "You have cleared the round after defeating one of the bosses";
			isGameOver_ = true;
		}
	}

	isGameOver_ = true;
	return "Attack failed !" + enemyId + " killed you as it cannot be defeated with " + objectId;
}


string Game::actionStatus_() {
	stringstream ss;

	ss << "----------------------------- Current Status -----------------------------" << endl;
	ss << actionLook_("player")  << endl;
	ss << actionLook_("objective") << endl;
	ss << actionLook_("room") << endl;
	ss << "--------------------------------------------------------------------------" << endl;

	return ss.str();
}
