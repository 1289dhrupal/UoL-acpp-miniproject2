#pragma once
#include <string>
#include <map>
#include "json.hpp"

#include "Enemy.h"
#include "Object.h"
#include "Objective.h"
#include "Player.h"
#include "Room.h"

#include <map>

using json = nlohmann::json;
using namespace std;

// Objective.h
#ifndef GAME_H
#define GAME_H

class Game {
    // Represents the game.
public:
    Game(const json& jsonData);

    string displayActions() const;

    string performCommand(const string& action, const string& value1 = "", const string& = "");

    bool isGameOver() const;
private:

    Player* player_ = nullptr;
    Objective* objective_ = nullptr;
    map<string, Enemy*> enemies_;
    map<string, Room*> rooms_;
    map<string, Object*> objects_;
    bool isGameOver_ = false;

    void initializePlayer_(const json& jsonData);

    void initializeObjective_(const json& jsonData);

    void initializeRooms_(const json& jsonData);

    void initializeObjects_(const json& jsonData);

    void initializeEnemies_(const json& jsonData);

    string actionLook_(const string& value1, const string& value2 = "");

    string actionPick_(const string& objectId);

    string actionDrop_(const string& objectId);

    string actionGoto_(const string& roomId);

    string actionAttack_(const string& enemyId, const string& objectId);

    string actionStatus_();
};

#endif // GAME_H
