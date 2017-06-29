# Decentralized Certificate Authority

A _decentralized certificate authority_ splits a CA's private signing key among two parties, eliminating the central trust in a single CA. It can also be used to enable certificates that are signed by a joint key split between a subject and CA.

For details, see:

> Bargav Jayaraman, Hannah Li, David Evans. [_Decentralized Certificate Authorities_(PDF)](https://oblivc.org/docs/dca.pdf) 
([arxiv 1706.03370](https://arxiv.org/abs/1706.03370)).

**Disclaimer.** This is a research prototype, developed for exploring and idea and feasibility testing. You should not run an actual certificate authority using this code.

## Prerequisites

 - Obliv-C (https://github.com/samee/obliv-c)
 - Absentminded Crypto Kit (https://bitbucket.org/jackdoerner/absentminded-crypto-kit/src)
 - MP Bignum Library (https://gmplib.org/)

## Running DCA

To run the code:
- Go to DecentralizedCA/src
- run `make` //This will generate two executables: a.out and setup.out
- To run on local machine: run `./a.out [port-number] -- [proto] [operation] & ./a.out [port-number] localhost [proto] [operation]`
- To run on separate machines: run `./a.out [port-number] -- [proto] [operation]` on server machine and run `./a.out [port-number] [remote-host] [proto] [operation]` on client machine
- proto defines the protocol to be executed - Yao or DualEx. The options of proto are 'yao' and 'dualex'
- operation defines the ECDSA operation to bed executed - Public Key Generation or Certificate Signing. The options of operation are 'genPubKey' and 'signCert'
- Warning: Both the parties should use the exact same values of proto and operation, else the code will fail!

For now, the code uses secp192k1 curve, and this could be easily extended to any standard Elliptic Curve. The code will output the ECDSA public key pair (Q_x, Q_y) in case of 'genPubKey', and ECDSA signature pair (r,s) in case of 'signCert'.

---

The current oblivCA.c contains hard coded values for the sec192k1 curve, pks A and B, ks A and B, and the hash of the to-be-signed certificate. 

To sign a different string/certificate, or to generate new values for k and pk:

   ./setup.out generateBigNums p log2n  
 or   
   ./setup.out hashMessage log2n   

Or omit the p or log2n to use the default secp192k1 curve.   
The log2n is the number of bits of your curve.   
For example, for the default secp192k1 curve, log2n=192  

The generated random big numbers and hashed message will be printed to console, where you can copy/paste into oblivCA.c.   
Note: a.out and setup.out are compiled as separately because libgmp does not compile with oblivC.   
