#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> syntaxes;
vector<string> incomplete;
unordered_set<char> opening { '(', '{', '[', '<' };
unordered_set<char> closing { ')', '}', ']', '>' };
unordered_map<char, int> point {
  {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}
};
unordered_map<char, char> openPair {
  {')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}
};
unordered_map<char, char> closePair {
  {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}
};
unordered_map<char, int> completePoint {
  {'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}
};

void parseInput() {
  string line;
  while (getline(cin, line)) {
    syntaxes.push_back(line);
  }
}

int firstPart() {
  int ans = 0;
  for (string s : syntaxes) {
    stack<char> eval;
    bool isIncomplete = true;
    for (int i = 0; i < s.size(); i++) {
      if (opening.find(s[i]) == opening.end()) {
        char top = eval.top(); eval.pop();
        if (openPair[s[i]] != top) {
          ans += point[s[i]];
          isIncomplete = false;
          break;
        }
      } else {
        eval.push(s[i]);
      }
    }
    if (isIncomplete) {
      incomplete.push_back(s);
    }
  }
  return ans;
}

ll secondPart() {
  vector<ll> scores;
  for (string s : incomplete) {
    stack<char> eval;
    ll currScore = 0;
    for (int i = 0; i < s.size(); i++) {
      if (opening.find(s[i]) == opening.end()) {
        eval.pop();
      } else {
        eval.push(s[i]);
      }
    }
    while (!eval.empty()) {
      currScore = currScore * 5 + completePoint[eval.top()];
      eval.pop();
    }
    scores.push_back(currScore);
  }
  sort(scores.begin(), scores.end());
  return scores[scores.size() / 2];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
