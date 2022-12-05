#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ifstream input("./input.txt"); // only contains the instructions, initial state is hardcoded
  vector<vector<char>> stacks = {
    {'Q', 'M', 'G', 'C', 'L'},
    {'R', 'D', 'L', 'C', 'T', 'F', 'H', 'G'},
    {'V', 'J', 'F', 'N', 'M', 'T', 'W', 'R'},
    {'J', 'F', 'D', 'V', 'Q', 'P'},
    {'N', 'F', 'M', 'S', 'L', 'B', 'T'},
    {'R', 'N', 'V', 'H', 'C', 'D', 'P'},
    {'H', 'C', 'T'},
    {'G', 'S', 'J', 'V', 'Z', 'N', 'H', 'P'},
    {'Z', 'F', 'H', 'G'}
  };
  string ops;
  while (input >> ops) {
    int count, idx1, idx2;
    input >> count >> ops >> idx1 >> ops >> idx2;
    while (count > 0) {
      stacks[idx2 - 1].push_back(stacks[idx1 - 1].back());
      stacks[idx1 - 1].pop_back();
      count--;
    }
  }
  string ans = "";
  for (auto& v : stacks) {
    ans.push_back(v.back());
  }
  cout << "Part 1: " << ans << endl;
  stacks = {
    {'Q', 'M', 'G', 'C', 'L'},
    {'R', 'D', 'L', 'C', 'T', 'F', 'H', 'G'},
    {'V', 'J', 'F', 'N', 'M', 'T', 'W', 'R'},
    {'J', 'F', 'D', 'V', 'Q', 'P'},
    {'N', 'F', 'M', 'S', 'L', 'B', 'T'},
    {'R', 'N', 'V', 'H', 'C', 'D', 'P'},
    {'H', 'C', 'T'},
    {'G', 'S', 'J', 'V', 'Z', 'N', 'H', 'P'},
    {'Z', 'F', 'H', 'G'}
  };
  input = ifstream("./input.txt");
  while (input >> ops) {
    int count, idx1, idx2;
    input >> count >> ops >> idx1 >> ops >> idx2;
    vector<char> temp;
    while (count > 0) {
      temp.push_back(stacks[idx1 - 1].back());
      stacks[idx1 - 1].pop_back();
      count--;
    }
    while (!temp.empty()) {
      stacks[idx2 - 1].push_back(temp.back());
      temp.pop_back();
    }
  }
  ans = "";
  for (auto& v : stacks) {
    ans.push_back(v.back());
  }
  cout << "Part 2: " << ans << endl;
}
