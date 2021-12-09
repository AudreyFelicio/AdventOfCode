#include <bits/stdc++.h>
using namespace std;

struct Display {
  vector<string> trials;
  vector<string> outputs;
};

vector<Display> displays;

void parseInput() {
  string line;
  string delim = " | ";
  while (getline(cin, line)) {
    Display d;
    string firstHalf = line.substr(0, line.find(delim));
    string secondHalf = line.substr(line.find(delim) + delim.size());
    string separator = " ";
    auto start = 0U;
    auto end = firstHalf.find(separator);
    while (end != string::npos) {
      d.trials.push_back(firstHalf.substr(start, end - start));
      start = end + separator.size();
      end = firstHalf.find(separator, start);
    }
    d.trials.push_back(firstHalf.substr(start, end - start));
    start = 0U;
    end = secondHalf.find(separator);
    while (end != string::npos) {
      d.outputs.push_back(secondHalf.substr(start, end - start));
      start = end + separator.size();
      end = secondHalf.find(separator, start);
    }
    d.outputs.push_back(secondHalf.substr(start, end - start));
    displays.push_back(d);
  }
}

int firstPart() {
  int ans = 0;
  for (Display d : displays) {
    for (string s : d.outputs) {
      int len = s.size();
      if (len == 2 || len == 3 || len == 4 || len == 7) {
        ans++;
      }
    }
  }
  return ans;
}

int detect(int segments) {
  /*
    0000
   1    2
   1    2
    3333
   4    5
   4    5
    6666
  */
  unordered_map<int, int> mappings = {
    { 119, 0 }, { 36, 1 }, { 93, 2 }, { 109, 3 }, { 46, 4 },
    { 107, 5 }, {123, 6 }, { 37, 7 }, { 127, 8 }, { 111, 9 } 
  };
  return mappings[segments];
}

int secondPart() {
  int ans = 0;
  for (Display d : displays) {
    int permute[7] = { 0, 1, 2, 3, 4, 5, 6 };
    do {
      int allDigits = 0;
      for (string s : d.trials) {
        int seg = 0;
        for (int i = 0; i < s.size(); i++) {
          seg += (1 << permute[s[i] - 'a']);
        }
        int infer = detect(seg);
        allDigits += (1 << infer);
      }
      if (allDigits == (1 << 10) - 1) {
        break;
      }
    } while (next_permutation(permute, permute + 7));

    string curr = "";
    for (string s : d.outputs) {
      int seg = 0;
      for (int i = 0; i < s.size(); i++) {
        seg += (1 << permute[s[i] - 'a']);
      }
      int infer = detect(seg);
      curr += infer + '0';
    }
    ans += stoi(curr);
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
