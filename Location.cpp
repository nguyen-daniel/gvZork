#include "Location.h"
#include <iostream>

// Constructor
Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false) {}

// Neighbor management
void Location::add_location(const std::string& direction, Location* location) {
    if (direction.empty()) throw std::invalid_argument("Direction cannot be blank.");
    if (neighbors.find(direction) != neighbors.end()) throw std::invalid_argument("Direction already exists.");
    neighbors[direction] = location;
}

std::map<std::string, Location*> Location::get_locations() const { return neighbors; }

// NPC management
void Location::add_npc(const NPC& npc) { npcs.push_back(npc); }
std::vector<NPC> Location::get_npcs() const { return npcs; }

// Item management
void Location::add_item(const Item& item) { items.push_back(item); }
std::vector<Item> Location::get_items() const { return items; }

// Visited status
void Location::set_visited() { visited = true; }
bool Location::get_visited() const { return visited; }

//getter
std::string Location::get_name() const { return name; }

// Overloaded stream operator
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << "- " << location.description << "\n";
    os << "You see the following NPCs: ";
    if (location.npcs.empty()) os << "None\n";
    else {
        for (const auto& npc : location.npcs) os << "- " << npc.get_name() << "\n";
    }
    os << "You see the following Items: ";
    if (location.items.empty()) os << "None\n";
    else {
        for (const auto& item : location.items) os << "- " << item << "\n";
    }
    os << "You can go in the following Directions:\n";
    for (const auto& [dir, loc] : location.neighbors) {
        os << "- " << dir << "- " << loc->get_name() << (loc->get_visited() ? " (Visited)" : " (Unknown)") << "\n";
    }
    return os;
}