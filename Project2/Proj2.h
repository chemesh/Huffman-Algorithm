#pragma once

#include <iostream>
#include<fstream>

using namespace std;



namespace GPD //General Program Data
{

	struct Item
	{
		int data;
		char key;

		Item() {}
		Item(const Item& o) : key(o.key), data(o.data) {}
		Item(const char& _key, const int& _data) :key(_key), data(_data) {}

		void operator=(const Item& o)
		{
			key = o.key;
			data = o.data;
		}
		friend ostream& operator<<(ostream& os, const Item& item)
		{
			os << item.data << ";" << item.key << " ";
			return os;
		}
	};
	


	template <class T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

}