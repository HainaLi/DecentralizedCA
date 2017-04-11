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
  
  io.private_key_share1 = (char *) malloc(MAXN);
  io.private_key_share2 = (char *) malloc(MAXN);
 
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

  return 0;
}
