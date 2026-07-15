class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                  int color) {

        int o = image[sr][sc];
        if (color == o)
            return image;
        image[sr][sc] = color;
        solve(image, sr, sc, color, o);

        return image;
    }
    void solve(vector<vector<int>>& image, int sr, int sc, int color, int o) {

        // above
        if (sr > 0 && image[sr - 1][sc] == o) {
            image[sr - 1][sc] = color;
            solve(image, sr - 1, sc, color, o);
        }
        // right
        if (sc < image[0].size() - 1 && image[sr][sc + 1] == o) {
            image[sr][sc + 1] = color;
            solve(image, sr, sc + 1, color, o);
        }
        // left
        if (sc > 0 && image[sr][sc - 1] == o) {
            image[sr][sc - 1] = color;
            solve(image, sr, sc - 1, color, o);
        }
        // below
        if (sr < image.size() - 1 && image[sr + 1][sc] == o) {
            image[sr + 1][sc] = color;
            solve(image, sr + 1, sc, color, o);
        }

        return;
    }
};
