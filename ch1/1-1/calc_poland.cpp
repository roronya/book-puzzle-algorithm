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
