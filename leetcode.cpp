#include<bits/stdc++.h>
using namespace std;

/*
    125. Number of Palindromic Substrings
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


// ++++++++++++++++++++++++++++++++++++++++++++

int main(){
    return 0;
}