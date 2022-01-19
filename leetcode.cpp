#include<bits/stdc++.h>
using namespace std;

/*
     88. Sort by Frequency and Value
    115. Longest Palindromic Substring 
    125. Number of Palindromic Substrings
    162. Long Distance (Binary index Tree inversion count)
    199. Level Order Alternating
    239. Fair pay
    460. LFU Cache (leetcode)
    725. Least Recently Used Cache
    741. Search Engine* (Trie implementation)
    1094. Car Pooling (leetcode)
    2121. Intervals Between Identical Elements (leetcode)
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

/*
    Important**
    We can't have index greator than 10^6, so we can use compression to solve our purpose.
    vector<int> arr containing the elements range between 1 < arr[i] < 10^9

    1. put elements into set.
    2. create a map and map the elements of set for unique elements 

    int var = 1;
    for(auto x: st) mp[x] = var++;

*/

/*

Long Distance
Given a list of integers nums, return a new list where each element in the new list is the number
of smaller elements to the right of that element in the original input list.

Constraints
n ≤ 100,000 where n is the length of nums
Example 1
Input
lst = [3, 4, 9, 6, 1]
Output
[1, 1, 2, 1, 0]
Explanation
There is 1 smaller element to the right of 3
There is 1 smaller element to the right of 4
There are 2 smaller elements to the right of 9
There is 1 smaller element to the right of 6
There are no smaller elements to the right of 1

*/

int getAns(vector<int> &tree, int num){

    int i = num;
    int ans = 0;
    for(;i>0;i -= (i&(-i)))
        ans += tree[i];
    return ans;
}

void update(vector<int> &tree, int num, int val){

    int i = num;
    for(;i < val; i += (i&(-i)))
        tree[i]++;
    return;
}

vector<int> solve(vector<int>& lst) {
    
    int n = lst.size();
    set<int> st;
    map<int, int> mp;
    for(auto x: lst) st.insert(x);
    int var = 1;
    for(auto x: st)
        mp[x] = var++;

    vector<int> tree(var, 0);
    vector<int> ans(n, 0);

    for(int i=n-1; i>=0; i--){
        ans[i] = getAns(tree, mp[lst[i]] - 1);
        update(tree, mp[lst[i]], var);
    }

    return ans;
}

/*

Sort by Frequency and Value

Given a list of integers nums, order nums by frequency, with most frequent values coming first. 
If there's a tie in frequency, higher valued numbers should come first.

Constraints
0 ≤ n ≤ 100,000 where n is the length of nums

Example 1
Input
nums = [1, 1, 5, 5, 5, 2, 2, 2, 1, 1]
Output
[1, 1, 1, 1, 5, 5, 5, 2, 2, 2]
Explanation
Since 1 occurs most frequently (4 times) they come first. 5 and 2 are then tied 
in terms of frequency (both 3 times) but 5 has higher value so it comes second.

*/

vector<int> solve(vector<int>& nums) {
    
    unordered_map<int, int> mp;
    for(auto x: nums) mp[x]++;

    auto comp = [&](int a, int b){

        if(mp[a] == mp[b])
            return a > b;
        return mp[a] > mp[b];
    };

    sort(nums.begin(), nums.end(), comp);
    return nums;
}

/*
Longest Palindromic Substring

Given a string s, return the length of the longest palindromic substring.
Constraints
n ≤ 1,000 where n is the length of s

Example 1
Input
s = "mactacocatbook"
Output
7

*/

int solve(string s) {
    
    int n = s.length();

    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    for(int g=0;g<n;g++){
        for(int i=0, j=g;i<n;i++, j++){
            if(g == 0)
                dp[i][j] = 1;
            else if(g == 1)
                dp[i][j] = s[i]==s[j] ? 2 : 0;
            else{

                if(s[i] == s[j] and dp[i+1][j-1])
                    dp[i][j] = 2 + dp[i+1][j-1];
            }
        }
    }

    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++)
            ans = max(ans, dp[i][j]);
    }

    return ans;
}

/*

Level Order Alternating

Given a binary tree root, return values of the nodes in each level, alternating from going 
left-to-right and right-to-left.

Constraints

n ≤ 100,000 where n is the number of nodes in root
*/

/**
 * class Tree {
 *     public:
 *         int val;
 *         Tree *left;
 *         Tree *right;
 * };
 */
