//todo chage this
#define SSL_SERVER_EXPORT

#ifdef SSL_SERVER_EXPORT
#define SSL_SERVER_API _declspec(dllexport)
#else
#define SSL_SERVER_API _declspec(dllimport)
#endif
