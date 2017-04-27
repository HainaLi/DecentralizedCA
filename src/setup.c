#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <gmp.h>
#include "sha256.h"
#include <time.h>



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

int ascii_to_hex(char c)
{
        int num = (int) c;
        printf("ascii to hex: %i", num);
        if(num < 58 && num > 47)
        {
                return num - 48; 
        }
        if(num < 103 && num > 96)
        {
                return num - 87;
        }
        return num;
}

void hex_string_to_char_array(const char * hex_string) {
  int length = strlen(hex_string);
  int i;
  char buf = 0;
  
  for(i = 0; i < length; i++){
    if(i % 2 != 0){
      printf("\\x%hhX", hex_to_ascii(buf, hex_string[i]));
  
    }else{
      buf = hex_string[i];
    }
  }

}

void write_hex_string_to_char_array(const char * hex_string1, char* filename) {
    int length = strlen(hex_string1);
    int i;
    char buf = 0;
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }  
    for(i = 0; i < length; i++){
        if(i % 2 != 0){
          fprintf(f, "%02hhX", hex_to_ascii(buf, hex_string1[i]));

        }else{
          buf = hex_string1[i];
        }
    }


    fclose(f);
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

void print_hash(unsigned char hash[], int length)
{
   int idx;
   for (idx=0; idx < length; idx++)
      //printf("%02x",hash[idx]);
    printf("x%02x",hash[idx]);
   printf("\n");
}

//outputs the hashed value
char * hashMessage(char * message, int log_2_n) {
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
    //ceiling(log2n) < 8*haslen -> output left most log2n bits of hash
    //ceiling(log2n) >= 8*haslen -> output hash
    
    int hash_len = strlen(hash);

    int comparison = 8*hash_len; 

    if (log_2_n < comparison) {
        int target_len = log_2_n/8; 
        char subchar[target_len];
        memcpy(subchar, &hash[0], target_len);
        //subchar[target_len] = "\0";
        print_hash(subchar, target_len); 
        //return subchar;
    }
    else {
        print_hash(hash, 32);
        //return hash; 
    }
    


    //5.2: we're comparing n >= 2^(8*hashlen) , there's no log in gmp, so we're just going to intput the log2(n)
    /*  
    mpz_t n_mpf; 
    mpz_init(n_mpf);
    mpz_set_str(n_mpf, "115792089237316195423570985008687907853269984665640564039457584007913129639936", 10); //1.16e77
    gmp_printf("%i\n", n_mpf); 

    mpz_t param_n;
    mpz_init(param_n);
    mpz_set_str(param_n, param_string_n, 16);

    gmp_printf("%Zx\n", param_n);

    mpz_clear(param_n);
    mpz_clear(n_mpf);
    */
    

    
    
}
/* Prepends t into s. Assumes s has enough space allocated
** for the combined string.
*/
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}


char * generate_big_num(int size) {
    mpz_t rand_Num;
    unsigned long int i;
    gmp_randstate_t r_state;

    srand(time(NULL));   // should only be called once
    unsigned long int seed = rand() % 10000;      // so the seed doesn't get too big
    //seed = 1236;
    //printf("%i\n", seed);

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    mpz_init(rand_Num);

    mpz_urandomb(rand_Num,r_state,size);
    //gmp_printf("%Zx\n", rand_Num);
    char * rand_char = mpz_get_str(NULL, 16, rand_Num);
    int rand_length = strlen(rand_char);
    //printf("%i\n", strlen(rand_char));
    char *final = malloc(48);  
    strcpy(final, rand_char);
    for(int i=rand_length;i<=48;i++){
        strcpy(final, final);
        prepend(final, "0");
    }
    free(rand_char);
    gmp_randclear(r_state);
    mpz_clear(rand_Num);  
    return final; 

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

char * read_hex_file(char * file_name) {
    int hex_length = 48; 
    FILE *fp = fopen(file_name,"r");
    unsigned char c1,c2;
    int i=0;
    unsigned char sum;
    //static unsigned char final_hex[hex_length/2];
    char * final_hex = (char *) malloc(hex_length/2);
    for(i=0;i<hex_length/2;i++)
    {
            c1 = hex_to_int(fgetc(fp));
            c2 = hex_to_int(fgetc(fp));
            
            sum = c1<<4 | c2;
            final_hex[i] = sum;
            //printf("%i ",sum);
    }
    //printf("\n");
    fclose(fp);
    return final_hex; 

}

int main(int argc,char *argv[]) {
    //SHA256 can only hash strings of length less than hashmaxlen = (2^61)-1 = 2.305843e18
    
    printf("Generating random big numbers...\n");
    char * rand0 = generate_big_num(48*4);
    unsigned int retTime = time(0) + 1;   // Get finishing time.
    while (time(0) < retTime); 
    char * rand1 = generate_big_num(48*4);
    //printf("%c\n", rand0[0]);
    //printf("%c\n", rand1[0]);

    printf("Printing random big numbers out to rand_key0.txt and rand_key_1.txt...\n");
    //char * param_string_n = "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D";
    write_hex_string_to_char_array(rand0, "rand_key0.txt"); 
    write_hex_string_to_char_array(rand1, "rand_key1.txt"); 
    int log2n = 192; 

    //char * tbscertificate = "../certificates/sample_tbscertificate.txt";
    //char * keys_file = "rand_keys.txt";

    char * key0 = read_hex_file("rand_key0.txt"); 
    char * key1 = read_hex_file("rand_key1.txt"); 
    //printf("%02hhX\n", key0[0]);
    //printf("%02hhX\n", key1[0]);

    free(rand0);
    free(rand1); 
    free(key0);
    free(key1);

    

    
    /*

    hashMessage(buffer, log2n); 
    */
    
    


    return 0;
}