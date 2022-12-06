#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ifstream input("./input.txt");

  auto parseString = [](const string& s1) -> pair<int64_t, int64_t> {
    auto pos = s1.find("-");
    return {stoll(s1.substr(0, pos)), stoll(s1.substr(pos + 1))};
  };

  string line;
  int64_t total = 0LL;
  int64_t overlaps = 0LL;
  while (getline(input, line)) {
    auto pos = line.find(",");
    string first = line.substr(0, pos);
    string second = line.substr(pos + 1);
    auto [x1, y1] = parseString(first);
    auto [x2, y2] = parseString(second);
    if ((x1 <= x2 && y1 >= y2) || (x2 <= x1 && y2 >= y1)) {
      total++;
    }
    if ((x1 <= x2 && y1 >= x2) || (x2 <= x1 && y2 >= x1)) {
      overlaps++;
    }
  }
  cout << "Part 1: " << total << endl;
  cout << "Part 2: " << overlaps << endl;
}
