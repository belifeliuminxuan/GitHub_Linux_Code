/**********************************************************
 * Author   : liuminxuan
 * Email    : liuminxuan1024@163.com
 * Time     : 2020-03-09 21:05
 * FileName : main.cpp
 * *******************************************************/
#include "stl.hpp"

class stu
{
  public:
    stu()
    {

    }
    void test()
    {
      cout<<"1";
    }
};
#if 0
int main()
{
vector<stu> s(5);
for (int i=0;i<5;i++)
  s[i].stu::test();

  return 0;
}
#endif


// 奇偶排序
// 先按照从大到小输出奇数
// 再从小到大输出偶数
//
#include <iterator>
#include <deque>
int main()
{

  istream_iterator<int>i1(cin),i2;
  vector<int>s1(i1,i2);
  sort(s1.begin(),s1.end());
  copy(s1.begin(),s1.end(),ostream_iterator<int>(cout,","));
  cout<<endl;
  deque<int>s2;
  for (vector<int>::iterator iter=s1.begin();iter!=s1.end();++iter)
  {
    if (*iter%2==0)
      s2.push_back(*iter);
    else
      s2.push_front(*iter);
  }
copy(s2.begin(),s2.end(),ostream_iterator<int>(cout,","));
cout<<endl;

  return 0;
}


