//
// Created by Venkata Krishna Mangapuram on 12/17/24.
//

// #include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// function to compare if 2 hashes are identical
bool compare_hash(vector<int> &s1_hash, vector<int> &window_hash) {
    for (int i = 0; i < 26; i++) {
        if (s1_hash[i] != window_hash[i]) {
            return false;
        }
    }
    return true;
}

bool checkInclusion(string s1, string s2)
{
    // Corner Case: If s1 is longer than s2

    if (s1.length() > s2.length())
    {
        return false;
    }


    vector<int> s1_Hash(26, 0);
    vector<int> window_hash(26, 0);

    // Hash S1
    for (int i = 0; i < s1.length(); i++) {
        s1_Hash[s1[i] - 'a']++;   //Hash every character of s1
    }

    int window_length = s1.length();
    int n = s2.length();

    // Hash the first window in s2
    for (int i=0; i<window_length; i++) {
        window_hash[s2[i]-'a']++;
    }

    if (compare_hash(s1_Hash, window_hash) == 1) {    // Corner case: To check if first window is a match for s1
        return true;
    }

    if (s1.length() == s2.length()) {   // Corner case: If both the strings are equal in size, then first window is the only window
        return false;
    }


    // Iterate the window start index, start from 1 because 0 is already hashed on the previous loop
    for (int window_start=1; window_start <= n - window_length; window_start++) {
        //UnHash the element slid out of the window on the left
        window_hash[s2[window_start-1]-'a']--;

        //Hash the new element slid into the window on the right
        window_hash[s2[window_start + window_length - 1]-'a']++;

        // If the 2 hashes are equal, return true, a substring has been found
        if (compare_hash(s1_Hash, window_hash) == 1) {
            return true;
        }
    }

    //If no substring has been found that match, return false
    return false;
}

int main() {
    int out = checkInclusion("ab", "ba");
    cout << "The output is: " << out << endl;
}

