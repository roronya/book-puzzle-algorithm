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
