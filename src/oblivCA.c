#include <obliv.h>
#include "oblivCA.oh"

int main(int argc, char *argv[]) {
  ProtocolDesc pd;     // Protocol Descriptor used for passing message between the parties
  protocolIO io;       // Data structure to store the input parameters
  double start, end;   // Variables to measure start and end time of Wall Clock
  int party;           // CommandLine Argument: 1 -> Generator and 2 -> Evaluator
  
  // Input curve parameters: secp192k1
  uint8_t p_hexstring[MAXN]   = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xEE, 0x37};
  uint8_t a_hexstring[MAXN]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t n_hexstring[MAXN]   = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x26, 0xF2, 0xFC, 0x17, 0x0F, 0x69, 0x46, 0x6A, 0x74, 0xDE, 0xFD, 0x8D};
  uint8_t g_x_hexstring[MAXN] = {0xDB, 0x4F, 0xF1, 0x0E, 0xC0, 0x57, 0xE9, 0xAE, 0x26, 0xB0, 0x7D, 0x02, 0x80, 0xB7, 0xF4, 0x34, 0x1D, 0xA5, 0xD1, 0xB1, 0xEA, 0xE0, 0x6C, 0x7D};
  uint8_t g_y_hexstring[MAXN] = {0x9B, 0x2F, 0x2F, 0x6D, 0x9C, 0x56, 0x28, 0xA7, 0x84, 0x41, 0x63, 0xD0, 0x15, 0xBE, 0x86, 0x34, 0x40, 0x82, 0xAA, 0x88, 0xD9, 0x5E, 0x2F, 0x9D};

  uint8_t rand_key_0[MAXN]    = {0xeb, 0xb1, 0x25, 0xa0, 0xcd, 0x2f, 0xea, 0x04, 0x68, 0x7f, 0x5e, 0x96, 0xa5, 0x7d, 0x60, 0x05, 0xb4, 0xde, 0x2c, 0x1d, 0x88, 0x51, 0xb8, 0x88};
  uint8_t rand_key_1[MAXN]    = {0x65, 0xdd, 0x53, 0x5f, 0x47, 0x7e, 0xb8, 0x83, 0xd1, 0x61, 0xd0, 0xb9, 0xbe, 0x00, 0x45, 0xe8, 0x48, 0x13, 0xc6, 0x6d, 0x74, 0x0c, 0xed, 0x23};
  uint8_t rand_key_2[MAXN]    = {0xf8, 0x9c, 0x26, 0x52, 0x91, 0x67, 0x4f, 0x65, 0x6c, 0x22, 0x18, 0x67, 0x62, 0x74, 0xd7, 0x17, 0x94, 0xe9, 0x5b, 0xa8, 0x27, 0x0b, 0x2f, 0xa4};
  uint8_t rand_key_3[MAXN]    = {0x9c, 0xb2, 0x2f, 0xa7, 0xd4, 0x5c, 0x9b, 0x15, 0xeb, 0xaf, 0x26, 0x76, 0x58, 0x75, 0xa5, 0x8e, 0x56, 0x4b, 0x7e, 0x60, 0x16, 0xc2, 0x1d, 0x2f};
  // Read key1 and key3 from file
  //char * rand_key_1 = read_hex_file("rand_key0.txt"); 
  //char * rand_key_3 = read_hex_file("rand_key1.txt"); 

  // This is the 'e' (hashed value of a template TBSCertificate (to be signed)) 
  uint8_t e_hexstring[MAXN]   = {0x0d, 0x80, 0xb4, 0x91, 0x9e, 0x2e, 0xdb, 0x5e, 0x1b, 0xa3, 0xe6, 0x19, 0xe8, 0xb6, 0x0b, 0xfa, 0xd2, 0x5d, 0x16, 0xc4, 0xde, 0xec, 0x05, 0xa7};  
  
  
  if (strcmp(argv[2], "--") == 0) {
    party = 1;
  } else {
    party = 2;
  }
  
  setCurrentParty(&pd, party);

  const char* remote_host = (strcmp(argv[2], "--") == 0 ? NULL : argv[2]);
  ocTestUtilTcpOrDie(&pd, remote_host, argv[1]);

  if (strcmp(argv[3], "yao") == 0) {
    io.proto = 1;
  } else if (strcmp(argv[3], "dualex") == 0) {
    io.proto = 2;
  } else {
    io.proto = 0;
  }

  if (strcmp(argv[4], "genPubKey") == 0) {
    io.operation = 1;
  } else if (strcmp(argv[4], "signCert") == 0) {
    io.operation = 2;
  } else {
    io.operation = 0;
  }

  // Load Curve Parameters
  memcpy(io.p, p_hexstring, MAXN);
  memcpy(io.a, a_hexstring, MAXN);
  memcpy(io.g_x, g_x_hexstring, MAXN);
  memcpy(io.g_y, g_y_hexstring, MAXN);
  memcpy(io.n, n_hexstring, MAXN);


  if (io.operation == 1) { // Execute Protocol to Generate Public Key

    if (party == 1) {
      memcpy(io.private_key_share1, rand_key_0, MAXN); // cryptographically generate this
    } else {
      memcpy(io.private_key_share2, rand_key_2, MAXN); // cryptographically generate this
    }

    start = wallClock();

    if (io.proto == 1) {
      execYaoProtocol(&pd, generatePublicKey, &io);
    } else {
      execDualexProtocol(&pd, generatePublicKey, &io);
    }

    end = wallClock();

    fprintf(stderr, "\nParty %d, Elapsed Time: %f seconds, \n", party, end - start);

    if (party == 1) {
      fprintf(stderr, "\nQ_x is :\n");
      for (int i = 0; i < MAXN; i++) {
        fprintf(stderr,"0x%02hhX ", io.Q_x[MAXN - 1 - i]);
      }
      fprintf(stderr, "\nQ_y is :\n");
      for (int i = 0; i < MAXN; i++) {
        fprintf(stderr,"0x%02hhX ", io.Q_y[MAXN - 1 - i]);
      }
    }
  } else { // Execute Protocol to Sign Certificate

    if (party == 1) {
      memcpy(io.private_key_share1, rand_key_0, MAXN); // cryptographically generate this
      memcpy(io.k1, rand_key_1, MAXN);  // cryptographically generate this
      memcpy(io.e1, e_hexstring, E_LENGTH);
    } else {
      memcpy(io.private_key_share2, rand_key_2, MAXN); // cryptographically generate this
      memcpy(io.k2, rand_key_3, MAXN);  // cryptographically generate this
      memcpy(io.e2, e_hexstring, E_LENGTH);
    }

    start = wallClock();

    if (io.proto == 1) {
      execYaoProtocol(&pd, signCertificate, &io);
    } else {
      execDualexProtocol(&pd, signCertificate, &io);
    }

    end = wallClock();

    fprintf(stderr, "\nParty %d, Elapsed Time: %f seconds, \n", party, end - start);

    if (io.RisZero) {
      fprintf(stderr, "\nError: 'r' is zero, Please retry with different 'k'\n");
    }

    if (io.SisZero) {
      fprintf(stderr, "\nError: 's' is zero, Please retry with different 'k'\n");
    }

    if (party == 1) {
      fprintf(stderr, "\nr is :\n");
      for (int i = 0; i < MAXN; i++) {
        fprintf(stderr,"0x%02hhX ", io.r[MAXN - 1 - i]);
      }
      fprintf(stderr, "\ns is :\n");
      for (int i = 0; i < MAXN; i++) {
        fprintf(stderr,"0x%02hhX ", io.s[MAXN - 1 - i]);
      }
    }
  }

  cleanupProtocol(&pd);

  return 0;
}
