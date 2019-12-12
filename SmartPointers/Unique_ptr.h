#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Unique_ptr
{
public:
	Unique_ptr() : m_data(nullptr)
	{
	}

	explicit Unique_ptr(T* data) : m_data(data)
	{
	}

	~Unique_ptr()
	{
		delete m_data;
	}

	Unique_ptr(std::nullptr_t) : m_data(nullptr)
	{
	}

	Unique_ptr& operator=(std::nullptr_t)
	{
		reset();
		return *this;
	}
	
	// Move Semantics
	Unique_ptr(Unique_ptr&& up) noexcept
	{
		up.swap(*this);
	}

	Unique_ptr& operator=(Unique_ptr&& up) noexcept
	{
		up.swap(*this);
		return *this;
	}

	// Constructor/Assignment for use with types derived from T
	template<typename U>
	Unique_ptr(Unique_ptr<U>&& up)
	{
		Unique_ptr<T> tmp(up.release());
		tmp.swap(*this);
	}

	template<typename U>
	Unique_ptr& operator=(Unique_ptr<U>&& up) 
	{
		Unique_ptr<T> tmp(up.release());
		tmp.swap(*this);
		return *this;
	}

	// Remove complier generated copy constructor.
	Unique_ptr(Unique_ptr const&) = delete;
	Unique_ptr& operator=(Unique_ptr const&) = delete;

	// Const correct access owned objects
	T* operator->() const
	{
		return m_data;
	}

	T& operator*() const 
	{
		return *m_data;
	}

	// Access Smart pointer state
	T* get() const
	{
		return m_data;
	}

	explicit operator bool() const
	{
		return m_data;
	}

	// Modify Object state
	T* release() noexcept
	{
		T* result = nullptr;
		std::swap(result, m_data);
		return result;
	}

	void swap(Unique_ptr& src) noexcept
	{
		std::swap(m_data, src.m_data);
	}

	void reset()
	{
		T* tmp = release();
		delete tmp;
	}

	friend ostream& operator<<(ostream& os, Unique_ptr<T>& up)
	{
		os << "Address Pointed : " << up.get() << endl;
		return os;
	}

private:
	T* m_data;
};

template<typename T>
void swap(Unique_ptr<T>& lhs, Unique_ptr<T>& rhs)
{
	lhs.swap(rhs);
}
