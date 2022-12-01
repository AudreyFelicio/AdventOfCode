#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  vector<int64_t> elves;
  int64_t accumulate = 0LL;
  while (getline(cin, s)) {
    if (s == "") {
      elves.push_back(accumulate);
      accumulate = 0;
      continue;
    }
    accumulate += stoll(s);
  }
  cout << "Part 1: " << *max_element(elves.begin(), elves.end()) << endl;

  sort(elves.begin(), elves.end(), greater<int64_t>{});
  cout << "Part 2: " << elves[0] + elves[1] + elves[2] << endl;
}

