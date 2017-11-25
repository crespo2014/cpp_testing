#include "stdio.h"
#include <type_traits>
#include <stdint.h>

static constexpr size_t InitialFNV = 2166136261U;
static constexpr size_t FNVMultiple = 16777619;

#define GET_SZIE(str) sizeof(str)

#define GET_HASH(str)

template<class T>
class StringHash
{
public:
	template<unsigned prev, unsigned pos>
	static constexpr uint64_t compute()
	{
		return (prev ^ T::template get<pos>()) * FNVMultiple;
	}

	template<uint64_t prev, unsigned pos, unsigned len>
	static constexpr typename std::enable_if<(pos < len), uint64_t>::type hash()
	{
		return hash< compute<prev, pos>(), pos + 1, len>();
	}

	template<uint64_t prev, unsigned pos, unsigned len>
	static constexpr typename std::enable_if<(pos == len), uint64_t>::type hash()
	{
		return prev;
	}

	static constexpr uint64_t get()
	{
		return hash<InitialFNV, 0, T::len>();
	}

};

class StringReject
{
public:
	template<unsigned pos>
	static constexpr uint64_t get()
	{
		return "Reject"[pos];
	}
	static const unsigned len = sizeof("Reject") - 1;
};

template<class type>
void fnc(type* v)
{

}

template<class type>
void fnc(type v)
{

}

int main()
{
	uint64_t id = 0;
	switch(id)
	{
	case StringHash<StringReject>::get():break;
	}

	const static uint64_t a = StringHash<StringReject>::get();
	printf("%lu", a);
	return 0;
}

