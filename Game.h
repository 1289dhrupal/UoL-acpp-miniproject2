#pragma once

#include <string>
#include <map>
#include "json.hpp"

#include "Enemy.h"
#include "Object.h"
#include "Objective.h"
#include "Player.h"
#include "Room.h"

using json = nlohmann::json;
using namespace std;

// Ensure that Game class is only defined once
#ifndef GAME_H
#define GAME_H

// The Game class represents the main game logic. 
// It manages game state, player actions, and interactions within the game world.
class Game {
public:
    // Constructor: Initializes a new Game instance using JSON data.
    // jsonData: JSON object containing game initialization data.
    explicit Game(const json& jsonData);

    // Destructor: Cleans up the game's allocated resources.
    ~Game();

    // displayActions: Displays available actions to the player.
    string displayActions() const;

    // performCommand: Performs a command given by the player.
    // action: The command to perform.
    // value1: The first optional argument for the command.
    // value2: The second optional argument for the command.
    string performCommand(const string& action, const string& value1 = "", const string& value2 = "");

    // isGameOver: Checks if the game is over.
    bool isGameOver() const;

private:
    // Pointers to various game elements.
    Player* player_ = nullptr;
    Objective* objective_ = nullptr;
    map<string, Enemy*> enemies_;
    map<string, Room*> rooms_;
    map<string, Object*> objects_;

    // Flag to track if the game is over.
    bool isGameOver_ = false;

    // Methods to initialize game components from JSON data.
    void initializePlayer_(const json& jsonData);
    void initializeObjective_(const json& jsonData);
    void initializeRooms_(const json& jsonData);
    void initializeObjects_(const json& jsonData);
    void initializeEnemies_(const json& jsonData);

    // Action methods corresponding to different player commands.
    string actionLook_(const string& value1, const string& value2 = "");
    string actionPick_(const string& objectId);
    string actionDrop_(const string& objectId);
    string actionGoto_(const string& direction);
    string actionAttack_(const string& enemyId, const string& objectId);
    string actionStatus_();
};

#endif // GAME_H
