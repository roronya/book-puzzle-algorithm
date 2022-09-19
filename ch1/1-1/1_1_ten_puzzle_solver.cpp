#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
#include<utility>
using namespace std;

// 逆ポーランド記法の計算式を計算する
double calc_porland(const string& exp) {
  // 計算のための配列
  vector<double> space;

  // 逆ポーランド記法expの各文字cを順に見る
  for (char c : exp) {
    if (c >= '0' && c <= '9') {
      // cが数字を表す文字の場合、
      // '7'のような文字リテラルを7のような数値に変換する
      int add = c - '0';

      // 配列の末尾に挿入する
      space.push_back(add);
    } else {
      // cが演算子の場合、末尾から2つの数を取り出す
      double second = space.back();
      space.pop_back();
      double first = space.back();
      space.pop_back();

      // 演算の実施結果を配列の末尾に挿入する
      if (c == '+') {
        space.push_back(first + second);
      } else if (c == '-') {
        space.push_back(first - second);
      } else if (c == '*') {
        space.push_back(first * second);
      } else {
        space.push_back(first / second);
      }
    }
  }
  // 配列の末尾に残っている値を返す
  return space.back();
}

// 逆ポーランド記法の計算式から、通常の計算式を復元する
string decode_poland(const string& exp) {
  // 通常の計算式の復元のための配列
  vector<string> space;

  // 逆ポーランド記法expの各文字cを順に見る
  for (char c : exp) {
    if (c >= '0' && c <= '9') {
      // 数字を表す文字cを文字列に変換して配列の末尾に挿入する
      space.push_back({c});
    } else {
      // cが演算子の場合、末尾から2つの計算式を取り出す
      string second = space.back();
      space.pop_back();
      string first = space.back();
      space.pop_back();

      // 掛け算、割り算の場合、演算子の優先順位が高いので
      // その前後の計算式（単独の数値を除く）にカッコをつける
      if (c == '*' || c == '/') {
        if (first.size() > 1) {
          first = "(" + first + ")";
        }
        if (second.size() > 1) {
          second = "(" + second + ")";
        }
      }

      // 演算子をもとに復元した計算式を配列の末尾に挿入する
      if (c == '+') {
        space.push_back(first + " + " + second);
      } else if (c == '-') {
        space.push_back(first + " - " + second);
      } else if (c == '*') {
        space.push_back(first + " * " + second);
      } else {
        space.push_back(first + " / " + second);
      }
    }
  }
  return space.back();
}


// テンパズルソルバー
// val: 4つの数を格納した配列、target: 作りたい数
vector<string> solve(vector<int> val, int target) {
  // 答えを表す計算式を格納する配列
  vector<string> res;

  // 逆ポーランド記法の計算式expを試すための関数オブジェクト
  const double EPS = 1e-9; // 十分小さい値
  auto check = [&](const string& exp) -> void {
    // 計算結果と作りたい数との差が十分小さいとき、一致とみなす
    if (abs(calc_porland(exp) - target) < EPS) {
     res.push_back(decode_poland(exp));
    }
  };

  // 4つの数valの並び替えを順に試していく
  sort(val.begin(), val.end()); // valを辞書順最小にする
  do {
    // 4つの数字を連結してできる文字列foursを作る
    string fours = "";
    for (int v : val) fours += to_string(v);

    // 4^3 = 64通りの演算子の組み合わせを試していく
    const string ops = "+-*/"; // 4つの演算子
    for (char op1: ops) {
      for (char op2: ops) {
        for (char op3: ops) {
          // まず、パターン"xxxxooo"を作る
          string exp = fours + op1 + op2 + op3;

          // パターン"xxxxooo"を試す
          check(exp);
          
          // パターン"xxxoxoo"を試す
          swap(exp[3], exp[4]); check(exp);

          // パターン"xxxooxo"を試す
          swap(exp[4], exp[5]); check(exp);

          // パターン"xxoxoxo"を試す
          swap(exp[2], exp[3]); check(exp);

          // パターン"xxoxxoo"を試す
          swap(exp[4], exp[5]); check(exp);
        }
      }
    }
  } while(next_permutation(val.begin(), val.end()));
  return res;
}

int main() {
  // 4つの数と、作りたい数の入力
  vector<int> val(4); //4つの数
  int target; //作りたい
  for (int i=0;i<4;i++) {
    cout << i + 1 << " th number: ";
    cin >> val[i];
  }
  cout << "target number: ";
  cin >> target;

  // テンパズルを解く
  vector<string> res = solve(val, target);

  // 出力
  for (const string& exp: res) {
    cout << exp << " = " << target << endl;
  }
}