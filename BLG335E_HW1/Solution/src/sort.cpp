#include "tweet.h"
using namespace std;

void bubbleSort(vector<Tweet>& tweets, const string& sortBy, bool ascending) 
{
    int n = tweets.size();

    for (int i = 0; i < n - 1; ++i) {
        
        for (int j = 0; j < n - i - 1; ++j) {

            if (sortBy == "retweetCount") {
                if (ascending == (tweets[j].retweetCount > tweets[j + 1].retweetCount)) { 
                    swap(tweets[j], tweets[j + 1]); // perform swap if the order doesnt match the ascending/descending choice
                }
            } 
            else if (sortBy == "favoriteCount") {
                if (ascending == (tweets[j].favoriteCount > tweets[j + 1].favoriteCount)) {
                    swap(tweets[j], tweets[j + 1]); 
                }
            } 
            else if (sortBy == "tweetID") {
                if (ascending == (tweets[j].tweetID > tweets[j + 1].tweetID)) {
                    swap(tweets[j], tweets[j + 1]);
                }
            } else {
                return;
            }
        }
    }
}

void insertionSort(vector<Tweet>& tweets, const string& sortBy, bool ascending) {
    int n = tweets.size();
    
    for (int sorted_portion = 1; sorted_portion < n; sorted_portion++) {
        Tweet element = tweets[sorted_portion]; // Element to be placed
        int i = sorted_portion - 1;

        // Place the element inside the sorted portion
        while (i >= 0) {
            if (sortBy == "retweetCount") {
                if (ascending == tweets[i].retweetCount > element.retweetCount){
                    tweets[i + 1] = tweets[i];
                    i--;
                } else {
                    break;
                }
            } 
            else if (sortBy == "favoriteCount") {
                if (ascending == tweets[i].favoriteCount > element.favoriteCount){
                    tweets[i + 1] = tweets[i];
                    i--;
                } else {
                    break;
                }
            } 
            else if (sortBy == "tweetID") {
                if (ascending == tweets[i].tweetID > element.tweetID){
                    tweets[i + 1] = tweets[i];
                    i--;
                } else {
                    break; // Correct position found
                }
            } else {
                return;
            }
        }
        tweets[i + 1] = element; // place the element to the position
    }
}

void mergeSort(vector<Tweet>& tweets, int left, int right, const string& sortBy, bool ascending) {
    if (left < right) {

        int mid = left + (right - left) / 2;
        // recursively keep dividing if element size is >= 2
        mergeSort(tweets, left, mid, sortBy, ascending); 
        mergeSort(tweets, mid + 1, right, sortBy, ascending);

        // merge after each sub array is also sorted by dividing and merging
        merge(tweets, left, mid, right, sortBy, ascending);
    }
}

void merge(vector<Tweet>& tweets, int left, int mid, int right, const string& sortBy, bool ascending) {
    vector<Tweet> subarray;
    int left_init = left;
    int right_init = mid + 1;
    int length = right - left + 1;
    
    while (left_init <= mid && right_init <= right) {
        if (sortBy == "retweetCount") {
            if ((ascending && tweets[left_init].retweetCount <= tweets[right_init].retweetCount) || 
                (!ascending && tweets[left_init].retweetCount > tweets[right_init].retweetCount)) {
                subarray.push_back(tweets[left_init++]);
            } else {
                subarray.push_back(tweets[right_init++]);
            }
        } 
        else if (sortBy == "favoriteCount") {
            if ((ascending && tweets[left_init].favoriteCount <= tweets[right_init].favoriteCount) || 
                (!ascending && tweets[left_init].favoriteCount > tweets[right_init].favoriteCount)) {
                subarray.push_back(tweets[left_init++]);
            } else {
                subarray.push_back(tweets[right_init++]);
            }
        } 
        else if (sortBy == "tweetID") {
            if ((ascending && tweets[left_init].tweetID <= tweets[right_init].tweetID) || 
                (!ascending && tweets[left_init].tweetID > tweets[right_init].tweetID)) {
                subarray.push_back(tweets[left_init++]);
            } else {
                subarray.push_back(tweets[right_init++]);
            }
        }
    }
    
    // If there are remaining elements on the left side
    while (left_init <= mid) {
        subarray.push_back(tweets[left_init++]);
    }
    
    // If there are remaining elements on the right side
    while (right_init <= right) {
        subarray.push_back(tweets[right_init++]);
    }

    // Write the sorted subarray back to the main tweets vector
    for (int i = 0; i < length; i++) {
        tweets[left + i] = subarray[i];
    }
}