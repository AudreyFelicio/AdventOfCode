#include <bits/stdc++.h>

using namespace std;

class List {
public:
  bool is_decoder;
  optional<int> val;
  vector<List> children;

  List(): val{nullopt}, is_decoder{false} {}

  List(int val): val{val}, is_decoder{false} {}

  bool isList() {
    return !val.has_value();
  }

  void convertList() {
    if (isList()) return;
    assert(val.has_value() && children.empty());
    children.push_back(List(val.value()));
    val = nullopt;
  }
};

enum class State {
  IN_ORDER,
  CONTINUE,
  OUT_OF_ORDER
};

List makeList(const string& s) {
  vector<List> depth;
  string integer = "";
  for (auto c : s) {
    if (c == '[') {
      depth.push_back(List());
    } else if (c == ']') {
      assert(!depth.empty());
      if (!integer.empty()) depth.back().children.push_back(stoi(integer));
      integer = "";
      if (depth.size() == 1) continue;
      List curr = depth.back(); depth.pop_back();
      depth.back().children.push_back(curr);
    } else if (c == ',') {
      if (!integer.empty()) depth.back().children.push_back(List(stoi(integer)));
      integer = "";
    } else {
      integer += c;
    }
  }
  assert(depth.size() == 1);
  return depth.back();
}

State compareLists(List& left, List& right) { 
  if (!left.isList() && !right.isList()) {
    if (left.val < right.val) return State::IN_ORDER;
    if (left.val == right.val) return State::CONTINUE;
    if (left.val > right.val) return State::OUT_OF_ORDER;
  }
  left.convertList();
  right.convertList();
  for (int i = 0; i < left.children.size(); ++i) {
    if (i == right.children.size()) return State::OUT_OF_ORDER;;
    auto res = compareLists(left.children[i], right.children[i]);
    if (res != State::CONTINUE) {
      return res;
    }
  }
  if (left.children.size() < right.children.size()) {
    return State::IN_ORDER;
  }
  return State::CONTINUE;
}

auto main() -> int {
  ifstream input("./input.txt");

  string l, r;
  int ans = 0;
  int index = 1;
  while (getline(input, l)) {
    getline(input, r);
    List left = makeList(l);
    List right = makeList(r);
    if (compareLists(left, right) == State::IN_ORDER) {
      ans += index;
    }
    index++;
    getline(input, l);
  }
  cout << "Part 1: " << ans << endl;

  input = ifstream("./input.txt");
  vector<List> lists = {makeList("[[2]]"), makeList("[[6]]")};
  lists[0].is_decoder = true;
  lists[1].is_decoder = true;
  while (getline(input, l)) {
    getline(input, r);
    lists.push_back(makeList(l));
    lists.push_back(makeList(r));
    getline(input, l);
  }
  auto cmp = [](const List& left, const List& right) -> bool {
    List copy_left = left;
    List copy_right = right;
    auto state = compareLists(copy_left, copy_right);
    return state == State::IN_ORDER;
  };
  sort(lists.begin(), lists.end(), cmp);
  int part2 = 1;
  for (int i = 0; i < lists.size(); ++i) {
    if (lists[i].is_decoder) part2 *= (i + 1);
  }
  cout << "Part 2: " << part2 << endl;
}
