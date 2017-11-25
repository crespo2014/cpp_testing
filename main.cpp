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

PICK(MACRO, Accept                  ,MFTYPE_ASCII  ,"Accept"                       ,true ) \
        PICK(MACRO, AcceptCharset           ,MFTYPE_ASCII  ,"Accept-Charset"               ,true ) \
        PICK(MACRO, AcceptEncoding          ,MFTYPE_ASCII  ,"Accept-Encoding"              ,true ) \
        PICK(MACRO, AcceptLanguage          ,MFTYPE_ASCII  ,"Accept-Language"              ,true ) \
        PICK(MACRO, AcceptRanges            ,MFTYPE_ASCII  ,"Accept-Ranges"                ,true ) \
        PICK(MACRO, Age                     ,MFTYPE_UINT64 ,"Age"                          ,false ) \
        PICK(MACRO, Allow                   ,MFTYPE_ASCII  ,"Allow"                        ,true ) \
        PICK(MACRO, Authorization           ,MFTYPE_ASCII  ,"Authorization"                ,false ) \
        PICK(MACRO, CacheControl            ,MFTYPE_ASCII  ,"Cache-Control"                ,true ) \
        PICK(MACRO, Cookie                  ,MFTYPE_ASCII  ,"Cookie"                       ,false ) \
        PICK(MACRO, Connection              ,MFTYPE_ASCII  ,"Connection"                   ,true ) \
        PICK(MACRO, ContentEncoding         ,MFTYPE_ASCII  ,"Content-Encoding"             ,true ) \
        PICK(MACRO, ContentLanguage         ,MFTYPE_ASCII  ,"Content-Language"             ,true ) \
        PICK(MACRO, ContentLength           ,MFTYPE_UINT64 ,"Content-Length"               ,false ) \
        PICK(MACRO, ContentLocation         ,MFTYPE_ASCII  ,"Content-Location"             ,false ) \
        PICK(MACRO, ContentMD5              ,MFTYPE_ASCII  ,"Content-MD5"                  ,false ) \
        PICK(MACRO, ContentRange            ,MFTYPE_ASCII  ,"Content-Range"                ,false ) \
        PICK(MACRO, ContentType             ,MFTYPE_ASCII  ,"Content-Type"                 ,false ) \
        PICK(MACRO, Date                    ,MFTYPE_ASCII  ,"Date"                         ,false ) \
        PICK(MACRO, ETag                    ,MFTYPE_ASCII  ,"ETag"                         ,false ) \
        PICK(MACRO, Expect                  ,MFTYPE_ASCII  ,"Expect"                       ,true ) \
        PICK(MACRO, Expires                 ,MFTYPE_ASCII  ,"Expires"                      ,false ) \
        PICK(MACRO, From                    ,MFTYPE_ASCII  ,"From"                         ,false ) \
        PICK(MACRO, Host                    ,MFTYPE_ASCII  ,"Host"                         ,false ) \
        PICK(MACRO, IfMatch                 ,MFTYPE_ASCII  ,"If-Match"                     ,false ) \
        PICK(MACRO, IfRange                 ,MFTYPE_ASCII  ,"If-Range"                     ,false ) \
        PICK(MACRO, KeepAlive               ,MFTYPE_ASCII  ,"Keep-Alive"                   ,false ) \
        PICK(MACRO, LastModified            ,MFTYPE_ASCII  ,"Last-Modified"                ,false ) \
        PICK(MACRO, Origin                  ,MFTYPE_ASCII  ,"Origin"                       ,false ) \
        PICK(MACRO, Pragma                  ,MFTYPE_ASCII  ,"Pragma"                       ,true ) \
        PICK(MACRO, Range_                  ,MFTYPE_ASCII  ,"Range"                        ,false ) \
        PICK(MACRO, Referer                 ,MFTYPE_ASCII  ,"Referer"                      ,false ) \
        PICK(MACRO, SecWebSocketAccept      ,MFTYPE_ASCII  ,"Sec-WebSocket-Accept"         ,false ) \
        PICK(MACRO, SecWebSocketExtensions  ,MFTYPE_ASCII  ,"Sec-WebSocket-Extensions"     ,false ) \
        PICK(MACRO, SecWebSocketKey         ,MFTYPE_ASCII  ,"Sec-WebSocket-Key"            ,false ) \
        PICK(MACRO, SecWebSocketVersion     ,MFTYPE_ASCII  ,"Sec-WebSocket-Version"        ,false ) \
        PICK(MACRO, Server                  ,MFTYPE_ASCII  ,"Server"                       ,false ) \
        PICK(MACRO, SetCookie               ,MFTYPE_ASCII  ,"Set-Cookie"                   ,true ) \
        PICK(MACRO, TransferEncoding        ,MFTYPE_ASCII  ,"Transfer-Encoding"            ,true ) \
        PICK(MACRO, Upgrade                 ,MFTYPE_ASCII  ,"Upgrade"                      ,true ) \
        PICK(MACRO, UserAgent               ,MFTYPE_ASCII  ,"User-Agent"                   ,false ) \
        PICK(MACRO, Vary                    ,MFTYPE_ASCII  ,"Vary"                         ,true ) \
        PICK(MACRO, Via                     ,MFTYPE_ASCII  ,"Via"                          ,true ) \
        PICK(MACRO, WwwAuthenticate         ,MFTYPE_ASCII  ,"WWW-Authenticate"             ,false ) \

#define FOR_EACH_HTTP_HEADER_FIELD_V2(PICK, MACRO) \
        PICK(MACRO, Location                ,MFTYPE_ASCII  ,"Location"                     ,false ) \
        PICK(MACRO, TE                      ,MFTYPE_ASCII  ,"TE"                           ,false ) \
        PICK(MACRO, IfUnmodifiedSince       ,MFTYPE_ASCII  ,"If-Unmodified-Since"          ,false ) \
        PICK(MACRO, IfModifiedSince         ,MFTYPE_ASCII  ,"If-Modified-Since"            ,false ) \
        PICK(MACRO, IfNoneMatch             ,MFTYPE_ASCII  ,"If-None-Match"                ,false ) \
        PICK(MACRO, XForwardedFor           ,MFTYPE_ASCII  ,"X-Forwarded-For"              ,false ) \
        PICK(MACRO, ContentDisposition      ,MFTYPE_ASCII  ,"Content-Disposition"          ,false ) \
        PICK(MACRO, TrueClientIP            ,MFTYPE_ASCII  ,"True-Client-IP"               ,false ) \
        PICK(MACRO, HostName                ,MFTYPE_ASCII  ,"HostName"                     ,false ) \

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

