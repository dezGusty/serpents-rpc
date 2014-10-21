//todo chage this


#ifdef SSL_SERVER_EXPORT
#define SSL_SERVER_API _declspec(dllexport)
#else
#define SSL_SERVER_API _declspec(dllimport)
#endif
