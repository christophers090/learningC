class Solution {
public:
  vector<int> coutBits(int n) {
    vector<int> result(n + 1);
    for (int i = 1; i <= n; i++) {
      result[i] = result[i >> 1] + (i & 1);
    }
  }
}