// Now I get hashingggg

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> seen;
        int len = 0, left = 0;
        for(int right = 0; right < s.length(); right++){
            while(seen.count(s[right])){
                seen.erase(s[left]);
                left++;
            }
            seen.insert(s[right]);
            len = max(len, right - left + 1);
        }
        return len;
    }
};
