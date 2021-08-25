ch03 String Vector and Arrays

---



### 3.1 using 声明

需要注意以下几点：

+ 每个名字都需要独立的 using 声明，示例：

  ```c++
  #include<iostream>
  using std::cin;
  using std::cout;
  ```

+ 在头文件中，不应该使用 using 声明，因为头文件中的 using 声明，会扩展到所有引用它的文件中去，这可能会造成名字冲突。但是要用到的话，可以使用显示声明的方式，举个栗子：如果在头文件中，要用到 std 的 string ，则使用 `std::string` 的显式调用方式。像下面这个示例，使用显示调用的方式，代替 `using std::string` 申明：

  ```c++
  #ifndef SALES_DATA_H
  #define SALES_DATA_H
  #inlcude<string>
  struct Sales_data{
      std::string bookNo;
      unsigned units_sold = 0;
      double revenue = 0.0;
  };
  #endif
  ```



### 3.2 string

string 是 c++ 中的一个标准库类型，表示可变长的字符序列。在头文件 `#include<string>` 。

以下是一些常见的 string 操作。



定义和初始化 string 对象

```c++
string s1; //空串
string s2(s1); // s2 是 s1 的副本；
string s2 = s1; // s2是 s1 的副本；等价于上式；

string s3("value"); // s3 是 字面值 “value” 的副本；
string s3="value"; // s3 是 字面值 “value” 的副本，等价于上式；

string s4(n,"c"); // n个c组成的字符串
```



拷贝初始化和直接初始化

区分：如果使用等号（=）初始化一个变量，实际上执行拷贝初始化，编译器把等号右边的值拷贝到新创建的对象中去。如果不适用等号，则执行的是直接初始化。

```c++
string s5 = "hiya"; //拷贝初始化
string s6("value"); //直接初始化
```



string 的操作

```c++
string s;

os << s;
is>>s;

getline(is,s); //从 is 中读取一行赋值给s，并返回is

s.empty();
s.size();
s[n];

s1+s2;
s1=s2;
s1==s2;
s1!=s2;
<, <=, <, >=  //按字符的字典顺序，比较（自动区分大小写） 
```



关于读写 string 对象的几个示例操作：

读取未知数量的 string 对象：

```c++
int main()
{
	string word; 
    while(cin >> word) //反复读取，直至到达文件末尾
        cout << word << endl;
}
```

 使用 `getline()` 读取一整行：

```c++
int main()
{
    string line;
    while(getline(cin,line))//每次读入一整行，直到文件末尾
        // if(!line,empty())
        // if(line.size() > 80)
        cout << line << endl; //line里没有换行符
   	return 0;
}
```

getline 函数从给定的输入流中读入内容，直到遇到换行符（这个换行符也被读进来了），然后将这些读到的内容存入到 string 对象中去（注意，这里不存换行符）。可以推出，如果一开始读入的就是换行符，则 string 的就是个空 string。



字面值和 string 对象相加

先看示例：

```c++
string s1 = "hello, ";
string s2 = "world\n";

string s3=s1+s2; //ok, hello, world\n
s1+=s2; // s1=s1+s2

string s4 = s1 + ","; //ok, string 对象 + 字面值

string s5 = "hello" + ","; //error, 两个都是字面值
```

注意：

```c++
string s6 = s1 + ", " + "world"; //ok

//因为它等价于：
string tmp = s1 + ",";
string s6 = tmp + "world";

//加个（），一个意思
string s6 = (s1 + ", ") + "world";
```

调换一下字面值和string对象的顺序，则会出错：

```c++
string s7 = "hello" + ", " + s2; //error, 不能把字面值直接相加

//因为它等价于：
string tmp = "hello" + ","; // error, 两个都是字面值，不能相加

//加个（），更直观一些
string s7 = ("hello" + ", ") + s2;
```

字符串字面值和 string 对象的相加，之所以需要注意，是因为它们是不同的类型（主要是为了与C兼容）。



string对象中的字符

头文件 cctype 中，有许多处理字符的函数：

```c++
// cctype 头文件中的函数

isalnum(c); //为字母数字时，为真
isalpha(c); 
isdigit(c); 

ispunct(c); //标点符号

islower(c); //小写字母时，为真
isupper(c);

isspace(c); //空格

tolower(c);  //输出对用的小写字母
toupper(c);  //输出对应的大写字母
```



C++标准库中兼容了C语言的标准库，比如 ctype.h 在C++标准准库中，名为 cctype。如果 C++ 程序使用 C 语言标准库头文件，则名应该为 cname 而不是 name.h，尽管它们的内容是一样的。



处理每个字符

```c++
string str("some string");
for(auto c : str)
	cout << c << endl;
```



改变字符串中的字符

==如果要改变 string 对象中字符的值，必须把循环变量定义为引用类型==。（引用就是对象的别名，将引用作为循环控制变量时，这个变量被依次绑定在序列的每个元素上了，所以使用这个引用，我们就能改变它绑定的字符）。

```c++
string s("hello world！");
//to upper
for(auto &c : s)
    c = toupper(c); //c 是一个引用，所以赋值语句将改变s中字符的值
cout<<s<<endl; //HELLO WORLD!
```



改变个别字符

要访问 string 对象中的字符，只有两种方法：一种是使用下标（如`s[0]`），一种是使用迭代器。

