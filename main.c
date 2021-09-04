#include <stdio.h>
#include <stdlib.h>

#include "base64EncodingDecoding.h"

int main()
{
    char 		*encbuffer = NULL;
    unsigned char 	*decbuffer = NULL;
    char 		*txt 	   = "AAAABCDFSINUGBHHJK<<MNBCVVG(*&98756#$%@RGSDFGHSRT^%YSEDFBHGHKJT&*%&UK?ADF<VGSFB>@:#$%^)~";
    int 		iRes 	   = 0;
    int 		i          = 0;
    
    setvbuf(stdout, NULL, _IONBF, 0); 

    printf("input string: %s\n", txt);
    if (base64_encode(base64_encode_normal,txt, strlen(txt), &encbuffer) > 0)
    {
        printf("encoded to base64: %s\n",encbuffer); 

  	iRes = base64_decode(base64_encode_normal, encbuffer, strlen(encbuffer), &decbuffer);
	if (iRes > 0)
	{
		printf("decoded from base64:"); 
		for (i = 0; i < iRes ; i++)
		{
			printf("%c", decbuffer[i]);
		}
		printf("\n");
		free(decbuffer);
	}
        free(encbuffer);
    }

    return 0;
}
