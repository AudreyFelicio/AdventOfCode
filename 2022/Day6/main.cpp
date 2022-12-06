#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ifstream input("./input.txt");
  string line;
  int64_t ans = 0;
  while (getline(input, line)) {
    unordered_set<char> unique;
    for (int i = 3; i < line.size(); ++i) {
      unordered_set<char> unique;
      for (int j = 0; j < 4; ++j) {
        unique.insert(line[i - j]);
      }
      if (unique.size() == 4) {
        ans = i + 1;
        break;
      }
    }
  }
  cout << "Part 1: " << ans << endl;
  input = ifstream("./input.txt");
  while (getline(input, line)) {
    unordered_set<char> unique;
    for (int i = 13; i < line.size(); ++i) {
      unordered_set<char> unique;
      for (int j = 0; j < 14; ++j) {
        unique.insert(line[i - j]);
      }
      if (unique.size() == 14) {
        ans = i + 1;
        break;
      }
    }
  }
  cout << "Part 2: " << ans << endl;
}