+ 下标运算符`[]`输入参数是 `string::size_type()` ，返回值是该位置上字符的引用；
+ 注意检查下标的返回是否是0到 s.size()-1.



### 3.3 vector

vector 也是标准库类型，表示对象的集合，集合中的每个对象都有一个与之对应的索引，用于访问对象。vector 也叫做”容器“。

C++中有类模板，也有函数模板，其中 vector 是类模板。模板本身不是类或函数，可以看作是生成类和函数的一份说明。编译器根据模板创建类或函数的过程叫做实例化（instantiation）。  

使用声明：

```c++
#include<vector>
using std::vector;
```



定义和初始化

```c++
//常用
vector<T> v1; //v1是一个空vector，潜在元素是T类型的

vector<T> v2(v1); // v2元素是v1元素的副本
vector<T> v2=v1;  //等价于上式

vector<T> v3(n,val);  //v3 包含 n 个 val 元素
vector<T> v4(n);

vector<T> v5{a,b,c};
vector<T> v5 = {a,b,c}; //与上式等价
```



添加元素

```c++
vector<int> v2;
for (int i = 0; i<10;j++)
	v2.push_back(i);
```

开始时，创建一个空 vector 对象，在使用过程中，再动态添加元素，这一做法和C或java 是不同的，因为后者需要指定容量，而vector不用，因为vector能动态增长。



常用 vector 操作

```c++
v.empty();
v.size();
v.push_back(t);

v[n];
v1=v2; //用 v2 中的元素，拷贝替换 v1 中的元素

v1==v2; //当且仅当元素数量相同，且对应位置元素相同
v1!=v2;

< > <= >= //字典序进行比较
```

访问或修改 vector 中元素的方法，与string 对象中字符的方法一样（修改元素，使用引用方式），对应示例：

```c++
vector<int> v{1,2,3,4,5};
//修改元素
for (auto &i : v)
    i*=i;
//遍历
for (auto i : v)
    cout<< i << " ";
```

Note:

+ `vector<int>::size_type`，ok
+ `vector::size_type`，error



### 3.4 迭代器

除了使用下标运算符访问元素之外，还可以使用迭代器。迭代器提供对对象的间接访问。有效的迭代器或者指向某个元素或者指向容器中尾元素的下一位置。

```c++
auto b=v.begin(),e=v.end();
```

如果容器为空，则 begin 和 end 返回的是同一个迭代器，都是尾后迭代器。



迭代器运算符

```c++
*iter; // 返回迭代器 iter 所指元素的引用
iter -> mem; // 解引用 iter 并获取该元素中名为mem 的成员，等价于(*iter).mem

++iter;
--iter;

iter1!=iter2;
iter1==iter2;//如果迭代器指向同一个元素或为尾后迭代器，则两者相等
```



使用迭代器访问并修改元素

```c++
string s("some string");
if (s.begin() != s.end()){ // 确保s非空
    auto it = s.begin();
	*it = toupper(*it); //修改当前元素
}
```



begin 和 end 运算符

begin 和 end 返回的具体类型，是由对象是否是常量决定的，如果对象是常量，则begin 和 end 返回 const_iterator，如果对象不是常量，则返回 iterator。

```c++
vector<int> v;
const vector<int> cv;

auto it1 = v.begin();  //it1类型是vector<int>::iterator
auto it2 = cv.begin(); //it2类型是vector<int>::const_iterator
```

如果对象只需要读，而不需要写，最好使用`vector<int>::const_iterator`，但我们又不能回去修改 vector 类型为const，这个时候可以使用 cbegin() 和 cend()，来专门得到`vector<int>::const_iterator`。

```c++
auto it3 = v.cbegin(); // it3 类型是vector<int>::const_iterator
```



解引用和成员访问

解引用迭代器可以获得迭代器所指的对象，如果该对象的类型是类，在可以进一步访问它的成员，于是C++中定义了箭头运算符 `->` ，将解引用和成员访问两个操作结合在一起，即 `it->mem` 和 `(*it).mem` 是同一个意思。



#### 3.5 数组

区别于 vector，数组的长度是固定的。它们都是存储相同类型的元素。



数组初始化

```c++
unsigned cnt = 42;
constexpr unsigned sz = 42; //常量表达式

int arr[10]; //整型数组
int *parr[10]; // 整型指针的数组

string bad[cnt]; //error ,cnt 不是常量表达式
string strs[sz]; //ok, sz 是 constexpr 
```

 定义数组的时候，必须指定数组类型，不允许使用 auto 关键字 推荐类型。数组元素必须是对象。



数组和指针

通常使用取地址符来获取指向某个对象的指针，取地址符可以用于任何对象。

数组元素也是对象，所以对数组的元素使用取地址符就能得到指向该元素的指针。

```c++
string nums[] = {"one","two","three"};
string *p = &nums[0]; // p 指向 nums 的第一个元素

string *p2 = nums; //编译器会自动将其替换为一个指向数组首元素的指针。等价于 p2 = &nums[0]
```



使用指针遍历

```c++
int arr[]={0,1,2,3,4,5,6,7,8,9};
int p = arr; // 指向第一个元素，也可以写为 int *p= &arr[0];
int *e = &arr[10]; // 指向最后一个元素
//遍历
for (int * b = arr; b! = e; ++b){
    cout << *b << endl;
}
```



