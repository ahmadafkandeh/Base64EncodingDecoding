#ifndef BASE64ENCODEINGDECODING
#define BASE64ENCODEINGDECODING

#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

enum base64_encode_mode
{
	base64_encode_normal = 0,
	base64_encode_UrlSafe
};

int base64_decode(char mode, char* data, size_t len, unsigned char **out);
int base64_encode(char mode, unsigned char *data, size_t len, char **outbuffer);

#ifdef __cplusplus
}
#endif

#endif //BASE64_32ENCODEINGDECODING
