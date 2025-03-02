#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <vector>
#include "Item.h"
#include "NPC.h"

class Location {
private:
    std::string name;
    std::string description;
    bool visited;
    std::map<std::string, Location*> neighbors;
    std::vector<NPC> npcs;
    std::vector<Item> items;

public:
    // Constructor
    Location(const std::string& name, const std::string& description);

    // Neighbor management
    void add_location(const std::string& direction, Location* location);
    std::map<std::string, Location*> get_locations() const;

    // NPC management
    void add_npc(const NPC& npc);
    std::vector<NPC> get_npcs() const;

    // Item management
    void add_item(const Item& item);
    std::vector<Item> get_items() const;

    // Visited status
    void set_visited();
    bool get_visited() const;

    // Name getter
    std::string get_name() const;

    // Overloaded stream operator
    friend std::ostream& operator<<(std::ostream& os, const Location& location);
};

#endif