#include<obliv.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"util.h"

double wallClock()
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  return t.tv_sec+1e-9*t.tv_nsec;
}

void ocTestUtilTcpOrDie(ProtocolDesc* pd,const char* remote_host,
                        const char* port)
{
  if(!remote_host)
  { if(protocolAcceptTcp2P(pd,port)!=0)
    { fprintf(stderr,"TCP accept failed\n");
      exit(1);
    }
  }
  else 
    if(protocolConnectTcp2P(pd,remote_host,port)!=0) 
    { fprintf(stderr,"TCP connect failed\n");
      exit(1);
    }
}

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

