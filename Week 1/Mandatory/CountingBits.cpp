/* LOGIC : Number of 1's in the binary form of a number (say x) is the successive number of the number of 1's in 
           the binary form of (x - Largest power of two smaller than x)
*/


class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits(n+1, 0);
        int PowerOfTwo = 0;
        for(int i = 1; i <= n; i++){
            if((i & (i-1)) == 0){
                PowerOfTwo = i;
                bits[i] = 1;
            }
            else{
                bits[i] = 1 + bits[i - PowerOfTwo];
            }
        }
        return bits;
    }
};
