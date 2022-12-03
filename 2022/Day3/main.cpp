#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ifstream inputs("./input.txt");

  auto computeValue = [](char c) -> int64_t {
    if (c >= 'a' && c <= 'z') {
      return c - 'a' + 1;
    } else {
      return c - 'A' + 27;
    }
  };

  string bag;
  int64_t total = 0LL;
  while (inputs >> bag) {
    int64_t n = bag.size() / 2;
    unordered_set<char> appeared;
    unordered_set<char> doubled;
    for (int i = 0; i < bag.size(); ++i) {
      if (i < n) {
        appeared.insert(bag[i]);
      } else {
        if (appeared.find(bag[i]) != appeared.end()) {
          doubled.insert(bag[i]);
        }
      }
    }
    for (auto c : doubled) {
      total += computeValue(c);
    }
  }
  cout << "Part 1 " << total << endl;

  inputs = ifstream("./input.txt");
  total = 0LL;
  string elf1, elf2, elf3;
  while (inputs >> elf1 >> elf2 >> elf3) {
    unordered_map<char, int64_t> common;
    auto process = [&](string& elf) {
      unordered_set<char> unique;
      for (auto c : elf) {
        unique.insert(c);
      }
      for (auto c : unique) {
        common[c]++;
      }
    };
    process(elf1);
    process(elf2);
    process(elf3);
    for (auto [k, v] : common) {
      if (v == 3) total += computeValue(k);
    }
  }
  cout << "Part 2 " << total << endl;
}
