#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <gmp.h>
#include "sha256.h"
#include <math.h>


//hex, int, char conversion functions
int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

void hex_string_to_char_array(const char * hex_string) {
  int length = strlen(hex_string);
  int i;
  char buf = 0;
  
  for(i = 0; i < length; i++){
    if(i % 2 != 0){
      printf("%i\n", hex_to_ascii(buf, hex_string[i]));
  
    }else{
      buf = hex_string[i];
    }
  }

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

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 32; idx++)
      printf("%02x",hash[idx]);
   printf("\n");
}

//outputs the hashed value
char * hashMessage(char * message, char * param_string_n) {
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

    //page 31 Step 3. 
    //H = Hash(M')
    //unsigned char hash[SHA256_BLOCK_SIZE];
    unsigned char * hash = malloc(SHA256_BLOCK_SIZE);
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx,bit_string_message,strlen(bit_string_message));
    sha256_final(&ctx,hash);
    //print_hash(hash);

    //page 45 Step 5: deriving an integer e from H (but we're calculating using char arrays, so we will leave the output in hex)
    //192 < 256 not needed for our current curve
    /*
    double hash_len = strlen(hash);
    double comparison = pow(2.0, (8*hash_len)); 
    int c = (double) comparison; 
    printf("%08x\n", c); 

    //5.2: we're comparing n >= 2^(8*hashlen)    
    mpz_t n_mpf; 
    mpz_init(n_mpf);
    mpz_set_str(n_mpf, "115792089237316195423570985008687907853269984665640564039457584007913129639936", 10);
    gmp_printf("%i\n", n_mpf); 

    mpz_t param_n;
    mpz_init(param_n);
    mpz_set_str(param_n, param_string_n, 16);

    gmp_printf("%Zx\n", param_n);

    mpz_clear(param_n);
    mpz_clear(n_mpf);
    */

    return hash;
    
}

void generate_big_num(int size, int num_bignums) {
    mpz_t rand_Num;
    unsigned long int i, seed;
    gmp_randstate_t r_state;

    seed = 123456;

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init(rand_Num);

    for(i = 0; i < num_bignums; ++i) {
       mpz_urandomb(rand_Num,r_state,size);
       gmp_printf("%Zx\n", rand_Num);
    }

    gmp_randclear(r_state);
    mpz_clear(rand_Num);  

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
    
    //generate_big_num(48*4, 4);

    char * param_string_n = "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D";
    char * result = hashMessage("hello", param_string_n); 
    print_hash(result); 


    return 0;
}