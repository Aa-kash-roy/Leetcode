#include<bits/stdc++.h>
using namespace std;

/*
    125. Number of Palindromic Substrings
    725. Least Recently Used Cache
*/
// ++++++++++++++++++++++++++++++++++++++++++++

/*
- Number of Palindromic Substrings
Given a lowercase alphabet string s, return the number of palindromic substrings in s.

Constraints
1 ≤ n ≤ 1,000 where n is the length of s

Example 1
Input
s = "tacocat"
Output
10
Explanation
The palindromic substrings are:
{ "t", "a", "c", "o", "c", "a", "t", "coc", "acoca", "tacocat" }
*/

int solve(string s) {
    
    int n = s.length();
    bool dp[n][n];
    memset(dp, false, sizeof(dp));

    /*
        This technique is gap strategy.
        for gap (0, n-1):
        we put i, j at distance of gap.
          s[i]         s[j]
            t  [acoca]  t
                is_palindrome then this is palindrome.
    */
    for(int g=0;g<n;g++){
        for(int i=0,j=g;i < n; i++, j++){
            if(g == 0)
                dp[i][j] = 1;
            else if(g == 1)
                dp[i][j] = (s[i] == s[j]);
            else{
                if(dp[i+1][j-1] and s[i] == s[j])
                    dp[i][j] = 1;
                else
                    dp[i][j] = 0;
            }
        }
    }

    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++)
            if(dp[i][j]) ans++;
    }

    return ans;
}

/*

Least Recently Used Cache

Implement a least recently used cache with the following methods:
LRUCache(int capacity) constructs a new instance of a LRU cache with the given capacity.
get(int key) retrieves the value associated with the key key. If it does not exist, return -1. As a side effect, this key now becomes the most recently used key.
set(int key, int val) updates the key key with value val. If updating this key-value pair exceeds capacity, then evicts the least recently used key-value pair.
Each method should be done in O(1) time.

Constraints
n ≤ 100,000 where n is the number of calls to get and set.

*/

class LRUCache {
    public:
    int cap, time = 0;
    map<int, int> mp, mpt;
    std:: set<pair<int, int>> st;
    LRUCache(int _cap) {
        cap = _cap;
    }

    int get(int key) {
        if(!mp.count(key))
            return -1;
        return mp[key];
    }

    void set(int key, int val) {
        if(mp.size() == cap and !mp.count(key)){
            auto [a, b] = *st.begin();
            mp.erase(b);
            mpt.erase(b);

            st.erase(st.begin());
        }

        if(st.count({mpt[key], key}))
            st.erase({mpt[key], key});
        time++;
        mpt[key] = time;
        mp[key] = val;
        st.insert({time, key});
    }
};

/*

Fair Pay
You are given a list of integers ratings representing the performance scores of programmers.
The manager would like to give $1 to every programmer except if two programmers are adjacent, 
they'd like to pay the better performing programmer at least $1 higher than the worse performing one.

Return the minimum amount of dollars the manager can pay following above constraints.

Constraints

n ≤ 100,000 where n is the length of ratings.
Example 1
Input
ratings = [1, 2, 5, 1]
Output
7
Explanation
The minimum we can pay for each respective programmer is [1, 2, 3, 1]

*/

int solve(vector<int>& ratings) {
    
    int n = ratings.size();

    vector<int> left(n, 1), right(n, 1);
    for(int i=1;i<n;i++){
        if(ratings[i] > ratings[i-1])
            left[i] = left[i-1] + 1;
    }

    for(int i=n-2;i>=0;i--){
        if(ratings[i] > ratings[i+1])
            right[i] = right[i+1] + 1;
    }

    for(int i=0;i<n;i++){
        left[i] = max(left[i], right[i]);
    }

    int ans = 0;
    for(auto x: left)
        ans += x;

    return ans;
}

// ++++++++++++++++++++++++++++++++++++++++++++

int main(){
    return 0;
}