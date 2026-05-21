class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) return false;
        vector<int> vs(26,0), vt(26,0);
        for(char c : s) vs[(int)(c - 'a')]++;
        for(char c : t) vt[(int)(c - 'a')]++;
        return (vs == vt); 
    }
};
