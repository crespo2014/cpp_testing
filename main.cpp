#include "stdio.h"
#include <type_traits>
#include <stdint.h>
#include <vector>
#include <string.h>
#include <algorithm>

static constexpr size_t InitialFNV = 2166136261U;
static constexpr size_t FNVMultiple = 16777619U;

#define GET_SZIE(str) sizeof(str)

#define GET_HASH(str)

template<class T>
class StringHash
{
public:
	template<uint64_t prev, unsigned pos>
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


inline uint64_t getHash(const char* str)
{
	uint64_t v = InitialFNV;
	for (;*str; str++ )
	{
		v = (v ^ (uint64_t)(*str)) * FNVMultiple;
	}
	return v;
}


#define DEFINE_STRING_OBJECT(id, type, str, ...) \
	struct String##id {  template<unsigned pos>  static constexpr uint64_t get() { return str[pos]; }  static const unsigned len = sizeof(str) - 1; };

#define FOR_EACH_FIELD(MACRO)  \
		MACRO( Accept                  ,MFTYPE_ASCII  ,"Accept"                       ,true ) \
        MACRO( AcceptCharset           ,MFTYPE_ASCII  ,"Accept-Charset"               ,true ) \
        MACRO( AcceptEncoding          ,MFTYPE_ASCII  ,"Accept-Encoding"              ,true ) \
        MACRO( AcceptLanguage          ,MFTYPE_ASCII  ,"Accept-Language"              ,true ) \
        MACRO( AcceptRanges            ,MFTYPE_ASCII  ,"Accept-Ranges"                ,true ) \
        MACRO( Age                     ,MFTYPE_UINT64 ,"Age"                          ,false ) \
        MACRO( Allow                   ,MFTYPE_ASCII  ,"Allow"                        ,true ) \
        MACRO( Authorization           ,MFTYPE_ASCII  ,"Authorization"                ,false ) \
        MACRO( CacheControl            ,MFTYPE_ASCII  ,"Cache-Control"                ,true ) \
        MACRO( Cookie                  ,MFTYPE_ASCII  ,"Cookie"                       ,false ) \
        MACRO( Connection              ,MFTYPE_ASCII  ,"Connection"                   ,true ) \
        MACRO( ContentEncoding         ,MFTYPE_ASCII  ,"Content-Encoding"             ,true ) \
        MACRO( ContentLanguage         ,MFTYPE_ASCII  ,"Content-Language"             ,true ) \
        MACRO( ContentLength           ,MFTYPE_UINT64 ,"Content-Length"               ,false ) \
        MACRO( ContentLocation         ,MFTYPE_ASCII  ,"Content-Location"             ,false ) \
        MACRO( ContentMD5              ,MFTYPE_ASCII  ,"Content-MD5"                  ,false ) \
        MACRO( ContentRange            ,MFTYPE_ASCII  ,"Content-Range"                ,false ) \
        MACRO( ContentType             ,MFTYPE_ASCII  ,"Content-Type"                 ,false ) \
        MACRO( Date                    ,MFTYPE_ASCII  ,"Date"                         ,false ) \
        MACRO( ETag                    ,MFTYPE_ASCII  ,"ETag"                         ,false ) \
        MACRO( Expect                  ,MFTYPE_ASCII  ,"Expect"                       ,true ) \
        MACRO( Expires                 ,MFTYPE_ASCII  ,"Expires"                      ,false ) \
        MACRO( From                    ,MFTYPE_ASCII  ,"From"                         ,false ) \
        MACRO( Host                    ,MFTYPE_ASCII  ,"Host"                         ,false ) \
        MACRO( IfMatch                 ,MFTYPE_ASCII  ,"If-Match"                     ,false ) \
        MACRO( IfRange                 ,MFTYPE_ASCII  ,"If-Range"                     ,false ) \
        MACRO( KeepAlive               ,MFTYPE_ASCII  ,"Keep-Alive"                   ,false ) \
        MACRO( LastModified            ,MFTYPE_ASCII  ,"Last-Modified"                ,false ) \
        MACRO( Origin                  ,MFTYPE_ASCII  ,"Origin"                       ,false ) \
        MACRO( Pragma                  ,MFTYPE_ASCII  ,"Pragma"                       ,true ) \
        MACRO( Range_                  ,MFTYPE_ASCII  ,"Range"                        ,false ) \
        MACRO( Referer                 ,MFTYPE_ASCII  ,"Referer"                      ,false ) \
        MACRO( SecWebSocketAccept      ,MFTYPE_ASCII  ,"Sec-WebSocket-Accept"         ,false ) \
        MACRO( SecWebSocketExtensions  ,MFTYPE_ASCII  ,"Sec-WebSocket-Extensions"     ,false ) \
        MACRO( SecWebSocketKey         ,MFTYPE_ASCII  ,"Sec-WebSocket-Key"            ,false ) \
        MACRO( SecWebSocketVersion     ,MFTYPE_ASCII  ,"Sec-WebSocket-Version"        ,false ) \
        MACRO( Server                  ,MFTYPE_ASCII  ,"Server"                       ,false ) \
        MACRO( SetCookie               ,MFTYPE_ASCII  ,"Set-Cookie"                   ,true ) \
        MACRO( TransferEncoding        ,MFTYPE_ASCII  ,"Transfer-Encoding"            ,true ) \
        MACRO( Upgrade                 ,MFTYPE_ASCII  ,"Upgrade"                      ,true ) \
        MACRO( UserAgent               ,MFTYPE_ASCII  ,"User-Agent"                   ,false ) \
        MACRO( Vary                    ,MFTYPE_ASCII  ,"Vary"                         ,true ) \
        MACRO( Via                     ,MFTYPE_ASCII  ,"Via"                          ,true ) \
        MACRO( WwwAuthenticate         ,MFTYPE_ASCII  ,"WWW-Authenticate"             ,false ) \
        MACRO( Location                ,MFTYPE_ASCII  ,"Location"                     ,false ) \
        MACRO( TE                      ,MFTYPE_ASCII  ,"TE"                           ,false ) \
        MACRO( IfUnmodifiedSince       ,MFTYPE_ASCII  ,"If-Unmodified-Since"          ,false ) \
        MACRO( IfModifiedSince         ,MFTYPE_ASCII  ,"If-Modified-Since"            ,false ) \
        MACRO( IfNoneMatch             ,MFTYPE_ASCII  ,"If-None-Match"                ,false ) \
        MACRO( XForwardedFor           ,MFTYPE_ASCII  ,"X-Forwarded-For"              ,false ) \
        MACRO( ContentDisposition      ,MFTYPE_ASCII  ,"Content-Disposition"          ,false ) \
        MACRO( TrueClientIP            ,MFTYPE_ASCII  ,"True-Client-IP"               ,false ) \
        MACRO( HostName                ,MFTYPE_ASCII  ,"HostName"                     ,false ) \

#define STRING_HASH_CASE(id, type, str, ...) \
    case StringHash<String##id>::get(): return str;

#define TEST_HASH(id, type, str, ...) \
	if (findStr(getHash(str)) == 0) abort();

#define TEST_SEARCH(id, type, str, ...) \
	if (findStr(StaticString(str, sizeof(str)- 1)) == 0) abort();

#define PRINT_HASH(id, type, str, ...) \
	printf("%llX %llX \r\n", getHash(str), StringHash<String##id>::get());

#define ADD_TO_VECTOR(id, type, str, ...) \
    str_vector.emplace_back(str);


FOR_EACH_FIELD(DEFINE_STRING_OBJECT)

class StaticString
{
public:
	StaticString(const char* str) : size(strlen(str)) , str(str) {}
	StaticString(const char* str, unsigned len) : size(len) , str(str) {}

	unsigned size;
	const char* str;
	bool operator<(const StaticString& s) { return size < s.size || (size == s.size && strcmp(str, s.str) < 0); }
};

static std::vector<StaticString> str_vector;

void fillVector()
{
	FOR_EACH_FIELD(ADD_TO_VECTOR)
    std::sort(str_vector.begin(), str_vector.end());
}

const char* findStr(const StaticString& str)
{
	auto it = std::lower_bound(str_vector.begin(), str_vector.end(), str);
	if (it != str_vector.end())
		return it->str;
	return 0;
}

const char* findStr(uint64_t hash)
{
	switch(hash)
	{
	FOR_EACH_FIELD(STRING_HASH_CASE)
	}
	return 0;
}

inline void TestSearchByHash()
{
	FOR_EACH_FIELD(TEST_HASH);
}

inline void TestSearchByString()
{
	FOR_EACH_FIELD(TEST_SEARCH);
}


int main()
{
	fillVector();
	TestSearchByHash();
	TestSearchByString();
	return 0;
}