vector<int> solve(Tree* root) {
    
    vector<int> ans;
    queue<Tree*> q;
    bool ok = 0;

    q.push(root);
    while(q.size()){
        int sz = q.size();
        vector<int> t;
        for(int i=0;i<sz;i++){
            Tree *node = q.front();
            q.pop();
            t.push_back(node->val);
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        if(ok)
            reverse(t.begin(), t.end());
        for(auto x: t)
            ans.push_back(x);
        ok = !ok;
    }

    return ans;
}

/*
1094. Car Pooling

There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).
You are given the integer capacity and an array trips where trip[i] = [numPassengersi, fromi, toi] 
indicates that the ith trip has numPassengersi passengers and the locations to pick them up and drop them off are fromi and toi respectively. 
The locations are given as the number of kilometers due east from the car's initial location.

Return true if it is possible to pick up and drop off all passengers for all the given trips, 
or false otherwise.

Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false

*/

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int, int> map;
        for (int i = 0;i < trips.size();++i) {
            map[trips[i][1]] += trips[i][0]; //filled seats increase when we pick up passengers
            map[trips[i][2]] -= trips[i][0]; //filled seats decrease when we drop off the passengers
        }
        for (auto it = map.begin(); it != map.end();it++) { //map is sorted on keys( key is time instant)
            capacity -= it->second;
            if (capacity < 0) { //if at any time instant, vacant seats < no of passengers to pick up, return false
                return false;
            }
        }
        return true;
    }
};

/*

460. LFU Cache

Design and implement a data structure for a Least Frequently Used (LFU) cache.
Implement the LFUCache class:
LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, 
it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie 
(i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. 
The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). 
The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[3,4], cnt(4)=2, cnt(3)=3

*/

class LFUCache {
public:
    
    int cap, time = 0;
    map<int, int> mp, mpt, mpf;
    set<vector<int>> st;
    LFUCache(int _cap) {
        cap = _cap;
    }
    
    int get(int key) {
        
        if(mp.count(key)){
            auto vec = st.find({mpf[key], mpt[key], key});
            mpf[key]++;
            mpt[key] = time;
            time++;
            st.insert({mpf[key], mpt[key], key});
            st.erase(vec);
            return mp[key];
        }
        return -1;
    }
    
    void put(int key, int value) {
        
        if(cap == 0)
            return;
        vector<int> v(3, 0);
        int flag = 1;
        if(mp.count(key)){
            v[0] = mpf[key];
            v[1] = mpt[key];
            v[2] = key;
            flag = 0;
        }
        
        if(mp.size() == cap and flag){
            
            vector<int> temp = *st.begin();
            mp.erase(temp[2]);
            mpf.erase(temp[2]);
            mpt.erase(temp[2]);
            
            st.erase(st.begin());
        }
        
        if(!flag){
            auto temp = st.find(v);
            st.erase(temp);
        }
        
        mp[key] = value;
        mpt[key] = time;
        mpf[key] = (flag == 0 ? v[0]+1 : 1);
        
        st.insert({mpf[key], mpt[key], key});
        time++;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/*

2121. Intervals Between Identical Elements

You are given a 0-indexed array of n integers arr.
The interval between two elements in arr is defined as the absolute difference between their indices. 
More formally, the interval between arr[i] and arr[j] is |i - j|.

Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] 
and each element in arr with the same value as arr[i].
Note: |x| is the absolute value of x.

Example 1:

Input: arr = [2,1,3,1,2,3,3]
Output: [4,2,7,2,4,4,5]
Explanation:
- Index 0: Another 2 is found at index 4. |0 - 4| = 4
- Index 1: Another 1 is found at index 3. |1 - 3| = 2
- Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
- Index 3: Another 1 is found at index 1. |3 - 1| = 2
- Index 4: Another 2 is found at index 0. |4 - 0| = 4
- Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
- Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5

*/

class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        
        int n = arr.size();
        map<int, vector<int>> mp;
        for(int i=0;i<n;i++){
            mp[arr[i]].push_back(i);
        }
        
        vector<long long> ans(n, 0);
        for(auto x: mp){
            auto vp = x.second;
            int sz = vp.size();
            vector<long long> suf(sz, 0), pre(sz, 0);
            for(int i=1;i<sz;i++){
                pre[i] = (vp[i] - vp[i-1])*i + pre[i-1]; 
            }
            for(int i=sz-2;i>=0;i--)
                suf[i] = (vp[i+1] - vp[i])*(sz-i-1) + suf[i+1]; 
            
            for(int i=0;i<sz;i++){
                ans[vp[i]] = pre[i] + suf[i];
            }
        }
        
        return ans;
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++

int main(){
    return 0;
}