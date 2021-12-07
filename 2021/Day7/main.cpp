#include <bits/stdc++.h>
using namespace std;

int pos[20000];
int maxPos = 0;
int minPos = 20001;

void parseInput() {
  string line;
  getline(cin, line);
  string token = "";
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == ',') {
      int curr = stoi(token);
      maxPos = max(maxPos, curr);
      minPos = min(minPos, curr);
      pos[curr]++;
      token = "";
      continue;
    }
    token += line[i];
  }
  int curr = stoi(token);
  maxPos = max(maxPos, curr);
  minPos = min(minPos, curr);
  pos[curr]++;
}

int firstPart() {
  int ans = 1e9 + 1;
  for (int i = minPos; i <= maxPos; i++) {
    int curr = 0;
    for (int j = minPos; j <= maxPos; j++) {
      curr += pos[j] * abs(j - i);
    }
    ans = min(ans, curr);
  }
  return ans;
}

int secondPart() {
  int ans = 1e9 + 1;
  for (int i = minPos; i <= maxPos; i++) {
    int curr = 0;
    for (int j = minPos; j <= maxPos; j++) {
      curr += pos[j] * ((abs(j - i) * (abs(j - i) + 1)) / 2);
    }
    ans = min(ans, curr);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
