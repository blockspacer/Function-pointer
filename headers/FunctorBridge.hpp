#pragma once

#include "TryEquals.hpp"

template<typename R, typename ... Args>
class FunctorBridge
{
public:
	virtual ~FunctorBridge() {}

	virtual FunctorBridge* clone() const = 0;
	virtual R invoke(Args... args) const = 0;
	virtual bool equals(FunctorBridge const* fb) const = 0;
};

template<typename Functor, typename R, typename ... Args>
class SpecificFunctorBridge : public FunctorBridge<R, Args...>
{
	Functor functor;

public:

	template<typename FunctorFwd>
	SpecificFunctorBridge(FunctorFwd&& functor)
		: functor(std::forward<FunctorFwd>(functor))
	{}

	virtual SpecificFunctorBridge* clone() const override
	{
		return new SpecificFunctorBridge(functor);
	}

	virtual R invoke(Args... args) const override
	{
		return functor(std::forward<Args>(args)...);
	}

	virtual bool equals(FunctorBridge<R, Args...> const* fb) const override
	{
		if (auto specFb = dynamic_cast<SpecificFunctorBridge const*>(fb))
			return TryEquals<Functor>::equals(functor, specFb->functor);

		return false;
	}
};