#include "methods.h"

std::vector<Item> countingSort(std::vector<Item>& items, const std::string& attribute, bool ascending)
{
    if (attribute != "age"){
        return items;
    }

    // Get the maximum value by attribute
    int max_val = getMax(items, attribute);
    
    // Initialize count_array array based on the max value
    std::vector<int> count_array(max_val + 1, 0);
    std::vector<Item> sorted(items.size());

    // count the occurrences
    for (const auto& item : items) 
    {
        count_array[item.age]++;
    }

    // Calculate cumulative count_array to determine positions
    for (size_t i = 1; i < count_array.size(); i++) 
    {
        count_array[i] += count_array[i - 1];
    }

    // Place items into the sorted array based on cumulative count_array
    for (int i = items.size() - 1; i >= 0; --i)
    {
        sorted[count_array[items[i].age]-1] = items[i];
        count_array[items[i].age]--;
    }


    // Manually reverse the sorted vector if descending order is required
    // Could also change the way they are being cumulated based on the ascending value but this works too
    if (!ascending) 
    {
        for (size_t i = 0, j = sorted.size() - 1; i < j; i++, j--) 
        {
            std::swap(sorted[i], sorted[j]);
        }
    }

    return sorted;
}

void heapify(std::vector<Item>& items, int n, int i, bool descending) {

    if (descending){
        int smallest = i;  // Assume root is smallest initially
        int left = 2 * i + 1;  // Left child index
        int right = 2 * i + 2; // Right child index

        // If left child is larger than root
        if (left < n && items[left].rarityScore < items[smallest].rarityScore) {
            smallest = left;
        }

        // If right child is larger than the smallest so far
        if (right < n && items[right].rarityScore < items[smallest].rarityScore) {
            smallest = right;
        }

        // If smallest is not root, swap and continue heapifying
        if (smallest != i) {
            std::swap(items[i].rarityScore, items[smallest].rarityScore);  // Swap the elements

            // Recursively go to subtree
            heapify(items, n, smallest, descending);
        }

    } else {
        int largest = i;  // Assume root is largest initially
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        // If left child is larger than root
        if (left < n && items[left].rarityScore > items[largest].rarityScore) {
            largest = left;
        }

        // If right child is larger than the largest so far
        if (right < n && items[right].rarityScore > items[largest].rarityScore) {
            largest = right;
        }

        // If largest is not root, swap and continue heapifying
        if (largest != i) {
            std::swap(items[i].rarityScore, items[largest].rarityScore);  // Swap the elements

            // Recursively go to subtree
            heapify(items, n, largest, descending);
        }
    }
}


// Function to perform heap sort on rarityScore scores of items
std::vector<Item> heapSortByRarity(std::vector<Item>& items, bool descending) 
{
    int n = items.size();

    // Build a max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(items, n, i, descending);  // recursıve heapify on each non-leaf node
    }
        // Sıralama işlemi
    for (int i = n - 1; i > 0; i--) {
        std::swap(items[0], items[i]);
        heapify(items, i, 0, descending);
    }

    return items;
}