#include <bits/stdc++.h>

using namespace std;

vector<string> split(const string& s) {
  vector<string> parsed;
  string acc = "";
  for (auto c : s) {
    if (c == ' ') {
      parsed.push_back(acc);
      acc = "";
    } else {
      acc += c;
    }
  }
  parsed.push_back(acc);
  return parsed;
}

auto main() -> int {
  ifstream input("./input.txt");

  string line;
  vector<string> path = {"/"};
  unordered_map<string, int64_t> directories;
  while (getline(input, line)) {
    vector<string> parsed = split(line);
    if (parsed[0] == "$") {
      if (parsed[1] == "cd") {
        if (parsed[2] == "..") {
          path.pop_back();
        } else if (parsed[2] == "/") {
          path = {"/"};
        } else {
          path.push_back(parsed[2] + "/");
        }
      }
    } else {
      if (parsed[0] != "dir") {
        int64_t file_sz = stoll(parsed[0]);
        string curr_path = "";
        for (auto& str : path) {
          curr_path += str;
          directories[curr_path] += file_sz;
        }
      }
    }
  }
  int64_t total = 0;
  vector<int64_t> sizes;
  for (auto& [key, value] : directories) {
    sizes.push_back(value);
    if (value <= 100'000) {
      total += value;
    }
  }
  cout << "Part 1: " << total << endl;
  sort(sizes.begin(), sizes.end());
  int64_t space = 70'000'000;
  int64_t threshold = 30'000'000;
  int64_t left = space - directories["/"];
  int64_t required = threshold - left;
  cout << "Part 2: " << *lower_bound(sizes.begin(), sizes.end(), required) << endl;
}
