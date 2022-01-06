/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 06 Jan 2022 09:55:15 AM CST
 @ File Name	: c++_memory_layout_test_2.cpp
 @ Description	: c++ 内存分布测试， 参考 http://www.vishalchovatiya.com/memory-layout-of-cpp-object/ 
 ************************************************************************/
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define MARCO_SEP << "," <<


/***************************************************
* Memory Layout of Simple & Non-Polymorphic Object in C++ 
***************************************************/
/*
      |                        |          
      |------------------------| <------ X class object memory layout
      |        int X::x        |
      |------------------------|  stack segment
      |       float X::xx      |       |   
      |------------------------|       |
      |                        |      \|/
      |                        |    
      |                        |
------|------------------------|----------------
      |         X::X()         | 
      |------------------------|       |   
      |        X::~X()         |       |
      |------------------------|      \|/
      |      X::printInt()     |  text segment
      |------------------------|
      |     X::printFloat()    |
      |------------------------|
      |                        |            
class X {
public:
    int     x;
    float   xx;
public:
    X() {}
    ~X() {}
    void printInt() {}
    void printFloat() {}
};
*/

/***************************************************
* Layout of an Object With Virtual Function & Static Data Member
* 不同的编译器， vptr的位置不同，如gcc 就是在第一个8字节中。 而不是最后。
*
***************************************************/
/*
      |                        |          
      |------------------------| <------ X class object memory layout
      |        int X::x        |
stack |------------------------|
  |   |       float X::xx      |                      
  |   |------------------------|      |-------|--------------------------|
  |   |         X::_vptr       |------|       |       type_info X        |
 \|/  |------------------------|              |--------------------------|
      |           o            |              |    address of X::~X()    |
      |           o            |              |--------------------------|
      |           o            |              | address of X::printAll() |
      |                        |              |--------------------------|
      |                        |
------|------------------------|------------
      |  static int X::count   |      /|\
      |------------------------|       |
      |           o            |  data segment           
      |           o            |       |
      |                        |      \|/
------|------------------------|------------
      |        X::X()          | 
      |------------------------|       |   
      |        X::~X()         |       |
      |------------------------|       | 
      |      X::printAll()     |      \|/ 
      |------------------------|  text segment
      |      X::printInt()     |
      |------------------------|
      |     X::printFloat()    |
      |------------------------|
      | static X::printCount() |
      |------------------------|
      |                        |

class X {
public:
    int         x;
    float       xx;
    static int  count;

public:
    X() {}
    virtual ~X() {}

    virtual void printAll() {}
    void printInt() {}
    void printFloat() {}
    static void printCount() {}
};
*/

/***************************************************
* Layout of C++ Object With Inheritance 
* NOTE : 
*	不同于多重继承， 单一继承链中， 只有最先的polymorphic基类有vptr， 因为派生类的空间包含基类空间， 故使用中间派生类对象指针时， 也能拥有vptr。
***************************************************/


/*
      |                              |          
      |------------------------------| <------ Y class object memory layout
      |          int X::x            |
stack |------------------------------|
  |   |              int string::len |
  |   |string X::str ----------------|
  |   |            char* string::str |         
 \|/  |------------------------------|      |-------|--------------------------|
      |           X::_vptr           |------|       |       type_info Y        |
      |------------------------------|              |--------------------------|
      |          int Y::y            |              |    address of Y::~Y()    |
      |------------------------------|              |--------------------------|
      |               o              |              | address of Y::printAll() |
      |               o              |              |--------------------------|
      |               o              |              
------|------------------------------|--------
      |           X::X()             | 
      |------------------------------|       |   
      |           X::~X()            |       |
      |------------------------------|       | 
      |         X::printAll()        |      \|/ 
      |------------------------------|  text segment
      |           Y::Y()             |
      |------------------------------|
      |           Y::~Y()            |
      |------------------------------|
      |         Y::printAll()        |
      |------------------------------|
      |      string::string()        |
      |------------------------------|
      |      string::~string()       |
      |------------------------------|
      |      string::length()        |
      |------------------------------|
      |               o              |
      |               o              |
      |               o              |
      |                              |


class X {
    int     x;
    string str;

public:
    X() {}
    virtual ~X() {}

    virtual void printAll() {}
};

class Y : public X {
    int     y;

public:
    Y() {}
    ~Y() {}

    void printAll() {}
};

*/

