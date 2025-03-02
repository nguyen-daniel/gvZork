/**
* @file Game.cpp
 * @author [Your Name(s)] ([Your Email(s)])
 * @date [Date]
 * @brief Implementation of the Game class for GVZork.
 *
 * This file contains the implementation of the Game class, which serves as the core
 * logic for the GVZork text-based adventure game. The Game class manages the game
 * world, player interactions, and the command system using the Command Pattern.
 * It also handles the game loop, inventory management, and win/lose conditions.
 */

#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

/**
 * @brief Constructor for the Game class.
 *
 * Initializes the game by setting up the world, commands, and default values.
 * The player's starting location is randomly selected from the available locations.
 */
Game::Game() : current_weight(0), calories_needed(500), in_progress(true) {
    create_world();
    commands = setup_commands();
    current_location = random_location();
}

/**
 * @brief Creates the game world with Locations, NPCs, and Items.
 *
 * This method initializes all Locations, NPCs, and Items in the game. It connects
 * Locations via their neighbor maps and populates them with NPCs and Items.
 * Each Location is created with a name, description, and relationships to other
 * Locations. NPCs and Items are added to their respective Locations.
 */
void Game::create_world() {
    // Example Locations
    Location* padnos = new Location("Padnos Hall", "Lots of science labs are in this building.");
    Location* zumberge = new Location("Zumberge Field", "A large open field on campus.");
    Location* kirkhoff = new Location("Kirkhoff Center", "The student union with restaurants and stores.");
    Location* woods = new Location("Woods", "A mysterious forest behind campus.");

    // Add neighbors
    padnos->add_location("east", zumberge);
    zumberge->add_location("west", padnos);
    zumberge->add_location("north", kirkhoff);
    kirkhoff->add_location("south", zumberge);
    kirkhoff->add_location("west", woods);
    woods->add_location("east", kirkhoff);

    // Add NPCs
    std::vector<std::string> elf_messages = {"Bring me food!", "I need 500 calories!", "You're almost there!"};
    NPC elf("Elf", "A magical creature who can save GVSU.", elf_messages);
    woods->add_npc(elf);

    // Add Items
    Item cookie("Cookie", "A delicious M&M cookie.", 10, 0.5);
    Item nail("Rusty Nail", "A rusty nail (I hope you've had a tetanus shot).", 0, 1);
    padnos->add_item(cookie);
    zumberge->add_item(nail);

    // Store locations
    locations.push_back(*padnos);
    locations.push_back(*zumberge);
    locations.push_back(*kirkhoff);
    locations.push_back(*woods);
}

/**
 * @brief Sets up the command map for the game.
 *
 * This method creates a map of commands, where each key is a string representing
 * a command (e.g., "talk", "take"), and each value is a function pointer to the
 * corresponding method. It allows for flexible and extensible command handling.
 *
 * @return A map of commands and their associated functions.
 */
std::map<std::string, std::function<void(std::vector<std::string>)>> Game::setup_commands() {
    std::map<std::string, std::function<void(std::vector<std::string>)>> cmds;
    cmds["help"] = [this](std::vector<std::string> tokens) { show_help(tokens); };
    cmds["talk"] = [this](std::vector<std::string> tokens) { talk(tokens); };
    cmds["meet"] = [this](std::vector<std::string> tokens) { meet(tokens); };
    cmds["take"] = [this](std::vector<std::string> tokens) { take(tokens); };
    cmds["give"] = [this](std::vector<std::string> tokens) { give(tokens); };
    cmds["go"] = [this](std::vector<std::string> tokens) { go(tokens); };
    cmds["items"] = [this](std::vector<std::string> tokens) { show_items(tokens); };
    cmds["look"] = [this](std::vector<std::string> tokens) { look(tokens); };
    cmds["quit"] = [this](std::vector<std::string> tokens) { quit(tokens); };
    cmds["teleport"] = [this](std::vector<std::string> tokens) { teleport(tokens); };
    cmds["magic"] = [this](std::vector<std::string> tokens) { magic(tokens); };
    return cmds;
}

/**
 * @brief Selects a random Location from the game world.
 *
 * This method generates a random index and returns the corresponding Location
 * from the `locations` vector.
 *
 * @return A pointer to a randomly selected Location.
 */
Location* Game::random_location() {
    srand(time(nullptr));
    int index = rand() % locations.size();
    return &locations[index];
}

/**
 * @brief The core game loop.
 *
 * This method runs the main game loop, prompting the player for input and
 * executing commands until the game ends. It handles user input, tokenizes it,
 * and executes the corresponding command from the command map.
 */
