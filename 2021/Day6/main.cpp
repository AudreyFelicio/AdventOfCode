#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> original(9, 0);
vector<ll> countTimer(9, 0);

void parseInput() {
  string line;
  getline(cin, line);
  for (int i = 0; i < line.size(); i += 2) {
    countTimer[line[i] - '0']++;
    original[line[i] - '0']++;
  }
}

ll helper(int limit) {
  for (int t = 0; t < limit; t++) {
    vector<ll> newCountTimer(9, 0);
    for (int i = 8; i >= 1; i--) {
      newCountTimer[i - 1] = countTimer[i];
    }
    newCountTimer[6] += countTimer[0];
    newCountTimer[8] += countTimer[0];
    countTimer = newCountTimer;
  }

  ll count = 0;
  for (int i = 0; i <= 8; i++) {
    count += countTimer[i];
  }
  return count;
}

ll firstPart() {
  return helper(80);
}

ll secondPart() {
  return helper(256);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  cout << firstPart() << endl;
  countTimer = original;
  cout << secondPart() << endl;
}
