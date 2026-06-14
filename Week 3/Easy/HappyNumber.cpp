class Solution {
public:
    int op(int n){
        int sum = 0;
        while(n > 0){
            sum += (n%10)*(n%10);
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> s;
        while(n != 1){
            s.insert(n);
            n = op(n);
            if(s.count(n))
                return false;
        }
        return true;
    }
};
