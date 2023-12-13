#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp" // Include the JSON library header
#include "Game.h"   // Include the Game class header

using namespace std;

int main() {
    // Open the file containing the game map
    string filename = "map4.json";
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open " << filename << endl;
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
        while (!game.isGameOver()) {
            string command1;
            cout << "Enter command 1: ";
            getline(cin, command1);

            string command2;
            cout << "Enter command 2: ";
            getline(cin, command2);

            string command3;
            cout << "Enter command 3: ";
            getline(cin, command3);

            // Process the input command

            // Execute the command in the game and output the result
            result = game.performCommand(command1, command2, command3);
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