void Game::play() {
    std::cout << "Welcome to GVZork!\n";
    std::cout << "Your goal is to collect edible items and bring them to the Elf in the Woods.\n";
    std::cout << "Type 'help' for a list of commands.\n";

    while (in_progress) {
        std::cout << "\nYou are at: " << *current_location << "\n";
        std::cout << "What is your command? ";
        std::string input;
        std::getline(std::cin, input);

        // Tokenize input
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        std::string command = tokens[0];
        tokens.erase(tokens.begin());

        // Execute command
        if (commands.find(command) != commands.end()) {
            commands[command](tokens);
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    // End game message
    if (calories_needed <= 0) {
        std::cout << "Congratulations! The Elf has enough calories to save GVSU!\n";
    } else {
        std::cout << "You failed to save GVSU. Better luck next time!\n";
    }
}

/**
 * @brief Displays help information and the current time.
 *
 * This method prints a list of available commands and the current time.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::show_help(std::vector<std::string> tokens) {
    std::cout << "Available commands:\n";
    for (const auto& cmd : commands) {
        std::cout << "- " << cmd.first << "\n";
    }
    std::time_t now = std::time(nullptr);
    std::cout << "Current time: " << std::ctime(&now);
}

/**
 * @brief Allows the player to talk to an NPC.
 *
 * This method checks if the specified NPC is in the current Location. If found,
 * it retrieves and prints the NPC's current message.
 *
 * @param tokens A vector containing the name of the NPC to talk to.
 */
void Game::talk(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "Who do you want to talk to?\n";
        return;
    }

    std::string target = tokens[0];
    for (auto& npc : current_location->get_npcs()) {
        if (npc.get_name() == target) {
            std::cout << npc.get_message() << "\n";
            return;
        }
    }
    std::cout << "No such NPC in this location.\n";
}

/**
 * @brief Allows the player to meet an NPC.
 *
 * This method checks if the specified NPC is in the current Location. If found,
 * it retrieves and prints the NPC's description.
 *
 * @param tokens A vector containing the name of the NPC to meet.
 */
void Game::meet(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "Who do you want to meet?\n";
        return;
    }

    std::string target = tokens[0];
    for (auto& npc : current_location->get_npcs()) {
        if (npc.get_name() == target) {
            std::cout << npc.get_description() << "\n";
            return;
        }
    }
    std::cout << "No such NPC in this location.\n";
}

/**
 * @brief Allows the player to take an Item.
 *
 * This method checks if the specified Item is in the current Location. If found,
 * it adds the Item to the player's inventory and updates the carried weight.
 *
 * @param tokens A vector containing the name of the Item to take.
 */
void Game::take(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "What do you want to take?\n";
        return;
    }

    std::string target = tokens[0];
    for (auto& item : current_location->get_items()) {
        if (item.get_name() == target) {
            if (current_weight + item.get_weight() > 30) {
                std::cout << "You cannot carry that much weight.\n";
                return;
            }
            inventory.push_back(item);
            current_weight += item.get_weight();
            std::cout << "You took the " << item.get_name() << ".\n";
            current_location->get_items().erase(
                std::remove_if(current_location->get_items().begin(), current_location->get_items().end(),
                               [&item](const Item& i) { return i.get_name() == item.get_name(); }),
                current_location->get_items().end());
            return;
        }
    }
    std::cout << "No such item in this location.\n";
}

/**
 * @brief Allows the player to give an Item to the Elf.
 *
 * This method checks if the specified Item is in the player's inventory. If found,
 * it removes the Item from the inventory and updates the carried weight. If the
 * current Location is the Woods, it checks if the Item is edible. If edible, it
 * reduces the Elf's calorie requirement; otherwise, it teleports the player to a
 * random Location.
 *
 * @param tokens A vector containing the name of the Item to give.
 */
void Game::give(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "What do you want to give?\n";
        return;
    }

    std::string target = tokens[0];
    for (auto& item : inventory) {
        if (item.get_name() == target) {
            if (current_location->get_name() == "Woods") {
                if (item.get_calories() > 0) {
                    calories_needed -= item.get_calories();
                    std::cout << "You gave the Elf " << item.get_calories() << " calories.\n";
                    if (calories_needed <= 0) {
                        in_progress = false;
                    }
                } else {
                    std::cout << "The Elf is displeased and teleports you away!\n";
                    current_location = random_location();
                }
            } else {
                std::cout << "You can only give items to the Elf in the Woods.\n";
            }
            inventory.erase(
                std::remove_if(inventory.begin(), inventory.end(),
                               [&item](const Item& i) { return i.get_name() == item.get_name(); }),
                inventory.end());
            current_weight -= item.get_weight();
            return;
        }
    }
    std::cout << "No such item in your inventory.\n";
}

/**
 * @brief Allows the player to move to a neighboring Location.
 *
 * This method checks if the specified direction exists in the current Location's
 * neighbor map. If valid, it updates the player's current Location.
 *
 * @param tokens A vector containing the direction to move.
 */
void Game::go(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "Where do you want to go?\n";
        return;
    }

    std::string direction = tokens[0];
    auto neighbors = current_location->get_locations();
    if (neighbors.find(direction) != neighbors.end()) {
        current_location->set_visited();
        current_location = neighbors[direction];
        std::cout << "You moved " << direction << ".\n";
    } else {
        std::cout << "You cannot go that way.\n";
    }
}


/**
 * @brief Displays the player's inventory and carried weight.
 *
 * This method prints all Items in the player's inventory and the total weight
 * currently being carried.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::show_items(std::vector<std::string> tokens) {
    if (inventory.empty()) {
        std::cout << "You are not carrying any items.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (const auto& item : inventory) {
            std::cout << "- " << item << "\n";
        }
        std::cout << "Total weight: " << current_weight << " lb\n";
    }
}

/**
 * @brief Displays details about the current Location.
 *
 * This method prints the current Location's description, NPCs, Items, and
 * available directions to move.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::look(std::vector<std::string> tokens) {
    std::cout << *current_location << "\n";
}

/**
 * @brief Ends the game.
 *
 * This method prints a failure message and terminates the game loop.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::quit(std::vector<std::string> tokens) {
    std::cout << "Quitting the game. Goodbye!\n";
    in_progress = false;
}

/**
 * @brief Teleports the player to a random Location.
 *
 * This method sets the player's current Location to a randomly selected one.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::teleport(std::vector<std::string> tokens) {
    current_location = random_location();
    std::cout << "You have been teleported to " << current_location->get_name() << ".\n";
}

/**
 * @brief Reduces the player's carried weight by half.
 *
 * This method halves the player's current weight, simulating a magical effect.
 *
 * @param tokens Unused parameter included for consistency with other commands.
 */
void Game::magic(std::vector<std::string> tokens) {
    std::cout << "Magic happens! Your inventory weight is halved.\n";
    current_weight /= 2;
}