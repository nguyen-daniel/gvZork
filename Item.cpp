#include "Item.h"
#include <iostream>
#include <sstream>

// Constructor
Item::Item(const std::string& name, const std::string& description, int calories, float weight) {
    if (name.empty()) throw std::invalid_argument("Name cannot be blank.");
    if (calories < 0 || calories > 1000) throw std::invalid_argument("Calories must be between 0 and 1000.");
    if (description.empty()) throw std::invalid_argument("Description cannot be blank.");
    if (weight < 0 || weight > 500) throw std::invalid_argument("Weight must be between 0 and 500.");

    this->name = name;
    this->description = description;
    this->calories = calories;
    this->weight = weight;
}

// Getters
std::string Item::get_name() const {return name;}
std::string Item::get_description() const { return description; }
int Item::get_calories() const { return calories; }
float Item::get_weight() const { return weight; }

// Overloaded stream operator
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << "(" << item.calories << " calories)- " << item.weight << " lb- " << item.description;
    return os;
}