#include <stdio.h>
#include <obliv.h>
#include <time.h>
#include "oblivCA.oh"
#include "util.h"


int main(int argc,char *argv[]){
  ProtocolDesc pd;
  protocolIO io;
  clock_t start, end;
  double cpu_time_used;
  int party;

  //input curve parameters
  const char *p_hexstring = "0x7FFFFFFF";
  const char *a_hexstring = "-0x01";
  const char *b_hexstring = "-0x2DFC9311";
  const char *n_hexstring = "0x10000000";
  const char *g_x_hexstring = "0x216936D3";
  const char *g_y_hexstring = "0x66666666";
  const char *h_hexstring = "0x08";
      
  unsigned long long p_long = (long long)strtol(p_hexstring, NULL, 0);
  unsigned long long g_x_long = (long long)strtol(g_x_hexstring, NULL, 0);
  unsigned long long n_long = (long long)strtol(n_hexstring, NULL, 0);
  
  io.private_key_share1 = (char *) malloc(MAXN);
  io.private_key_share2 = (char *) malloc(MAXN);
  io.p = (long long *) malloc(MAXN);
  io.g_x = (long long *) malloc(MAXN);
  io.n = (long long *) malloc(MAXN);

  //protocolUseStdio(&pd);

  if(strcmp(argv[2],"--")==0)
    party = 1;
  else
    party = 2;

  const char* remote_host = (strcmp(argv[2],"--")==0?NULL:argv[2]);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

  if(party == 1)    
    memcpy(io.private_key_share1, "abcd", MAXN);

  else if (party == 2)    
    memcpy(io.private_key_share2, "2222", MAXN);

  memcpy(io.p, p_long, MAXN);
  memcpy(io.g_x, g_x_long, MAXN);
  memcpy(io.n, n_long, MAXN);

  start = clock();
  //setCurrentParty(&pd,argv[1][0]=='1'?1:2);
  setCurrentParty(&pd,(remote_host?2:1));
  execYaoProtocol(&pd,signCertificate,&io);
  cleanupProtocol(&pd);
  end = clock();

//  int gates = yaoGateCount();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"\nParty %d, Elapsed Time: %f seconds\n", party, cpu_time_used);
//  fprintf(stderr,"\nNumber of Gates: %u\n", gates);

  io.private_key[MAXN-1] = '\0'; // temp code for check, shoudl be removed
  fprintf(stderr,"\nCombined Private Key: %s\n", io.private_key);

  /*
  fprintf(stderr, "\tExpected quotient:\t%08X\n\tActual quotient: \t%08X\n", expected_q, io.output_q);

  fprintf(stderr, "\tExpected remainder:\t%08X\n\tActual remainder: \t%08X\n", expected_r, io.output_r);
  */
  

  return 0;
}
