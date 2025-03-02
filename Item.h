#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <stdexcept>

class Item {
private:
    std::string name;
    std::string description;
    int calories;
    float weight;

public:
    // Constructor
    Item(const std::string& name, const std::string& description, int calories, float weight);

    // Getters
    std::string get_name() const;
    std::string get_description() const;
    int get_calories() const;
    float get_weight() const;

    // Overloaded stream operator
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif