#include "methods.h"
#include <chrono> // For benchmarking
#include <algorithm> // For std::min_element

void makeAgeColumnZero(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return;
    }
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;

    // Process each line in the CSV
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;

        // Split line into fields
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (isHeader) {
            // Write header directly to output
            outFile << line << "\n";
            isHeader = false;
        } else {
            // Update age column (first column) to 0
            if (!fields.empty()) {
                fields[0] = "0";  // Set age to 0
            }

            // Write updated row to output
            for (size_t i = 0; i < fields.size(); ++i) {
                outFile << fields[i];
                if (i < fields.size() - 1) {
                    outFile << ",";
                }
            }
            outFile << "\n";
        }
    }

    inFile.close();
    outFile.close();
    std::cout << "Age column successfully updated to 0 in file: " << outputFile << std::endl;
}

void makeRarityColumnZero(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return;
    }
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;

    // Process each line in the CSV
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;

        // Split line into fields
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (isHeader) {
            // Write header directly to output
            outFile << line << "\n";
            isHeader = false;
        } else {
            // Update age column (first column) to 0
            if (!fields.empty()) {
                fields[3] = "0";  // Set age to 0
            }

            // Write updated row to output
            for (size_t i = 0; i < fields.size(); ++i) {
                outFile << fields[i];
                if (i < fields.size() - 1) {
                    outFile << ",";
                }
            }
            outFile << "\n";
        }
    }

    inFile.close();
    outFile.close();
    std::cout << "Rarity column successfully updated to 0 in file: " << outputFile << std::endl;
}

