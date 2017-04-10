#include <stdio.h>
#include <obliv.h>
#include <time.h>
#include "oblivCA.oh"
#include "/home/hannah/Desktop/obliv-c/test/oblivc/common/util.h"


int main(int argc,char *argv[]){
  ProtocolDesc pd;
  protocolIO io;
  clock_t start, end;
  double cpu_time_used;
  
  io.private_key_share1 = (char *) malloc(MAXN);
  io.private_key_share2 = (char *) malloc(MAXN);

  if(argv[1][0] == '1')    
    memcpy(io.private_key_share1, "abcd", MAXN);

  else if (argv[1][0] == '2')    
    memcpy(io.private_key_share2, "2222", MAXN);

  start = clock();
  //protocolUseStdio(&pd);

  const char* remote_host = (strcmp(argv[3],"--")==0?NULL:argv[3]);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);


  setCurrentParty(&pd,argv[1][0]=='1'?1:2);
  execYaoProtocol(&pd,signCertificate,&io);
  cleanupProtocol(&pd);
  end = clock();

  int gates = yaoGateCount();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"\nParty %c, Elapsed Time: %f seconds\n", argv[1][0], cpu_time_used);
  fprintf(stderr,"\nNumber of Gates: %u\n", gates);

  io.private_key[MAXN-1] = '\0'; // temp code for check, shoudl be removed
  fprintf(stderr,"\nCombined Private Key: %s\n", io.private_key);

  return 0;
}