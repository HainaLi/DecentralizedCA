## Welcome to our project on decentralized certificate authority

Our  members are [Bargav Jayaraman](https://github.com/bargavjayaraman) and [Hannah Li](https://github.com/HainaLi/)

(Add team name)


### Motivation Paragraph

### Plan for the project


### Relevant Sources

1. [High-Throughput Semi-Honest Secure Three-Party Computation with an Honest Majority](https://eprint.iacr.org/2016/768.pdf)

  Araki et al. provides a new, secure three-party computation protocol with an honest majority that will be the basis of our decentralized certificate authority design. Our decentralized certificate authority will use this light-weight protocol to compute certificate generation and signing across multiple parties, delivering guarantees about security and privacy (the protocol reveals nothing but the output so that one party cannot learn about the input of any other parties). 

2. [SoK: SSL and HTTPS: Revisiting past challenges and evaluating certificate trust model enhancements](https://tlseminar.github.io/docs/soktls.pdf)

  In their systematization of knowledge (SoK) paper on summarizing and evaluating current certificate trust model, Clark and van Oorschot considered attacks on the certificate authority/browser infrastructure where MITM attacks are made possible through compromising a certificate authority. A decentralized certificate authority made of several CAs provides a security enhancement to the creation and maintenance of certificates and signing keys. 

3. Related Works

  Decentralizing or distributing a certificate authority across many nodes is an idea first introduced by [Zhou and Haas](http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=806983) in 1999 when tackling the problem of providing security for ad hoc, mobile networks where hosts relied on each other to keep the network connected. This work proposed spreading the functionality of a single certificate authority to a set of nodes using [Shamir's secret sharing](https://cs.jhu.edu/~sdoshi/crypto/papers/shamirturing.pdf) and treshold cryptography. Later, researchers such as [Dong et al.](http://ac.els-cdn.com/S0140366407001673/1-s2.0-S0140366407001673-main.pdf?_tid=18d2c35e-0811-11e7-8a8e-00000aab0f26&acdnat=1489425698_08801bf940f34f59da45353ffe7cd27d)  and [Seno et al.](http://www.sciencedirect.com/science/article/pii/S0140366407001673) built upon this idea and provided practical deployment solutions. Though we do not consider mobile ad hoc networks, we attempt to solve the same problem through secure multi-party computation. 


