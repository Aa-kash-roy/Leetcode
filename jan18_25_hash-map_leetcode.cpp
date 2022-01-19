/*
676. Implement Magic Dictionary

Design a data structure that is initialized with a list of different words. Provided a string, you should determine if you can change exactly one character in this string to match any word in the data structure.

Implement the MagicDictionary class:

MagicDictionary() Initializes the object.
void buildDict(String[] dictionary) Sets the data structure with an array of distinct strings dictionary.
bool search(String searchWord) Returns true if you can change exactly one character in searchWord to match any string in the data structure, otherwise returns false.
 

Example 1:

Input
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
Output
[null, null, false, true, false, false]

Explanation
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // return False
magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
magicDictionary.search("hell"); // return False
magicDictionary.search("leetcoded"); // return False

*/
#include<bits/stdc++.h>
using namespace std;

class MagicDictionary {
public:
    /** Initialize your data structure here. */
    unordered_set<string> st;
    MagicDictionary() {
        
        st.clear();
    }
    
    void buildDict(vector<string> dict) {
        
        for(auto x: dict){
            st.insert(x);
        }
    }
    
    bool search(string str) {
        
        for(int i=0;str[i];i++){
            char ch = str[i];
            for(int j=0;j<26;j++){
                if(ch == j+'a') continue;
                else
                    str[i] = j+'a';
                if(st.count(str)) return true;
            }
            str[i] = ch;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

class MagicDictionary {
public:
    /** Initialize your data structure here. */
    map<int, vector<string>> mp;
    MagicDictionary() {
        
        mp.clear();
    }
    
    void buildDict(vector<string> dict) {
        
        for(auto x: dict){
            mp[x.size()].push_back(x);
        }
    }
    
    bool search(string str) {
        
        vector<string> temp = mp[str.size()];
        for(auto s: temp){
            int cnt = 0;
            for(int i=0;s[i];i++){
                if(str[i] != s[i])
                    cnt++;
            }
            if(cnt == 1) return true;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

/*

621. Task Scheduler

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different 
task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, 
the CPU could complete either one task or just be idle.
However, there is a non-negative integer n that represents the cooldown period between two same tasks 
(the same letter in the array), that is that there must be at least n units of time between any two same
tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.


*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        
        int f[26] = {0};
        for(auto x: tasks)
            f[x-'A']++;
        
        sort(f, f+26);
        int mx = f[25];
        int eslots = (mx-1)*n;

        for(int i=24;i>=0;i--){
            eslots -= min(f[i], mx-1);
        }
        
        return eslots > 0 ? tasks.size() + eslots : tasks.size();
    }
};

/*
767. Reorganize String

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
Return any possible rearrangement of s or return "" if not possible.

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""

*/

class Solution {
public:
    string reorganizeString(string s) {
        
        map<int, int> mp;
        for(auto x: s) mp[x]++;
        string ans = "";
        
        priority_queue<pair<int, int>> pq;
        for(auto x: mp){
            pq.push({x.second, x.first});
        }
        while(pq.size()){
            auto [x, y] = pq.top(); pq.pop();
            ans.push_back(y);
            if(pq.size()){
                auto[x1, y1] = pq.top(); pq.pop();
                ans.push_back(y1);
                if(x1 > 1){
                    pq.push({x1-1, y1});
                }
            }
            if(x > 1)
                pq.push({x-1, y});
        }
        
        for(int i=1;ans[i];i++){
            if(ans[i] == ans[i-1])
                return "";
        }
        return ans;
    }
};


