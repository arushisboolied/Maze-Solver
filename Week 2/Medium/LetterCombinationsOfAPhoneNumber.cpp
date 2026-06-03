class Solution {
public:
    unordered_map<char, vector<char>> m = {
        {'2', {'a', 'b', 'c'}}, {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}}, {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}}, {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}}, {'9', {'w', 'x', 'y', 'z'}}};

    void backtrack(vector<string>& res, string& path, const string& digits,
                   int idx) {
        if (path.length() == digits.length()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < m[digits[idx]].size(); i++) {
            path.push_back(m[digits[idx]][i]);
            backtrack(res, path, digits, idx + 1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string path = "";

        backtrack(res, path, digits, 0);

        return res;
    }
};
