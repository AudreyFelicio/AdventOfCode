#include <bits/stdc++.h>

using namespace std;

auto add(vector<pair<int64_t, int64_t>>& prefix, int64_t& total, int64_t cycle) {
  auto it = lower_bound(prefix.begin(), prefix.end(), make_pair(cycle, 0LL));
  if (it->first >= cycle) {
    --it;
  }
  total += it->second * cycle;
}

auto main() -> int {
  ifstream input("./input.txt");

  string inst;
  vector<pair<int64_t, int64_t>> prefix = {{0, 1}};
  while (input >> inst) {
    auto [x, y] = prefix.back();
    if (inst == "noop") {
      prefix.push_back({x + 1, y});
    } else {
      int64_t value; input >> value;
      prefix.push_back({x + 2, y + value});
    }
  }
  int64_t total = 0LL;
  add(prefix, total, 20LL);
  add(prefix, total, 60LL);
  add(prefix, total, 100LL);
  add(prefix, total, 140LL);
  add(prefix, total, 180LL);
  add(prefix, total, 220LL);
  cout << "Part 1: " << total << endl;

  input = ifstream("./input.txt");
  vector<vector<char>> screen(6, vector<char>(40, '.'));
  int sprite = 1;
  int curr_cycle = 0;
  while (input >> inst) {
    int row_index = curr_cycle / 40;
    cout << row_index << " " << curr_cycle << " " << sprite << endl;
    if (inst == "noop") {
      curr_cycle++;
      if (abs(((curr_cycle - 1) % 40) - sprite) <= 1) {
        screen[row_index][(curr_cycle - 1) % 40] = '#';
      } else {
        screen[row_index][(curr_cycle - 1) % 40] = '.';
      }
    } else {
      int val; input >> val;
      curr_cycle++;
      if (abs(((curr_cycle - 1) % 40) - sprite) <= 1) {
        screen[row_index][(curr_cycle - 1) % 40] = '#';
      } else {
        screen[row_index][(curr_cycle - 1) % 40] = '.';
      }
      row_index = curr_cycle / 40;
      curr_cycle++;
      if (abs(((curr_cycle - 1) % 40) - sprite) <= 1) {
        screen[row_index][(curr_cycle - 1) % 40] = '#';
      } else {
        screen[row_index][(curr_cycle - 1) % 40] = '.';
      }
      sprite += val;
    }
  }
  for (auto& v : screen) {
    for (auto c : v) {
      cout << c;
    }
    cout << endl;
  }
}
