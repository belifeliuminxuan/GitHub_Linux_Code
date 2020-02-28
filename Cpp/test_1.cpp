/**********************************************************
 * Author   : liuminxuan
 * Email    : liuminxuan1024@163.com
 * Time     : 2020-02-21 17:14
 * FileName : test_1.cpp
 * *******************************************************/
#include <iostream>
using namespace std;
#include <string>
#include <ctype.h>
class Str
{

  public:

    Str()
    {
      cout<<"请输入:";
      cin>>test_;
    }
    string Cap2Lower()
    {
      for (size_t i=0;i<test_.length();i++)
      {
       test_[i]=tolower(test_[i]); 
      }
      return test_;
    }
    string Lower2Cap();
  private:
    string test_;

};

int main()
{

  Str S;
 cout<< S.Cap2Lower();

  return 0;
}
