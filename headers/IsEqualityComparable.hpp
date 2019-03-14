#pragma once

#include <utility>
#include <type_traits>

template<typename T>
class IsEqualityComparable
{
private:
	static void* conv(bool);

	template<typename U>
	static std::true_type test(decltype(conv(std::declval<U const&>() == std::declval<U const&>())));

	template<typename U>
	static std::false_type test(...);

public:
	static constexpr bool value = decltype(test<T>(nullptr))::value;
};


