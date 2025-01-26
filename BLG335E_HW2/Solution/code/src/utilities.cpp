#include "methods.h"

std::vector<Item> readItemsFromFile(const std::string& filename) 
{
    
    std::vector<Item> items;

    try {
        std::ifstream file(filename); // ifstream bc i just wanna read it
        if (!file.is_open()) {
            throw ("Could not open file");
        }

        std::string line;
        getline(file, line);

        while (getline(file, line)) {
            Item item;
            // we learned this sscanf function last year but no one uses it
            // i think it suits better to our implementations more 
            // bc we can directly parse the string without converting the types and creating string streams etc
            sscanf(line.c_str(), "%d,%d,%d,%lf", &item.age, &item.type, &item.origin, &item.rarityScore);
            items.push_back(item);
        }

        file.close();

    } catch(const std::exception& e) { // if theres any error while reading file or parsing string it will be caught here
        std::cout << "hata" << e.what() << std::endl;
    } // i searched for smth similar to this line in py: except Exception as e:

    return items; // Return the vector of tweets whether empty or not

}

void writeItemsToFile(const std::string& filename, const std::vector<Item>& items) 
{
    std::ofstream file(filename);

    file << "age,type,origin,rarity\n";

    for (const auto& item : items) 
    {
        file << item.age << "," << item.type << "," << item.origin << "," << item.rarityScore << "\n";
    }
}