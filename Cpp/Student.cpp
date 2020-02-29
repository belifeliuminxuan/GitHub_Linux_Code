/**********************************************************
 * Author   : liuminxuan
 * Email    : liuminxuan1024@163.com
 * Time     : 2020-02-29 22:21
 * FileName : Student.cpp
 * *******************************************************/

#include <iostream>
using namespace std;

class Student
{
  public:
    Student()
    {
      cout<<"i am test "<<endl;
    }
    Student(const Student& stu)
    {
      cout<<"i am"<<endl;
    }
  private:
    string m_strName;
};

int main()
{
  Student stu1;
  Student stu2=stu1;
  Student stu3(stu2);


  return 0;
}
