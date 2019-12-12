#pragma once
#include <iostream>
#include "Counter.h"

using namespace std;

template <typename T>
class Shared_ptr
{
public:
	Shared_ptr() :
		m_ptr(nullptr), m_counter(nullptr)
	{
		*(m_counter)++;
	}

	explicit Shared_ptr(T* ptr = nullptr)
	{
		m_ptr = ptr;
		m_counter = new Counter();
		if (ptr)
		{
			(*m_counter)++;
		}
	}

	// Copy Constructor
	Shared_ptr(Shared_ptr<T>& sp)
	{
		m_ptr = sp.m_ptr;
		m_counter = sp.m_counter;
		(*m_counter)++;
	}

	Shared_ptr(Shared_ptr<T>&& sp)
	{
		m_ptr = sp.m_ptr;
		m_counter = sp.m_counter;
		sp.m_ptr = nullptr;
		sp.m_counter = nullptr;
	}


	Shared_ptr& operator=(T* p) 
	{
		Shared_ptr(*p).swap(*this);
		return *this;
	}

	Shared_ptr& operator=(Shared_ptr<T>& sp)
	{
		Shared_ptr(sp).swap(*this);
		return *this;
	}

	Shared_ptr& operator=(Shared_ptr<T>&& sp)
	{
		Shared_ptr(std::move(sp)).swap(*this);
		return *this;
	}

	// Reference cocunt
	unsigned int use_count()
	{
		return m_counter->get();
	}

	T* get() noexcept
	{
		return m_ptr;
	}

	T& operator*() noexcept
	{
		return *m_ptr;
	}

	T* operator->() noexcept
	{
		return m_ptr;
	}

	operator bool() const noexcept
	{
		return (m_ptr != nullptr);
	}

	void swap(Shared_ptr<T>& sp)
	{
		std:swap(m_ptr, sp.m_ptr);
		std:swap(m_counter, sp.m_counter);
	}

	// Destructor
	~Shared_ptr()
	{
		(*m_counter)--;
		if (m_counter->get() == 0)
		{
			delete m_counter;
			delete m_ptr;
		}
	}

	friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp)
	{
		os << "Address Pointed : " << sp.get() << endl;
		cout << *(sp.m_counter) << endl;
		return os;
	}

private:
	Counter* m_counter;
	T* m_ptr;
};

