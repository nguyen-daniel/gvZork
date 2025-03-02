#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>

class NPC {
private:
    std::string name;
    std::string description;
    int message_number;
    std::vector<std::string> messages;

public:
    // Constructor
    NPC(const std::string& name, const std::string& description, const std::vector<std::string>& messages);

    // Getters
    std::string get_name() const;
    std::string get_description() const;

    // Get current message and update message number
    std::string get_message();

    // Overloaded stream operator
    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
};

#endif