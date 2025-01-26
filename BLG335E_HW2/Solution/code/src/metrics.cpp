#include "methods.h"

int getMax(std::vector<Item>& items, const std::string& attribute)
{
    if (items.empty()){
        // if empty terminate early
        return 0;
    }

    // iterate based on attribute
    if (attribute == "age") {
        int max_val = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].age > max_val){
                max_val = items[i].age;
            }
        }
        return max_val;

    } else if (attribute == "type") {
        int max_val = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].type > max_val){
                max_val = items[i].type;
            }
        }
        return max_val;

    } else if (attribute == "origin") {
        int max_val = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].origin > max_val){
                max_val = items[i].origin;
            }
        }
        return max_val;

    } else if (attribute == "rarityScore") {
        double max_val = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].rarityScore > max_val){
                max_val = items[i].rarityScore;
            }
        }
        return int(max_val); // turn double into int
    } else {
        return 0;
    }
}

// min = age - ageWindow
// max = age + ageWindow
// rarityScore = (1 - probability) * (1 + item.age/ageMax)
void calculateRarityScores(std::vector<Item>& items, int ageWindow) {
    // Find the maximum age in the dataset
    int ageMax = getMax(items, "age");
    std::cout << "Maximum Age: " << ageMax << std::endl;

    // Iterate over each item
    for (auto& item : items) {
        int similar_count = 0;
        int total_count = 0;

        int min = item.age - ageWindow;
        int max = item.age + ageWindow;

        for (const auto& comparable_item : items) {
            if (comparable_item.age >= min && comparable_item.age <= max) {
                // Count similar items based on type and origin
                if (item.type == comparable_item.type && item.origin == comparable_item.origin) {
                    similar_count++;
                }
                total_count++;
            }
        }

        // probability P
        double P = (total_count > 0) ? double(similar_count) / total_count : 0.0;

        // rarity score
        item.rarityScore = (1 - P) * (1 + double(item.age) / ageMax);
    }
}