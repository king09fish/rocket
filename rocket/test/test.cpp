

#include<iostream>
#include <utility>      // std::move
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string
#include<memory>
#include<functional>
using namespace std;
class stu
{
public:
	stu();
	~stu();
	stu(stu &a);
	int test(string name);

	int js;
};

stu::stu()
{
	printf("construct sut\n");
	js = 2;
}
stu::stu(stu &a)
{
	printf("copy \n");
	js = 2;
}

stu::~stu()
{
	printf("delete funciton");
}
int stu::test(string name)
{
	//js = 88;
	printf("the stud test %s", name.c_str());
	return js;
}
int test(stu &&kk)
{
	std::cout << "------" << std::endl;

	kk.js = 2;
	return 1;
}




stu get()
{
	return stu();
}
typedef shared_ptr<stu> test_ptr;
int count(test_ptr test)
{
	cout << test.use_count() << endl;
	return 0;
}

class calc
{
public:
	calc(int base)
	{
		m_base = base;
	}

	int Add(int j)
	{
		m_base += j;
		return m_base;
	}

	int sub(int j)
	{
		m_base -= j;
		return m_base;
	}
protected:
	int m_base;
};

int main()
{	
	/*std::shared_ptr<stu> ptest(new stu());
	cout << ptest.use_count() << endl;
	count(ptest);
	*/
	/*stu *sut = new stu();
	sut->js = 99;
	//auto sayHello = std::bind(&stu::test, sut/*调用者*/ std::placeholders::_1/*参数1*/;
	//printf("before delete \n");
	//delete sut;
	//printf("end delete \n");
	//auto result = sayHello("Jack");
	//printf("the return value %d", result);*/
	

	int n = 8;
	if (n == 8)
	{
		n = n + 2;
		goto number8;
	}

number7:
	printf("number u");

number8:
	printf("the n = %d", n);
	int kw = 1;
	while (true)
	{
		kw = kw + 1;
		//printf("kkkkkkk");
		if (kw >= 4)
		{
			continue;
		}
		//printf("end now");
	}
	//shared_ptr<stu> ptest2(new stu());
	/*
	cout << ptest2->getStr() << endl;
	cout << ptest2.use_count() << endl;
	ptest = ptest2;//"456"引用次数加1，“123”销毁
	ptest->print();
	cout << ptest2.use_count() << endl;//2
	cout << ptest.use_count() << endl;//2
	ptest.reset();
	ptest2.reset();//此时“456”销毁
	cout << "done !\n";*/
	return 0;
}