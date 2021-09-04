#include "base64EncodingDecoding.h"

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

char *base64_Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *base64_Table_UrlSafe = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";


size_t findIndex(unsigned char c, unsigned char * buffer)
{
	size_t index = (size_t)strchr(buffer, c);

	return  index ? index - (size_t)buffer : 0;
}

int base64_encode(char mode, unsigned char *data, size_t len, char **outbuffer)
{
	unsigned char   tmp             = 0;
	char            offset          = 0;
	unsigned char   mask            = 0;
	size_t          dataIndex       = 0;
	int             dataSizeInBytes = (len * 8);
	int             padding         = ((dataSizeInBytes % 6) % 3);
	int             outLen          = (dataSizeInBytes / 6) + padding + ( padding ? 1 : 0 );
	int             count           = (outLen - padding);
	int             i               = 0;
	char            *buf            = NULL;
	
	if ( mode < base64_encode_normal || mode > base64_encode_UrlSafe)
	{
	    perror("Encoding mode is Invalid\n");
	    
	    return 0;
	}
	
	buf = (char*) malloc(outLen + 1);
	if (buf == NULL)
	{
		perror("Memory allocation failed.\n");
		
		return 0;
	}
	
	memset(buf, 0 , outLen+1);
	
	for (i = 0 ; i < count; i++)
	{
	    mask = 0xff >> (8 - offset);
	    mask = mask ? mask : 0xff;
		if (offset == 0)
		{
			tmp = data[dataIndex] >> 2;
		}
		else
		{
			tmp = ((data[dataIndex] & mask) << (6 - offset)) +
				((dataIndex + 1 < len ? (data[++dataIndex] & ~mask) : 0) >> (8-(6-offset)));
		}
		
		offset+=2;
		offset = offset > 6 ? 0: offset;
		
		if (mode == base64_encode_normal)
		{
			buf[i] = base64_Table[tmp];
		}
		else
		{
			buf[i] = base64_Table_UrlSafe[tmp];
		}
	}
	
 	memset(&buf[(outLen - padding)], '=', padding);
	*outbuffer = buf;
	
	return outLen;
}

int base64_decode(char mode, char* data, size_t len, unsigned char **out)
{
	char 		padding 	= 0;
	size_t 		count 		= 0;
	char            *buf            = NULL;
	int 		i 		= 0;
	int 		y		= 0;
	int 		outlen		= 0;
	unsigned char	tmp		= 0;
	unsigned char 	offset		= 2;
	unsigned char   *table		= NULL;
	int 		outindex 	= 0;

	switch (mode)
	{
	case base64_encode_normal:
		table = (unsigned char *)base64_Table;
		break;
	case base64_encode_UrlSafe:
		table = (unsigned char *)base64_Table_UrlSafe;
		break;
	default:
		perror("Encoding mode is Invalid\n"); 
   	    	return 0;
	}

	if (len < 4 || (len % 4) != 0)
	{
		perror("data format is Invalid\n");
		
		return 0;
	}
	
	padding = (data[len-1] == '=' ? (data[len - 2] == '='? 2: 1) : 0);
	count = len - padding;
	outlen = count * 6 / 8;
	buf = (char*) malloc(outlen);
	if (buf == NULL)
	{
		perror("Memory allocation failed.\n");
		
		return 0;
	}

	for ( y = 0 ; y < count ; y+=4)
	{
		if (strchr(table, data[i]) == NULL)
		{
			perror("this packet is not a base64 packet.\n");
			free(buf);

			return 0;
		}

		for ( i = y ; i < y + 3 & i < (count - 1) ; i++)
		{
			tmp = (i + 1 < count ? (findIndex(data[i], table)) << (offset ? offset : 2): (findIndex(data[i], table) >> offset))
				 + (i + 1 < count ? (findIndex(data[i + 1], table)) >> (6-offset): 0);
			buf[outindex++] = tmp;
			offset = offset < 6 ? offset+ 2 : 2;
		}
	}
	*out = buf;
	
	return outlen;
	
}

