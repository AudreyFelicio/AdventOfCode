#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> al;
unordered_map<string, int> mapper;
unordered_set<int> small;
unordered_set<int> big;

pair<string, string> tokenize(string &line) {
  vector<string> tokens;
  string token = "";
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == '-') {
      tokens.push_back(token);
      token = "";
      continue;
    }
    token += line[i];
  }
  return { tokens[0], token };
}

void parseInput() {
  int id = 0;
  string line;
  while (getline(cin, line)) {
    auto [from, to] = tokenize(line);
    if (mapper.find(from) == mapper.end()) {
      mapper[from] = id;
      isupper(from[0]) ? big.insert(id) : small.insert(id);
      id++;
      al.push_back({});
    }
    if (mapper.find(to) == mapper.end()) {
      mapper[to] = id;
      isupper(to[0]) ? big.insert(id) : small.insert(id);
      id++;
      al.push_back({});
    }
    al[mapper[from]].push_back(mapper[to]);
    al[mapper[to]].push_back(mapper[from]);
  }
}

void dfs(int curr, vector<bool> &visited, int &total) {
  if (curr == mapper["end"]) {
    total++;
    return;
  }
  if (small.find(curr) != small.end()) {
    visited[curr] = true;
  }
  for (int n : al[curr]) {
    if (!visited[n]) {
      dfs(n, visited, total);
    }
  }
  visited[curr] = false;
  return;
}

int firstPart() {
  int ans = 0;
  int startId = mapper["start"];
  vector<bool> visited(mapper.size(), false);
  dfs(startId, visited, ans);
  return ans;
}

void modDfs(int curr, vector<int> &visited, int &total, int special) {
  if (curr == mapper["end"]) {
    total++;
    return;
  }
  if (small.find(curr) != small.end()) {
    visited[curr]++;
  }
  for (int n : al[curr]) {
    if (n == special && visited[n] < 2) {
      modDfs(n, visited, total, special);
    } else if (visited[n] == 0) {
      modDfs(n, visited, total, special);
    }
  }
  if (small.find(curr) != small.end()) {
    visited[curr]--;
  }
  return;
}

int secondPart() {
  int ans = 0;
  int startId = mapper["start"];
  int endId = mapper["end"];
  vector<int> visited(mapper.size(), 0);
  int withoutDouble = 0;
  int overCount = 0;

  modDfs(startId, visited, withoutDouble, -1);
  for (int i : small) {
    if (i != startId && i != endId) {
      overCount++;
      visited.assign(mapper.size(), 0);
      modDfs(startId, visited, ans, i);
    }
  }
  ans -= (overCount - 1) * withoutDouble;
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();
  
  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
