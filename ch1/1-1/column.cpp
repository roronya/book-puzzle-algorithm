#include<iostream>
using namespace std;

/**
家庭用コンピューターが1秒で計算できるのは10億回
$ time ./a.out
./a.out  0.69s user 0.01s system 99% cpu 0.697 total
**/
int main() {
  for (int i=0;i<1000000000;++i){}
}
