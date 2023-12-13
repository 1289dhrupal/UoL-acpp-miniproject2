#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp" // Include the JSON library header
#include "Game.h"  // Include the Game class header

int main() {

    ifstream file("map4.json");
    if (!file.is_open()) {
        cout << "Failed to open map.json" << endl;
        return 1;
    }
    string s;
    
    try {
        json jsonData;
        file >> jsonData;
        file.close();

        Game game(jsonData);

        string input;
        while (!game.isGameOver()) {
            cout << "Enter command: ";
            getline(cin, input);

            stringstream ss(input);
            string action, value1, value2;
            ss >> action >> value1 >> value2;

            string result = game.performCommand(action, value1, value2);
            cout << result << endl;
        }

        cout << "Game Over. Thank you for playing!" << endl;
    }
    catch (const exception& e) {
        cout << "Caught a runtime error: " << e.what() << std::endl;
    }

    cout << s << endl;

    return 0;
}
