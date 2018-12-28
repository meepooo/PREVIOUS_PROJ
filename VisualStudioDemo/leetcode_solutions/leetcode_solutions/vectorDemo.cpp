#include "vectorDemo.h"

//（1）a.assign(b.begin(), b.begin() + 3); //b为向量，将b的0~2个元素构成的向量赋给a
//（2）a.assign(4, 2); //是a只含4个元素，且每个元素为2
//（3）a.back(); //返回a的最后一个元素
//（4）a.front(); //返回a的第一个元素
//（5）a[i]; //返回a的第i个元素，当且仅当a[i]存在2013-12-07
//（6）a.clear(); //清空a中的元素
//（7）a.empty(); //判断a是否为空，空则返回ture,不空则返回false
//（8）a.pop_back(); //删除a向量的最后一个元素
//（9）a.erase(a.begin() + 1, a.begin() + 3); //删除a中第1个（从第0个算起）到第2个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+         3（不包括它）
//（10）a.push_back(5); //在a的最后一个向量后插入一个元素，其值为5
//（11）a.insert(a.begin() + 1, 5); //在a的第1个元素（从第0个算起）的位置插入数值5，如a为1,2,3,4，插入元素后为1,5,2,3,4
//（12）a.insert(a.begin() + 1, 3, 5); //在a的第1个元素（从第0个算起）的位置插入3个数，其值都为5
//（13）a.insert(a.begin() + 1, b + 3, b + 6); //b为数组，在a的第1个元素（从第0个算起）的位置插入b的第3个元素到第5个元素（不包括b+6），如b为1,2,3,4,5,9,8         ，插入元素后为1,4,5,9,2,3,4,5,9,8
//（14）a.size(); //返回a中元素的个数；
//（15）a.capacity(); //返回a在内存中总共可以容纳的元素个数
//（16）a.resize(10); //将a的现有元素个数调至10个，多则删，少则补，其值随机
//（17）a.resize(10, 2); //将a的现有元素个数调至10个，多则删，少则补，其值为2
//（18）a.reserve(100); //将a的容量（capacity）扩充至100，也就是说现在测试a.capacity();的时候返回值是100.这种操作只有在需要给a添加大量数据的时候才         显得有意义，因为这将避免内存多次容量扩充操作（当a的容量不足时电脑会自动扩容，当然这必然降低性能） 
//（19）a.swap(b); //b为向量，将a中的元素和b中的元素进行整体性交换
//（20）a == b; //b为向量，向量的比较操作还有!=,>=,<=,>,<

vectorDemo::vectorDemo()
{
}


vectorDemo::~vectorDemo()
{
}

int vectorDemo::getVectorValue()
{
	vector<int> vec;
	int i;

	// 显示 vec 的原始大小
	cout << "vector size = " << vec.size() << endl;

	// 推入 5 个值到向量中
	for (i = 0; i < 5; i++) {
		vec.push_back(i);
	}

	// 显示 vec 扩展后的大小
	cout << "extended vector size = " << vec.size() << endl;

	// 访问向量中的 5 个值
	for (i = 0; i < 5; i++) {
		cout << "value of vec [" << i << "] = " << vec[i] << endl;
	}

	// 遍历vector最简单的写法
	for (auto autov : vec)
	{
		cout << autov << endl;
	}

	// 使用迭代器 iterator 访问值
	vector<int>::iterator v = vec.begin();
	while (v != vec.end()) {
		cout << "value of v = " << *v << endl;
		v++;
	}

	// 判断空,boolapha输出true or false
	cout << "容器是否为空：" << boolalpha << vec.empty() << endl;

	// 计算size空间和capacity空间
	vector<string> v1(10);
	cout << "占用空间size:" << v1.size() << "占用空间capacity:" << v1.capacity() << endl;
	v1.push_back("aaaa");
	cout << "占用空间size:" << v1.size() << "占用空间capacity:" << v1.capacity() << endl;
	v1.push_back("bbbb");
	cout << "占用空间size:" << v1.size() << "占用空间capacity:" << v1.capacity() << endl;
	v1.push_back("cccc");
	cout << "占用空间size:" << v1.size() << "占用空间capacity:" << v1.capacity() <<  endl;
	v1.pop_back();//顶元素出栈
	cout << "占用空间size:" << v1.size() << "占用空间capacity:" << v1.capacity() << endl;
	
	// 插入元素，尾部插入push_back，任意位置插入insert
	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);

	cout << "v2 push_back 插入" << endl;
	for ( auto iter_v2: v2)
		cout << iter_v2 << endl;

	vector<int>::iterator it_v2 = v2.begin();
	it_v2++;
	v2.insert(it_v2,555);

	cout << "v2 insert value" << endl;
	for (auto iter_v2 : v2)
		cout << iter_v2 << endl;

	//v2.insert(it_v2, 4, 0);//insert 4 zero element at iterator it_v2
	//v2.insert(it_v2, v2.begin(), v2.end());// insert the whole v2

	// delete element
	vector<int> v3(4, 555);
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;
	// push to stack ,pop from statck top
	//v3.push_back(222);
	//v3.pop_back();
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;

	// delete any one element
	v3.erase(v3.begin());
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;
	// get element
	cout << v3[1] << endl;
	cout << v3.at(1) << endl;

	// delete the whole vector
	v3.erase(v3.begin(), v3.end());

	//算法
	vector<int> v8;
	v8.push_back(1);
	v8.push_back(5);
	v8.push_back(4);
	v8.push_back(2);
	v8.push_back(3);
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	reverse(v8.begin(), v8.end());//逆序，需要#include<algorithm>
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	sort(v8.begin(), v8.end()); //升序
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//定义排序比较函数，可进行降序排序
	//sort(v8.begin(), v8.end(), 0); //降序
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//二维数组
	cout << "********二维数组********" << endl;
	vector<vector<int>> v9;
	vector<int> v9_0(3, 4);
	vector<int> v9_1(3, 6);
	v9.push_back(v9_0);
	v9.push_back(v9_1);
	for (int i = 0; i < v9.size(); i++)
	{
		for (int j = 0; j < v9[0].size(); j++)
			cout << v9[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	return 0;
}
