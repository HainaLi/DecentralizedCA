## Welcome to our project on decentralized certificate authority

Our  members are [Bargav Jayaraman](https://github.com/bargavjayaraman) and [Hannah Li](https://github.com/HainaLi/)
## 3/30/2017

## Motivation
Currently, certificate authorities (CAs) store and sign certificates on one machine where the private key could easily be stolen. We propose a new model where multiple machines owned by a CA hold shares to the signing key and jointly sign the certificate so that the compromise of a single party does not enable an attacker to steal an all-powerful private key. 

This model could be later expanded to involve multiple separate CAs. In addition to reaping the benefits of decentralizing the storage of the private key, the division of power could also reduce mistakes commonly made in the certificate approval process. 

## Goal for the Semester
Our goal for the next month is to implement certificate authority (CA) private key generation and certificate signing (via ECDSA) using the two-party computation protocol described in [Yao's Garbled Circuit](http://dl.acm.org/citation.cfm?id=1382944). We assume that the two CA machines hold private key shares, and that they have agreed on a single certificate and set of elliptic curve parameters. The finished MPC implementation should output a signed certificate and the public key without revealing any information about the private key shares. This considers the honest-but-curious model of adversary where the CA machines do not deviate from the protocol.

## Plan

Our plan is to implement the private key generation and certificate signing using the [Obliv-C](https://oblivc.org/) framework which is based on Yao's GC protocol and has the state-of-art efficiency enhancements. Specifically, we will add an ECDSA library to the [Absentminded Crypto Kit](https://bitbucket.org/jackdoerner/absentminded-crypto-kit/overview) project, which already has big integer math and cryptographic hash function features developed.

Generating Standard Elliptic Curve for ECDSA library: (Hannah)
1. [SEC-2](http://www.secg.org/sec2-v2.pdf) recommends a set of standard elliptic curves defined by a sextuple of parameters (p,a,b,G,n,h). Here 'p' specifies the finite field F_p. 'a' and 'b' are the coefficients of the elliptic curve y^2 = x^3 + ax^2 + b. 'G' is the base point or generator of the curve. 'n' is the order of 'G' and 'h' is the cofactor of the sub-group such that n*h gives the number of curve points in the finite field F_p. 
2. The parameters are written in octet-string format and hence are required to be converted to usable format (for example, 'G' has to be represented in a curve point format (x,y)) using the procedure mentioned in [SEC-1](http://www.secg.org/sec1-v2.pdf).
3. Next all the parameters are to be represented in big int format which is compatible with MPC protocol in Obliv-C.

MPC protocol for ECDSA based Certificate Signing: (Bargav)
1. Both CA machines combine their pseudo-random private key shares inside the MPC protocol to obtain the master private key (not revealed to either of the parties) that is used in ECDSA for certificate signing. 
2. Next we perform the certificate signing with the private key and curve parameters obtained above (via steps 1-7 of [Certificate Signing Algorithm](https://en.wikipedia.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm)) inside the MPC protocol.
3. At the end of the protocol, the signed cirtificate and the public key are revealed to both the parties.


### Prior ECDSA Implementations
We have attempted to compile GCC libraries [libgcrypt](https://gnupg.org/software/libgcrypt/index.html), [libgmp](https://gmplib.org/), [openSSL](https://www.openssl.org/) directly with Obliv-C because they offered important big number arithmetic and crypto algorithmic functionalities. After running into compiler compatibility issues, we decided to write our own ECDSA implementation from scratch using important features from the [Absentminded Crypto Kit](https://bitbucket.org/jackdoerner/absentminded-crypto-kit/overview), as described above. 

We will use straightforward ECDSA and ECDH implementations such as [SimpleECDSA](https://github.com/sowbug/SimpleECDSA) and [curve25519](https://github.com/agl/curve25519-donna/) as references. 

## 3/15/2017

## Motivation
Modern Internet users heavily rely on HTTPS to provide a trusted, secure channel to communicate sensitive information. Among the many points of failure possible in the SSL/TLS mechanism, we focus on weaknesses in the certificate generation process. 

In their systematization of knowledge (SoK) paper on summarizing and evaluating current certificate trust model, [Clark and van Oorschot](https://tlseminar.github.io/docs/soktls.pdf) considered attacks on the certificate authority/browser infrastructure where MITM attacks are made possible through compromising a certificate authority.

[Roosa and Schultze](http://ieeexplore.ieee.org/document/6451080/) discussed about various recent high-profile attacks on certificate authorities where the attacker either takes control of the CA or colludes with CA to obtain certificates trusted by a client's browser. The authors particularly note the attacks on two trusted certificate authorities: [Comodo](https://freedom-to-tinker.com/2011/03/23/web-browsers-and-comodo-disclose-successful-certificate-authority-attack-perhaps-iran/) and [DigiNotar](http://freedom-to-tinker.com/2011/09/06/diginotar-hack-highlights-critical-failures-our-ssl-web-security-model/). The attack on Comodo's registration authority (RA) allowed the hacker to get hold of domain validation (DV) certificate of Google. In the case of DigiNotar, the hacker was able to obtain several extended validation (EV) certificates from a subCA of DigiNotar. EV certificates provide access to high security HTTPS websites, and hence their leakage is more serious compared to the leakage of DV certificates.

The above attacks are possible due to single point-of-failure where the certificate generation is carried out by a single CA machine in which case the hacker can either take control of the CA machine or collude with the CA machine to obtain the desired certificates. The same problem persists if the attacker is an authorized personnel within the CA organization and hence may have access to the CA machine. This issue can be resolved by requiring multiple CA machines (possibly geographically separated) to collaboratively generate certificates using secure multi-party computation protocol, thereby effectively removing any single point-of-failure from the certificate generation process. Secure multi-party computation (MPC) ensures that two or more parties can collaboratively compute a functionality without revealing their individual inputs to other parties. In the presence of malicious adversaries which can deviate from the protocol execution, MPC can ensure that the other parties detect the deviation and terminate the computation. This will ensure that the certificate stealing attack will be thwarted even if an adversary captures one of the CA machines.
We propose a decentralized certificate authority consisting of multiple CAs (or multiple CA machines within a CA organization) which provides a security enhancement to the creation of certificates and key signing.


## Plan of Action

[Araki et al.](https://eprint.iacr.org/2016/768.pdf) provided a new, secure three-party computation protocol with an honest majority that will be the basis of our decentralized certificate authority design. Our decentralized certificate authority will use this light-weight protocol to compute certificate generation and signing across multiple parties, delivering guarantees about security and privacy (the protocol reveals nothing but the output so that one party cannot learn about the input of any other parties). 

We will first use one of the available open-source public key infrastructure (PKI) toolkits ([Cloudflare's CFSSL](https://github.com/cloudflare/cfssl) or [OpenSSL](https://github.com/openssl/openssl)) to instantiate our decentralized CA. Next we will use multi-party computation protocol for secure collaborative certificate generation within the decentralized CA. For our multi-party computation, we will utilize the [Obliv-C](http://oblivc.org) framework that includes the latest enhancements of [Zahur et al.](https://eprint.iacr.org/2014/756.pdf) and [Huang et al.](https://www.cs.umd.edu/~jkatz/papers/SP12.pdf) to the garbled circuits of [Yao](http://ieeexplore.ieee.org/document/4568207/). This allows us to ensure privacy even in the presence of malicious adversaries, i.e. when one of the CA machine deviates from the certificate generation protocol.


## Related Works

  Decentralizing or distributing a certificate authority across many nodes is an idea first introduced by [Zhou and Haas](http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=806983) in 1999 when tackling the problem of providing security for ad hoc, mobile networks where hosts relied on each other to keep the network connected. This work proposed spreading the functionality of a single certificate authority to a set of nodes using [Shamir's secret sharing](https://cs.jhu.edu/~sdoshi/crypto/papers/shamirturing.pdf) and treshold cryptography. Later, researchers such as [Dong et al.](http://ac.els-cdn.com/S0140366407001673/1-s2.0-S0140366407001673-main.pdf?_tid=18d2c35e-0811-11e7-8a8e-00000aab0f26&acdnat=1489425698_08801bf940f34f59da45353ffe7cd27d) built upon this idea and provided practical deployment solutions. Though we do not consider mobile ad hoc networks, we attempt to solve the same problem through secure multi-party computation. 


## Resources

[Cloudflare's CFSSL](https://github.com/cloudflare/cfssl): Cloudflare's PKI toolkit to generate certificates and instantiate CA

[OpenSSL](https://github.com/openssl/openssl): OpenSSL toolkit to generate certificates and instantiate CA 

[Obliv-C](http://oblivc.org): Framework based on C for implementing multi-party computation (MPC)
