class Solution {
public:
    bool isPalindrome(string s) {
        string conv;
        for (char c : s)
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                    conv += tolower(c);
                else
                    conv += c;
        int start = 0, end = conv.size() - 1;
        while (start < end) {
            if (conv[start] != conv[end])
                return false;
            start++;
            end--;
        }
        return true;
    }
};