/***************************************************
* Memory Layout of an Object With Multiple Inheritances & Virtual Function 
* 
* Note:
*	In multiple inheritance hierarchy, an exact number of the virtual table pointer(_vptr) created will be N-1, where N represents the number of classes(polymorphic).
***************************************************/

/*
      |                              |          
      |------------------------------| <------ Z class object memory layout
stack |          int X::x            |         
  |   |------------------------------|                  |--------------------------|      
  |   |          X:: _vptr           |----------------->|       type_info Z        |
  |   |------------------------------|                  |--------------------------|
 \|/  |          int Y::y            |                  |    address of Z::~Z()    |
      |------------------------------|                  |--------------------------|
      |          Y:: _vptr           |------|           |   address of Z::printX() |
      |------------------------------|      |           |--------------------------|
      |          int Z::z            |      |           |--------GUARD_AREA--------|    
      |------------------------------|      |           |--------------------------|
      |              o               |      |---------->|       type_info Z        |
      |              o               |                  |--------------------------|
      |              o               |                  |    address of Z::~Z()    |
      |                              |                  |--------------------------|
------|------------------------------|---------         |   address of Z::printY() |
      |           X::~X()            |       |          |--------------------------|  
      |------------------------------|       |          
      |          X::printX()         |       |        
      |------------------------------|       |         
      |           Y::~Y()            |      \|/        
      |------------------------------|  text segment
      |          Y::printY()         |                
      |------------------------------|                
      |           Z::~Z()            |                
      |------------------------------|                
      |          Z::printX()         |                
      |------------------------------|                
      |          Z::printY()         |                
      |------------------------------|                
      |          Z::printZ()         |                
      |------------------------------|                
      |               o              |                
      |               o              |                
      |                              |                


class X {
public:
    int     x;

    virtual ~X() {}
    virtual void printX() {}
};

class Y {
public:
    int     y;

    virtual ~Y() {}
    virtual void printY() {}
};

class Z : public X, public Y {
public:
    int     z;

    ~Z() {}
    void printX() {}
    void printY() {}
    void printZ() {}
};
*/

/***************************************************
* Layout of Object Having Virtual Inheritance 
*
* Note:
*	对于虚拟继承， 每个派生类中都会在vptr中添加对共享的虚基类的offset， 用于能够访问到共享的虚基类数据成员。
***************************************************/
/*
                  |                |          
 Y class  ------> |----------------| <------ A class object memory layout
sub-object        |   Y::y         |          
                  |----------------|             |------------------| 
                  |   Y::_vptr_Y   |------|      |    offset of X   | // offset(20) starts from Y 
 Z class  ------> |----------------|      |----> |------------------|     
sub-object        |   Z::z         |             |       .....      |     
                  |----------------|             |------------------|  
                  |   Z::_vptr_Z   |------|       
                  |----------------|      |        
 A sub-object --> |   A::a         |      |      |------------------| 
                  |----------------|      |      |    offset of X   | // offset(12) starts from Z
 X class -------> |   X::x         |      |----> |------------------|          
 shared           |----------------|             |       .....      |           
 sub-object       |                |             |------------------|           


class X { int x; };
class Y : public virtual X { int y; };
class Z : public virtual X { int z; };
class A : public Y, public Z { int a; };
*/


int main(int argc, char *argv[]) {
	// cout << sizeof(objx) MARCO_SEP offsetof(X, x) MARCO_SEP offsetof(X, xx) <<  endl;

	return 0;
}
