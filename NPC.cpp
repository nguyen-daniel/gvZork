#include "NPC.h"
#include <iostream>

// Constructor
NPC::NPC(const std::string& name, const std::string& description, const std::vector<std::string>& messages)
    : name(name), description(description), message_number(0), messages(messages) {
    if (name.empty()) throw std::invalid_argument("Name cannot be blank.");
    if (description.empty()) throw std::invalid_argument("Description cannot be blank.");
}

// Getters
std::string NPC::get_name() const { return name; }
std::string NPC::get_description() const { return description; }

// Get current message and update message number
std::string NPC::get_message() {
    if (messages.empty()) return "No messages available.";
    std::string current_message = messages[message_number];
    message_number = (message_number + 1) % messages.size();
    return current_message;
}

// Overloaded stream operator
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    return os;
}