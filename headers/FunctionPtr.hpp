#pragma once

#include "FunctorBridge.hpp"



template<typename Signature>
class FunctionPtr;

template<typename R, typename ... Args>
class FunctionPtr<R(Args...)>
{
private:
	FunctorBridge<R, Args...>* bridge;

public:

	FunctionPtr() : bridge(nullptr) {}

	template<typename F>
	FunctionPtr(F&& f)
		: bridge(nullptr)
	{
		using Functor = std::decay_t<F>;
		using Bridge = SpecificFunctorBridge<Functor, R, Args...>;
		bridge = new Bridge(std::forward<F>(f));
	}

	R operator()(Args... args) const
	{
		return bridge->invoke(std::forward<Args>(args)...);
	}

	FunctionPtr(FunctionPtr const& other)
		: bridge(nullptr)
	{
		if (other.bridge)
			bridge = other.bridge->clone();
	}

	FunctionPtr(FunctionPtr&& other) : bridge(other.bridge)
	{
		other.bridge = nullptr;
	}

	FunctionPtr& operator=(FunctionPtr const& other)
	{
		FunctionPtr tmp(other);
		swap(*this, tmp);

		return *this;
	}

	FunctionPtr& operator=(FunctionPtr&& other)
	{
		delete bridge;
		bridge = other.bridge;
		other.bridge = nullptr;

		return *this;
	}


	~FunctionPtr()
	{
		delete bridge;
	}


	explicit operator bool() const
	{
		return bridge != nullptr;
	}

	friend void swap(FunctionPtr& fp1, FunctionPtr& fp2)
	{
		std::swap(fp1.bridge, fp2.bridge);
	}

	friend bool operator==(FunctionPtr const& f1, FunctionPtr const& f2)
	{
		if (!f1 || !f2)
		{
			return !f1 && !f2;
		}

		return f1.bridge->equals(f2.bridge);
	}

	friend bool operator!=(FunctionPtr const& fl, FunctionPtr const& f2)
	{
		return !(fl == f2);
	}

};

