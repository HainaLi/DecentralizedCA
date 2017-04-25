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

  //input curve parameters: secp192k1
  const unsigned char * p_hexstring = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFE\xFF\xFF\xEE\x37"; //{255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,255,255,238,55}; 
  const unsigned char *a_hexstring = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; 
  const unsigned char * b_hexstring = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03";
  const unsigned char *n_hexstring = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFE\x26\xF2\xFC\x17\x0F\x69\x46\x6A\x74\xDE\xFD\x8D";
  const unsigned char *g_x_hexstring = "\xDB\x4F\xF1\x0E\xC0\x57\xE9\xAE\x26\xB0\x7D\x02\x80\xB7\xF4\x34\x1D\xA5\xD1\xB1\xEA\xE0\x6C\x7D";
  const unsigned char *g_y_hexstring = "\x9B\x2F\x2F\x6D\x9C\x56\x28\xA7\x84\x41\x63\xD0\x15\xBE\x86\x34\x40\x82\xAA\x88\xD9\x5E\x2F\x9D";
  const unsigned char *h_hexstring = "\x01";      
  
  const unsigned char *rand_key_0 = "\xeb\xb1\x25\xa0\xcd\x2f\xea\x04\x68\x7f\x5e\x96\xa5\x7d\x60\x05\xb4\xde\x2c\x1d\x88\x51\xb8\x88";
  const unsigned char *rand_key_1 = "\x65\xdd\x53\x5f\x47\x7e\xb8\x83\xd1\x61\xd0\xb9\xbe\x00\x45\xe8\x48\x13\xc6\x6d\x74\x0c\xed\x23";
  const unsigned char *rand_key_2 = "\xf8\x9c\x26\x52\x91\x67\x4f\x65\x6c\x22\x18\x67\x62\x74\xd7\x17\x94\xe9\x5b\xa8\x27\x0b\x2f\xa4";
  const unsigned char *rand_key_3 = "\x9c\xb2\x2f\xa7\xd4\x5c\x9b\x15\xeb\xaf\x26\x76\x58\x75\xa5\x8e\x56\x4b\x7e\x60\x16\xc2\x1d\x2f";
  
  io.private_key_share1 = (char *) malloc(MAXN);
  io.private_key_share2 = (char *) malloc(MAXN);
  io.k1 = (char *) malloc(MAXN);
  io.k2 = (char *) malloc(MAXN);
  io.p = (char *) malloc(MAXN);
  io.g_x = (char *) malloc(MAXN);
  io.g_y = (char *) malloc(MAXN);
  io.n = (char *) malloc(MAXN);
  io.h = (char *) malloc(1);
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
    memcpy(io.private_key_share1, rand_key_0, MAXN); // cryptographically generate this
    memcpy(io.k1, rand_key_1, MAXN);  // cryptographically generate this
  }

  else if (party == 2){
    memcpy(io.private_key_share2, rand_key_2, MAXN); // cryptographically generate this
    memcpy(io.k2, rand_key_3, MAXN);  // cryptographically generate this
  }

  memcpy(io.p, p_hexstring, MAXN);
  memcpy(io.a, a_hexstring, MAXN);
  memcpy(io.b, b_hexstring, MAXN);
  memcpy(io.g_x, g_x_hexstring, MAXN);
  memcpy(io.g_y, g_y_hexstring, MAXN);
  memcpy(io.n, n_hexstring, MAXN);
  memcpy(io.h, h_hexstring, 1);

  start = clock();
  //setCurrentParty(&pd,argv[1][0]=='1'?1:2);
  setCurrentParty(&pd,(remote_host?2:1));
  execYaoProtocol(&pd,signCertificate,&io);
  cleanupProtocol(&pd);
  end = clock();

  //int gates = yaoGateCount();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"\nParty %d, Elapsed Time: %f seconds\n", party, cpu_time_used);
  //fprintf(stderr,"\nNumber of Gates: %u\n", gates);

  //fprintf(stderr,"\nComputation output: %d\n", io.output);
  //fprintf(stderr,"\nPrivate key: %s\n", io.private_key);
  for(int i = 0; i < 5; i++)
    fprintf(stderr,"\noutput: \\x%02x\n", io.output[i]);
  fprintf(stderr, "obig_div_mod(g_x, n)%d\n", io.tempBool);

  /*
  fprintf(stderr, "\tExpected quotient:\t%08X\n\tActual quotient: \t%08X\n", expected_q, io.output_q);

  fprintf(stderr, "\tExpected remainder:\t%08X\n\tActual remainder: \t%08X\n", expected_r, io.output_r);
  */
  

  return 0;
}
