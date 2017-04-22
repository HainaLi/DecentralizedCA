#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "sha256.h"

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 32; idx++)
      printf("%02x",hash[idx]);
   printf("\n");
}

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

//outputs the hashed value
char * hashMessage(char * message) {
    int str_len = strlen(message);
    long hashmaxlen = 2.305843e18;

    //page 31. Step 1
    //str_len shouldn't be longer than hashmaxlen = (2^61)-1 = 2.305843e18
    if (str_len >= hashmaxlen){
        printf("%s\n", "Invalid. Message length is too long. Exiting.");
        exit(-1);
    }
    //unsigned char text1[]={"abc"};
    //page 31. Step 2
    //Convert M to bit string M'
    char * bit_string_message = stringToBinary(message);

    //Step 3. 
    //H = Hash(M')
	//unsigned char hash[SHA256_BLOCK_SIZE];
    unsigned char * hash = malloc(SHA256_BLOCK_SIZE);
	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx,bit_string_message,strlen(bit_string_message));
	sha256_final(&ctx,hash);
    //print_hash(hash);

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


int main(int argc,char *argv[]) {
    //SHA256 can only hash strings of length less than hashmaxlen = (2^61)-1 = 2.305843e18
	char * result = hashMessage("hello"); 

	return 0;
}