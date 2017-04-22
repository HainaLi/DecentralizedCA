#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha256.c"

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 32; idx++)
      printf("%02x",hash[idx]);
   printf("\n");
}

char * hashMessage(char * message) {

	unsigned char hash[32];
	SHA256_CTX ctx;

	// Hash one
	sha256_init(&ctx);
	sha256_update(&ctx,message,strlen(message));
	sha256_final(&ctx,hash);
	print_hash(hash);

	return hash;
	
}
/*
char * bit_string_to_octet_string_conversion() {
    long int binarynum, octalnum = 0, j = 1, remainder;
 
    while (binarynum != 0)
    {
        remainder = binarynum % 10;
        octalnum = octalnum + remainder * j;
        j = j * 2;
        binarynum = binarynum / 10;
    }
    return octalnum; 
}
*/
char* stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

int main(int argc,char *argv[]) {
	char * binary = stringToBinary("hello");
	printf("%s\n", binary);
	hashMessage("binary"); 

	return 0;
}