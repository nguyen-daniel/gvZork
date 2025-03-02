#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>
#include <functional>
#include "Location.h"
#include "Item.h"

class Game {
private:
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
    std::vector<Item> inventory;
    int current_weight;
    std::vector<Location> locations;
    Location* current_location;
    int calories_needed;
    bool in_progress;

    // Helper methods
    void create_world();
    std::map<std::string, std::function<void(std::vector<std::string>)>> setup_commands();
    Location* random_location();

public:
    // Constructor
    Game();

    // Core game loop
    void play();

    // Command methods
    void show_help(std::vector<std::string> tokens);
    void talk(std::vector<std::string> tokens);
    void meet(std::vector<std::string> tokens);
    void take(std::vector<std::string> tokens);
    void give(std::vector<std::string> tokens);
    void go(std::vector<std::string> tokens);
    void show_items(std::vector<std::string> tokens);
    void look(std::vector<std::string> tokens);
    void quit(std::vector<std::string> tokens);

    // Custom commands
    void teleport(std::vector<std::string> tokens);
    void magic(std::vector<std::string> tokens);
};

#endif