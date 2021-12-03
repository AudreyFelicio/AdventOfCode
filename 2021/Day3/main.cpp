#include <bits/stdc++.h>
using namespace std;

vector<string> bits;

void parseInput() {
  string line;
  while (getline(cin, line)) {
    bits.push_back(line);
  }
}

int parseBinary(string &binary) {
  int n = binary.size();
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (binary[i] == '1') {
      ans += (1 << (n - i - 1));
    }
  }

  return ans;
}

int firstPart() {
  int n = bits[0].size();
  int m = bits.size();
  string gamma = "";
  string epsilon = "";
  for (int i = 0; i < n; i++) {
    int countOne = 0;
    for (int j = 0; j < m; j++) {
      if (bits[j][i] == '1') {
        countOne++;
      } else {
        countOne--;
      }
    }
    if (countOne > 0) {
      gamma += "1";
      epsilon += "0";
    } else {
      gamma += "0";
      epsilon += "1";
    }
  }

  return parseBinary(gamma) * parseBinary(epsilon);
}

void mark(vector<bool> &isValid, char indicator, int index, int &count) {
  for (int i = 0; i < isValid.size(); i++) {
    if (!isValid[i]) {
      continue;
    }
    if (bits[i][index] != indicator) {
      isValid[i] = false;
      count--;
    }
  }
}

int helper(bool isOxygen) {
  int n = bits[0].size();
  int m = bits.size();
  int count = m;
  vector<bool> isValid(m, true);

  for (int i = 0; i < n; i++) {
    int countOne = 0;
    for (int j = 0; j < m; j++) {
      if (!isValid[j]) {
        continue;
      }
      if (bits[j][i] == '1') {
        countOne++;
      } else {
        countOne--;
      }
    }
    if (countOne >= 0) {
      if (isOxygen) {
        mark(isValid, '1', i, count);
      } else {
        mark(isValid, '0', i, count);
      }
    } else {
      if (isOxygen) {
        mark(isValid, '0', i, count);
      } else {
        mark(isValid, '1', i, count);
      }
    }
    
    if (count == 1) {
      break;
    }
  }

  string filteredBit = "";
  for (int i = 0; i < m; i++) {
    if (isValid[i]) {
      filteredBit = bits[i];
      break;
    }
  }

  return parseBinary(filteredBit);
}

int secondPart() {
  return helper(true) * helper(false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
