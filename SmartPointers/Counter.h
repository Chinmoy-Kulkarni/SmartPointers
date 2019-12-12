#pragma once
#include <iostream>

using namespace std;

class Counter
{
public:
	Counter() : m_counter{0} 
	{
	};

	Counter(const Counter&) = delete;
	
	Counter& operator=(const Counter&) = delete;

	~Counter() 
	{
	};

	void Reset()
	{
		m_counter = 0;
	}

	unsigned int get()
	{
		return m_counter;
	}

	void operator++()
	{
		m_counter++;
	}

	void operator--()
	{
		m_counter--;
	}

	void operator++(int)
	{
		m_counter++;
	}

	void operator--(int)
	{
		m_counter--;
	}

	friend ostream& operator<<(ostream& os, const Counter& counter)
	{
		os << "Counter Value : " << counter.m_counter << endl;
		return os;
	}

private:
	unsigned int m_counter{};
};

