#include "tweet.h"
using namespace std;
 
int binarySearch(const vector<Tweet>& tweets, long long key, const string& sortBy) {
    int left = 0;
    int right = tweets.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        long long midValue;
        
        if (sortBy == "favoriteCount") {
            midValue = tweets[mid].favoriteCount;
        } else if (sortBy == "retweetCount") {
            midValue = tweets[mid].retweetCount;
        } else if (sortBy == "tweetID") {
            midValue = tweets[mid].tweetID;
        } else {
            return -1; 
        }

        
        if (midValue == key) {
            return mid; 
        } else if (midValue < key) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return -1;
}

int countAboveThreshold(const vector<Tweet>& tweets, const string& metric, int threshold) {
    int count = 0;

    for (const auto& tweet : tweets) {
        // Check the specified metric
        if (metric == "favoriteCount") {
            if (tweet.favoriteCount > threshold) {
                count++;
            }
        } else if (metric == "retweetCount") {
            if (tweet.retweetCount > threshold) {
                count++;
            }
        } else {
            cerr << "Invalid metric specified." << endl;
            return -1;
        }
    }

    return count;
}
