#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "tweet.h" 
using namespace std;

void measureSortExecutionTime(const string& filename, double& bubbleTime, double& insertionTime, double& mergeTime) {
    vector<Tweet> tweets = readTweetsFromFile(filename);
    
    // Measure Bubble Sort
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(tweets, "retweetCount", true); // Ascending
    auto end = chrono::high_resolution_clock::now();
    bubbleTime = chrono::duration<double, milli>(end - start).count();

    tweets = readTweetsFromFile(filename);
    
    // Measure Insertion Sort
    start = chrono::high_resolution_clock::now();
    insertionSort(tweets, "retweetCount", true); // Ascending
    end = chrono::high_resolution_clock::now();
    insertionTime = chrono::duration<double, milli>(end - start).count();

    tweets = readTweetsFromFile(filename);
    
    // Measure Merge Sort
    start = chrono::high_resolution_clock::now();
    mergeSort(tweets, 0, tweets.size() - 1, "retweetCount", true); // Ascending
    end = chrono::high_resolution_clock::now();
    mergeTime = chrono::duration<double, milli>(end - start).count();
}

int main() {

    double bubbleTime, insertionTime, mergeTime;

    // 1. Measure sorting execution times for different datasets in permutations
    cout << "Sorting Permutations Dataset:\n";
    measureSortExecutionTime("/workspaces/Code/data/permutations/tweets.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/permutations/tweetsSA.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweetsSA.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/permutations/tweetsSD.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweetsSD.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/permutations/tweetsNS.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweetsNS.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    // 2. Measure sorting execution times for different datasets in sizes
    cout << "\nSorting Sizes Dataset:\n";
    measureSortExecutionTime("/workspaces/Code/data/sizes/tweets5K.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets5K.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/sizes/tweets10K.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets10K.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/sizes/tweets20K.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets20K.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/sizes/tweets30K.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets30K.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    measureSortExecutionTime("/workspaces/Code/data/sizes/tweets50K.csv", bubbleTime, insertionTime, mergeTime);
    cout << "tweets50K.csv:\nBubble Sort Time (ms): " << bubbleTime << "\n";
    cout << "Insertion Sort Time (ms): " << insertionTime << "\n";
    cout << "Merge Sort Time (ms): " << mergeTime << "\n";

    // 3. Perform binary searches on sizes datasets
    long long searchKey = 1773335;
    double searchTime;

    cout << "\nPerforming Binary Search:\n";
    
    for (const auto& sizeFile : {"/workspaces/Code/data/sizes/tweets5K.csv", 
                                  "/workspaces/Code/data/sizes/tweets10K.csv", 
                                  "/workspaces/Code/data/sizes/tweets20K.csv", 
                                  "/workspaces/Code/data/sizes/tweets30K.csv", 
                                  "/workspaces/Code/data/sizes/tweets50K.csv"}) {
        auto start = chrono::high_resolution_clock::now();
        bool found = binarySearch(readTweetsFromFile(sizeFile), searchKey, "tweetID"); // Binary search for tweetID
        auto end = chrono::high_resolution_clock::now();
        searchTime = chrono::duration<double, milli>(end - start).count();

        cout << sizeFile << ":\nBinary Search Time (ms): " << searchTime << "\n";
        
    }


    // 4. Perform treshold function on sizes datasets

    cout << "\nPerforming Treshold:\n";
    
    for (const auto& sizeFile : {"/workspaces/Code/data/sizes/tweets5K.csv", 
                                  "/workspaces/Code/data/sizes/tweets10K.csv", 
                                  "/workspaces/Code/data/sizes/tweets20K.csv", 
                                  "/workspaces/Code/data/sizes/tweets30K.csv", 
                                  "/workspaces/Code/data/sizes/tweets50K.csv"}) {
        auto start = chrono::high_resolution_clock::now();
        int found = countAboveThreshold(readTweetsFromFile(sizeFile), "favoriteCount", 250);
        auto end = chrono::high_resolution_clock::now();
        searchTime = chrono::duration<double, milli>(end - start).count();

        cout << sizeFile << ":\nTreshold Counting time (ms): " << searchTime << "\n";
        
    }

    // vector<Tweet> tweets = readTweetsFromFile("/workspaces/Code/data/sizes/tweets5K.csv");
    // mergeSort(tweets, 0, tweets.size() - 1, "retweetCount", true); // Ascending
    // writeTweetsToFile("sonuc.csv", tweets);
    // return 0;
}