int main() {
    // Read items from file
    std::vector<Item> items_large = readItemsFromFile("/workspaces/code/data/items_l.csv");
    std::vector<Item> items_medium = readItemsFromFile("/workspaces/code/data/items_m.csv");
    std::vector<Item> items_small = readItemsFromFile("/workspaces/code/data/items_s.csv");
    makeAgeColumnZero("/workspaces/code/data/items_l.csv", "/workspaces/code/data/items_zero.csv");
    std::vector<Item> items_zero = readItemsFromFile("/workspaces/code/data/items_zero.csv");

    // Sort items by age using Counting Sort (Large)
    auto start_large_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_large = countingSort(items_large, "age", true);
    auto end_large_sort = std::chrono::high_resolution_clock::now();
    auto duration_large_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_large_sort - start_large_sort);
    std::cout << "Execution time of sorted_ascending_age_large: " << duration_large_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_large.csv", sorted_ascending_age_large);

    // Sort items by age using Counting Sort (Medium)
    auto start_medium_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_medium = countingSort(items_medium, "age", true);
    auto end_medium_sort = std::chrono::high_resolution_clock::now();
    auto duration_medium_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_medium_sort - start_medium_sort);
    std::cout << "Execution time of sorted_ascending_age_medium: " << duration_medium_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_medium.csv", sorted_ascending_age_medium);

    // Sort items by age using Counting Sort (Small)
    auto start_small_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_small = countingSort(items_small, "age", true);
    auto end_small_sort = std::chrono::high_resolution_clock::now();
    auto duration_small_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_small_sort - start_small_sort);
    std::cout << "Execution time of sorted_ascending_age_small: " << duration_small_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_small.csv", sorted_ascending_age_small);

    // Sort items by age using Counting Sort (Reverse Large)
    auto start_reverse_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_reverse = countingSort(sorted_ascending_age_large, "age", false);
    auto end_reverse_sort = std::chrono::high_resolution_clock::now();
    auto duration_reverse_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_reverse_sort - start_reverse_sort);
    std::cout << "Execution time of sorted_ascending_age_reverse large: " << duration_reverse_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_reverse.csv", sorted_ascending_age_reverse);

    // Sort items by age using Counting Sort (Sorted Large)
    auto start_sortedd_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_sortedd = countingSort(sorted_ascending_age_large, "age", true);
    auto end_sortedd_sort = std::chrono::high_resolution_clock::now();
    auto duration_sortedd_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_sortedd_sort - start_sortedd_sort);
    std::cout << "Execution time of sorted_ascending_age_sortedd large: " << duration_reverse_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_sortedd.csv", sorted_ascending_age_sortedd);

    // Sort items by age using Counting Sort (All Zero)
    auto start_all_zero_sort = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_ascending_age_all_zero = countingSort(items_zero, "age", true);
    auto end_all_zero_sort = std::chrono::high_resolution_clock::now();
    auto duration_all_zero_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_all_zero_sort - start_all_zero_sort);
    std::cout << "Execution time of sorted_ascending_age_all_zero: " << duration_all_zero_sort.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/sorted_ascending_age_all_zero.csv", sorted_ascending_age_large);

    // Calculate rarity scores (Large)
    calculateRarityScores(sorted_ascending_age_large, 50);

    // Calculate rarity scores (Medium)
    calculateRarityScores(sorted_ascending_age_medium, 50);

    // Calculate rarity scores (Small)
    calculateRarityScores(sorted_ascending_age_small, 50);

    // Sort items by rarity score using Heap Sort (Large)
    auto start_large_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_large = heapSortByRarity(sorted_ascending_age_large, true);
    auto end_large_heap = std::chrono::high_resolution_clock::now();
    auto duration_large_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_large_heap - start_large_heap);
    std::cout << "Execution time of Heap Sort (large): " << duration_large_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_large.csv", sorted_descending_rarity_large);

    // Sort items by rarity score using Heap Sort (Medium)
    auto start_medium_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_medium = heapSortByRarity(sorted_ascending_age_medium, true);
    auto end_medium_heap = std::chrono::high_resolution_clock::now();
    auto duration_medium_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_medium_heap - start_medium_heap);
    std::cout << "Execution time of Heap Sort (medium): " << duration_medium_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_medium.csv", sorted_descending_rarity_medium);

    // Sort items by rarity score using Heap Sort (Small)
    auto start_small_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_small = heapSortByRarity(sorted_ascending_age_small, true);
    auto end_small_heap = std::chrono::high_resolution_clock::now();
    auto duration_small_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_small_heap - start_small_heap);
    std::cout << "Execution time of Heap Sort (small): " << duration_small_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_small.csv", sorted_descending_rarity_small);

    auto start_sortedd_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_sortedd = heapSortByRarity(sorted_descending_rarity_large, true);
    auto end_sortedd_heap = std::chrono::high_resolution_clock::now();
    auto duration_sortedd_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_sortedd_heap - start_sortedd_heap);
    std::cout << "Execution time of Heap Sort (sortedd): " << duration_sortedd_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_sortedd.csv", sorted_descending_rarity_sortedd);

    auto start_reverse_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_reverse = heapSortByRarity(sorted_descending_rarity_large, false);
    auto end_reverse_heap = std::chrono::high_resolution_clock::now();
    auto duration_reverse_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_reverse_heap - start_reverse_heap);
    std::cout << "Execution time of Heap Sort (reverse): " << duration_reverse_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_reverse.csv", sorted_descending_rarity_reverse);

    makeRarityColumnZero("/workspaces/code/data/new/heap_descending_rarity_large.csv", "/workspaces/code/data/rarity_zero.csv");
    std::vector<Item> rarity_zero = readItemsFromFile("/workspaces/code/data/rarity_zero.csv");

    // Sort items by rarity score using Heap Sort (Large)
    auto start_all_zero_heap = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted_descending_rarity_all_zero = heapSortByRarity(rarity_zero, true);
    auto end_all_zero_heap = std::chrono::high_resolution_clock::now();
    auto duration_all_zero_heap = std::chrono::duration_cast<std::chrono::microseconds>(end_all_zero_heap - start_all_zero_heap);
    std::cout << "Execution time of Heap Sort (all_zero): " << duration_all_zero_heap.count() << " microseconds" << std::endl;
    writeItemsToFile("/workspaces/code/data/new/heap_descending_rarity_all_zero.csv", sorted_descending_rarity_all_zero);

    std::cout << "All tasks completed. Check the output files for results." << std::endl;

    return 0;
}