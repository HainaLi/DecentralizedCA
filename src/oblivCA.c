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
  const char *p_hexstring = "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFED";
  const char *a_hexstring = "-01";
  const char *b_hexstring = "-2DFC9311D490018C7338BF8688861767FF8FF5B2BEBE27548A14B235ECA6874A";
  const char *n_hexstring = "0x1000000000000000000000000000000014DEF9DEA2F79CD65812631A5CF5D3ED";
  const char *g_x_hexstring = "0x216936D3CD6E53FEC0A4E231FDD6DC5C692CC7609525A7B2C9562D608F25D51A";
  const char *g_y_hexstring = "6666666666666666666666666666666666666666666666666666666666666658";
  const char *h_hexstring = "08";      
  
  io.private_key_share1 = (char *) malloc(MAXN);
  io.private_key_share2 = (char *) malloc(MAXN);
  io.k1 = (char *) malloc(MAXN);
  io.k2 = (char *) malloc(MAXN);
  io.p = (char *) malloc(MAXN);
  io.g_x = (char *) malloc(MAXN);
  io.g_y = (char *) malloc(MAXN);
  io.n = (char *) malloc(MAXN);
  io.h = (char *) malloc(MAXN);
  io.a = (char *) malloc(MAXN);
  io.b = (char *) malloc(MAXN);

  //protocolUseStdio(&pd);

  if(strcmp(argv[2],"--")==0)
    party = 1;
  else
    party = 2;

  const char* remote_host = (strcmp(argv[2],"--")==0?NULL:argv[2]);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

  if(party == 1){
    memcpy(io.private_key_share1, "abcd", MAXN);
    memcpy(io.k1, "abcdi", MAXN);  // cryptographically generate this
  }

  else if (party == 2){
    memcpy(io.private_key_share2, "2222", MAXN);
    memcpy(io.k2, "49256", MAXN);  // cryptographically generate this
  }

  memcpy(io.p, p_hexstring, MAXN);
  memcpy(io.a, a_hexstring, MAXN);
  memcpy(io.b, b_hexstring, MAXN);
  memcpy(io.g_x, g_x_hexstring, MAXN);
  memcpy(io.g_y, g_y_hexstring, MAXN);
  memcpy(io.n, n_hexstring, MAXN);
  memcpy(io.h, h_hexstring, MAXN);

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

  //fprintf(stderr,"\nComputation output: %d\n", io.output);
  fprintf(stderr,"\nPrivate key: %s\n", io.private_key);
  fprintf(stderr,"\noutput_r: %s\n", io.output_r);
  fprintf(stderr, "obig_div_mod(g_x, n)%d\n", io.tempBool);

  /*
  fprintf(stderr, "\tExpected quotient:\t%08X\n\tActual quotient: \t%08X\n", expected_q, io.output_q);

  fprintf(stderr, "\tExpected remainder:\t%08X\n\tActual remainder: \t%08X\n", expected_r, io.output_r);
  */
  

  return 0;
}
