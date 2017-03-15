## Welcome to our project on decentralized certificate authority

Our  members are [Bargav Jayaraman](https://github.com/bargavjayaraman) and [Hannah Li](https://github.com/HainaLi/)


### Motivation

[Roosa and Schultze](http://ieeexplore.ieee.org/document/6451080/) discuss about various recent high-profile attacks on certificate authorities where the attacker either takes control of the CA or colludes with CA to obtain certificates trusted by a client's browser. The authors particularly note the attacks on two trusted certificate authorities: [Comodo](https://freedom-to-tinker.com/2011/03/23/web-browsers-and-comodo-disclose-successful-certificate-authority-attack-perhaps-iran/) and [DigiNotar](http://freedom-to-tinker.com/2011/09/06/diginotar-hack-highlights-critical-failures-our-ssl-web-security-model/). The attack on Comodo's registration authority (RA) allowed the hacker to get hold of domain validation (DV) certificate of Google. In the case of DigiNotar, the hacker was able to obtain several extended validation (EV) certificates from a subCA of DigiNotar. EV certificates provide access to high security HTTPS websites, and hence their leakage is more serious compared to the leakage of DV certificates.

The above attacks are possible due to single point-of-failure where the certificate generation is carried out by a single CA machine in which case the hacker can either take control of the CA machine or collude with the CA machine to obtain the desired certificates. The same problem persists if the attacker is an authorized personnel within the CA organization and hence may have access to the CA machine. This issue can be resolved by requiring multiple CA machines (possibly geographically separated) to collaboratively generate certificates, thereby effectively removing any single point-of-failure from the certificate generation process. This will ensure that the certificate stealing attack will be thwarted even if an adversary captures one of the CA machines.
We propose a decentralized certificate authority consisting of multiple CAs (or multiple CA machines within a CA organization) which provides a security enhancement to the creation of certificates and key signing.


### Plan of Action

We will use [Cloudflare's CFSSL](https://github.com/cloudflare/cfssl) open-source public key infrastructure (PKI) toolkit to instantiate our decentralized CA and use multi-party computation protocol for collaborative certificate generation within the decentralized CA. For our multi-party computation, we will utilize the [Obliv-C](http://oblivc.org) framework that includes the latest enhancements of [Zahur et al.](https://eprint.iacr.org/2014/756.pdf) and [huang et al.](https://www.cs.umd.edu/~jkatz/papers/SP12.pdf) to the [garbled circuits](http://ieeexplore.ieee.org/document/4568207/). This allows us to ensure privacy in the presence of malicious adversaries, i.e. when one of the CA machine deviates from the certificate generation protocol.


### Relevant Sources

1. [High-Throughput Semi-Honest Secure Three-Party Computation with an Honest Majority](https://eprint.iacr.org/2016/768.pdf)

  [Araki et al.](https://eprint.iacr.org/2016/768.pdf) provide a new, secure three-party computation protocol with an honest majority that will be the basis of our decentralized certificate authority design. Our decentralized certificate authority will use this light-weight protocol to compute certificate generation and signing across multiple parties, delivering guarantees about security and privacy (the protocol reveals nothing but the output so that one party cannot learn about the input of any other parties). 

2. [SoK: SSL and HTTPS: Revisiting past challenges and evaluating certificate trust model enhancements](https://tlseminar.github.io/docs/soktls.pdf)

  In their systematization of knowledge (SoK) paper on summarizing and evaluating current certificate trust model, Clark and van Oorschot considered attacks on the certificate authority/browser infrastructure where MITM attacks are made possible through compromising a certificate authority. A decentralized certificate authority made of several CAs provides a security enhancement to the creation and maintenance of certificates and signing keys. 

3. Related Works

  Decentralizing or distributing a certificate authority across many nodes is an idea first introduced by [Zhou and Haas](http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=806983) in 1999 when tackling the problem of providing security for ad hoc, mobile networks where hosts relied on each other to keep the network connected. This work proposed spreading the functionality of a single certificate authority to a set of nodes using [Shamir's secret sharing](https://cs.jhu.edu/~sdoshi/crypto/papers/shamirturing.pdf) and treshold cryptography. Later, researchers such as [Dong et al.](http://ac.els-cdn.com/S0140366407001673/1-s2.0-S0140366407001673-main.pdf?_tid=18d2c35e-0811-11e7-8a8e-00000aab0f26&acdnat=1489425698_08801bf940f34f59da45353ffe7cd27d)  and [Seno et al.](http://www.sciencedirect.com/science/article/pii/S0140366407001673) built upon this idea and provided practical deployment solutions. Though we do not consider mobile ad hoc networks, we attempt to solve the same problem through secure multi-party computation. 


