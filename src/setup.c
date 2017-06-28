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
    printf("{");
    for (idx=0; idx < length; idx++) {
        printf("0x%02x",hash[idx]);
        if (idx != length-1) {
            printf(",");            
        }
    }
    printf("}\n");
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
    //H = Hash(M') M' is the bitstring
    unsigned char * hash = malloc(SHA256_BLOCK_SIZE);
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx,bit_string_message,strlen(bit_string_message));
    sha256_final(&ctx,hash);
    
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
        print_hash(hash, hash_len);
        //return hash; 
    }
    
    
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


void generate_big_num(char * p) {
    mpz_t rand_Num;
    mpz_init(rand_Num);
    unsigned long int i;
    gmp_randstate_t r_state;

    srand(time(NULL));   // should only be called once
    unsigned long int seed = rand() % 10000;      // so the seed doesn't get too big
    //seed = 1236;
    //printf("%i\n", seed);

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

    

    //generate a big number between 0 and p-2

    //Function: void mpz_urandomm (mpz_t rop, gmp_randstate_t state, const mpz_t n)

    mpz_t p_mpz_t; 
    mpz_init(p_mpz_t);
    mpz_set_str(p_mpz_t, p, 16);

    //need to submit p - 1, since we want a number between 0 and p-2, inclusive
    mpz_sub_ui(p_mpz_t, p_mpz_t, 1);
    mpz_urandomm(rand_Num,r_state,p_mpz_t); //generates a random integer between 0 and p_mpz_t-1, inclusive
    //gmp_printf("%Zx\n", rand_Num);
    char * rand_char = mpz_get_str(NULL, 16, rand_Num);
    int rand_length = strlen(rand_char);
    printf("{");
    for(int i=0;i<rand_length;i++){
        if (i % 2 == 0) {
            printf("0x");
        }
        printf("%c", rand_char[i]);
        if (i % 2 == 1 && i != rand_length-1) {
            printf(",");
        }
    }
    printf("}\n");

    free(rand_char);
    gmp_randclear(r_state);
    mpz_clear(rand_Num);  
    mpz_clear(p_mpz_t); 

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

    if (argc < 2) {
        printf("./setup.out generateBigNums p log2n \n or \n ./setup.out hashMessage log2n \n Or omit the p or log2n to use the default secp192k1 curve. \n The log2n is the number of bits of your curve. \n For example, for the default secp192k1 curve, \n log2n=192 \n");
        exit(0);
    }


    
    if (strcmp(argv[1], "generateBigNums") == 0) {
        printf("%s\n", argv[1]);
        char * p; 
        int log2n; 
        if (argc != 4) {
            //go with the default values of the secp192k1 curve
            p = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37"; 
            log2n = 192; 
        }
        else {
            p = argv[2]; 
            log2n = strtol(argv[3], NULL, 10);;
        }


        printf("Generating random big numbers...\n");
        generate_big_num(p);
        unsigned int retTime = time(0) + 1;   // Get finishing time.
        while (time(0) < retTime); 
        generate_big_num(p);

    }
    else if (strcmp(argv[1], "hashMessage") == 0) {
        int log2n;
        if (argc != 3) {
            //go with the default values of the secp192k1 curve
            log2n = 192; 
        }
        else {

            log2n = strtol(argv[2], NULL, 10);;
        }

        FILE *fp;
        long lSize;
        char *buffer;

        fp = fopen ( "../certificates/sample_tbscertificate.txt" , "rb" );
        if( !fp ) perror("../certificates/sample_tbscertificate.txt"),exit(1);

        fseek( fp , 0L , SEEK_END);
        lSize = ftell( fp );
        rewind( fp );

        /* allocate memory for entire content */
        buffer = calloc( 1, lSize+1 );
        if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

        /* copy the file into the buffer */
        if( 1!=fread( buffer , lSize, 1 , fp) )
          fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

        /* do your work here, buffer is a string contains the whole text */

        fclose(fp);
        free(buffer);
        //printf("%s\n", buffer);
        hashMessage(buffer, log2n); 
    
    }   


    return 0;
}