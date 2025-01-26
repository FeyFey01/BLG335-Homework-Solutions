
#include "tweet.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<Tweet> readTweetsFromFile(const string& filename) {

    vector<Tweet> tweets; // first create an empty file to return at the end

    try {
        ifstream file(filename); // ifstream bc i just wanna read it
        if (!file.is_open()) {
            throw ("Could not open file");
        }
        string line;
        getline(file, line);

        while (getline(file, line)) {
            Tweet tweet;
            // we learned this sscanf function last year but no one uses it
            // i think it suits better to our implementations more 
            // bc we can directly parse the string without converting the types and creating string streams etc
            sscanf(line.c_str(), "%lld,%d,%d", &tweet.tweetID, &tweet.retweetCount, &tweet.favoriteCount);
            tweets.push_back(tweet);
        }

        file.close();
    } catch(const exception& e) { // if theres any error while reading file or parsing string it will be caught here
        cout << "hata" << e.what() << endl;
    } // i searched for smth similar to this line in py: except Exception as e:

    return tweets; // Return the vector of tweets whether empty or not
}

void writeTweetsToFile(const string& filename, const vector<Tweet>& tweets) {
    try{
        ofstream file(filename); // ofstream bc i wanna create it or clean it if it exists.
        if (!file.is_open()) {
            throw ("Could not open file");
        }
        file << "tweetID,retweet_count,favorite_count\n"; // header

        for (const auto& tweet : tweets) {
            file << tweet.tweetID << "," << tweet.retweetCount << "," << tweet.favoriteCount << "\n";
        }

        file.close(); // Close the file
    } catch(const exception& e) { 
        cout << "hata" << e.what() << endl;
    }
    
}