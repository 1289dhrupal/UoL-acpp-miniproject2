#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp" // Include the JSON library header
#include "Game.h"   // Include the Game class header

using namespace std;

int main() {
    // Open the file containing the game map
    ifstream file("map4.json");
    if (!file.is_open()) {
        cout << "Failed to open map.json" << endl;
        return 1;
    }

    // Variable to store the file content
    string file_content;

    try {
        // Parse the JSON data from the file
        json jsonData;
        file >> jsonData;
        file.close(); // Close the file after reading

        // Initialize the game with the JSON data
        Game game(jsonData);

        string result = game.performCommand("commands");
        cout << result << endl;

        // Variable to store user input
        string input;
        while (!game.isGameOver()) {
            cout << "Enter command: ";
            getline(cin, input);

            // Process the input command
            stringstream ss(input);
            string action, value1, value2;
            ss >> action >> value1 >> value2;

            // Execute the command in the game and output the result
            result = game.performCommand(action, value1, value2);
            cout << result << endl;
        }

        // Game over message
        cout << "Game Over. Thank you for playing!" << endl;
    }
    catch (const exception& e) {
        // Catch and display runtime errors
        cout << "Caught a runtime error: " << e.what() << endl;
    }

    return 0;
}
