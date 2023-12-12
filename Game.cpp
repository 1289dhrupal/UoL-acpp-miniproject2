#include "Game.h"
#include "Player.h"

Game::Game(const json& jsonData)
{

	initializePlayer_(jsonData);
	initializeObjective_(jsonData);
	initializeRooms_(jsonData);

	initializeEnemies_(jsonData);
	initializeObjects_(jsonData);
	// int agg = j["enemies"][0]["aggressiveness"].get<int>();
}

void Game::initializePlayer_(const json& jsonData) {
	string playerLocation = "room1";
	player_ = new Player(playerLocation);
}

void Game::initializeObjective_(const json& jsonData) {
	string objectiveType = "room";
	string objectiveRoomId = "room3";
	objective_ = new Objective(objectiveType, objectiveRoomId);
}

void Game::initializeRooms_(const json& jsonData) {
	if (jsonData.contains("rooms") && jsonData["rooms"].is_array()) {
		for (const auto& roomData : jsonData["rooms"]) {
			const string roomId = jsonData["rooms"]["id"].get<string>();
			const string roomDescription = jsonData["rooms"]["desc"].get<string>();
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
	const string object1Id = "object1";
	const string object1Description = "object1 description";
	const string object1Location = "room2";
	const int object1Durability = 10;
	Object* object1 = new Object(object1Id, object1Description, object1Location, object1Durability);
	objects_[object1->getId()] = object1;

	const string object2Id = "object1";
	const string object2Description = "object2 description";
	const string object2Location = "room3";
	const int object2Durability = 10;
	Object* object2 = new Object(object2Id, object2Description, object2Location, object2Durability);
	objects_[object2->getId()] = object2;
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
				Room* room = rooms_[initialLocationId];
				room->addObject(newObject);
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

			Enemy* newEnemy = new Enemy(enemyId, enemyDescription, enemyAggressiveness);
			enemies_[enemyId] = newEnemy;

			// Add the enemy to its initial room
			string bossRoomId = objective_->getBossRoomId(); // Use a default value

			string initialRoomId = bossRoomId; // Use a default value
			if (enemyData.contains("initialroom") && enemyData["initialroom"].is_string()) {
				initialRoomId = enemyData["initialroom"].get<string>();
			}

			Room* room = rooms_[bossRoomId];
			if (rooms_.find(initialRoomId) != rooms_.end()) {
				room = rooms_[initialRoomId];
			}

			room->addEnemy(newEnemy);
		}
	}
}
