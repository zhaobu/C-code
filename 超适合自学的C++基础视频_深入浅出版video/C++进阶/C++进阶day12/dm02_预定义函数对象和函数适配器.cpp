
#include <iostream>
using namespace std;

#include "string"
#include <vector>
#include <list>
#include "set"
#include <algorithm>
#include "functional"


//plus<int> 预定义好的函数对象 能实现不同类型的数据的 + 运算
//实现了 数据类型 和算法的分离 ===》通过函数对象技术实现的。。。。

//思考：怎么样知道 plus<type> 是两个参数
void main21()
{
	/*
	template<class _Ty>
	struct plus
		: public binary_function<_Ty, _Ty, _Ty>
	{	// functor for operator+
		_Ty operator()(const _Ty& _Left, const _Ty& _Right) const
		{	// apply operator+ to operands
			return (_Left + _Right);
		}
	};
	*/
	plus<int> intAdd;
	int x = 10; 
	int y = 20;
	int z = intAdd(x, y); // x + y 
	cout << "z:" << z << endl;

	plus<string> stringAdd;

	string s1 = "aaa";
	string s2 = "bbb";
	string s3 = stringAdd(s1, s2);
	cout << "s3:" << s3 << endl;

	vector<string> v1;
	v1.push_back("bbb");
	v1.push_back("aaa");
	v1.push_back("ccc");
	v1.push_back("zzz");
	v1.push_back("ccc");
	v1.push_back("ccc");

	/*
	template<class _Ty>
	struct greater
		: public binary_function<_Ty, _Ty, bool>
	{	// functor for operator>
		bool operator()(const _Ty& _Left, const _Ty& _Right) const
		{	// apply operator> to operands
			return (_Left > _Right);
		}
	};
	*/
	sort(v1.begin(), v1.end(), greater<string>() );

	for (vector<string>::iterator it=v1.begin(); it!=v1.end(); it++)
	{
		cout << *it << endl;
	}

	//求 ccc 出现的个数
	string sc = "ccc";

	//equal_to<string>() 有两个参数 left参数来自容器，right参数来自sc
	//bind2nd函数适配器 ：把预定义函数对象 和 第二个参数进行绑定
	int num = count_if(v1.begin(), v1.end(), bind2nd(equal_to<string>(), sc) );
	cout << "num: " << num << endl;
}

class IsGreat
{
public:
	IsGreat(int i)
	{
		m_num = i;
	}
	bool operator()(int &num)
	{
		if (num > m_num)
		{
			return true;
		}
		return false;
	}
private:
	int m_num;
};

void main22()
{
	vector<int> v1;
	for (int i=0; i<10; i++)
	{
		v1.push_back(i+1);
	}
	for (vector<int>::iterator it=v1.begin(); it!=v1.end(); it++ )
	{
		cout << *it << " ";
	}
	cout << endl;

	int num1 = count(v1.begin(), v1.end(), 3);
	cout << "3的个数为: " << num1 <<endl;

	//通过 谓词 求大于2 的个数
	int num2 = count_if(v1.begin(), v1.end(),  IsGreat(2));
	cout << "通过谓词求大于2 的个数: " << num2 <<endl;

	/*
	template<class _Ty>
	struct greater
		: public binary_function<_Ty, _Ty, bool>
	{	// functor for operator>
		bool operator()(const _Ty& _Left, const _Ty& _Right) const
		{	// apply operator> to operands
			return (_Left > _Right);
		}
	};
	*/
	//通过 预定义的函数对象 求大于2 的个数
	//greater<int>() 有两个参数 左参数来自容器的元素 ，右参数固定成2 （通过bind2nd做的）
	int num3 = count_if(v1.begin(), v1.end(), bind2nd (greater<int>(), 2) );
	cout << "通过 预定义的函数对象bind2nd 求大于2 的个数: " << num3 <<endl;

	//如果使用bind1st就是这样
	int num31 = count_if(v1.begin(), v1.end(), bind1st(less<int>(),2));
	cout << "通过 预定义的函数对象bind1st 求大于2 的个数: " << num31 << endl;

	int t = 7;
	//求 奇数的个数.t=2时
	int num4 = count_if(v1.begin(), v1.end(), bind2nd (modulus<int>(), t) );

	//通过求余,能被t整除,则结果为0,不能整除,结果为真,所以就相当于是统计奇数
	transform(v1.begin(), v1.end(), v1.begin(), bind2nd(modulus<int>(), t));
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << "不能被"<<t<<"整除的个数为" << num4 <<endl;

	//求 偶数的个数 取反器(negator) 
	int num5 = count_if(v1.begin(), v1.end(), not1( bind2nd (modulus<int>(), 2) ) );

	//取反器(negator) : not1翻转一元预定义函数对象的真值,而not2翻转二元谓词函数的真值。
	transform(v1.begin(), v1.end(), v1.begin(),not1( bind2nd(modulus<int>(), t)));
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << "偶数的个数 num5:" << num5 <<endl;

}
void main222()
{
	//main21();
	main22(); //函数适配器综合案例
	cout<<"hello..."<<endl;
	return ;
}






