# ECDH
Implementation Of Elliptic- curve Diffie–Hellman Key Exchange Protocol

In the implementation of the Elliptic-curve Diffie–Hellman Key Exchange
Protocol my code structure is as follows :

• To generate the key in one end the first party generates a 330-bit long
binary string such that it's less than n, I convert this string to a number of
base two power thirty, suppose the number is A. Now I add G, A times
following the elliptic curve group law. This is shared of the Frist party in
the public channel.

• In a similar fashion second party also generates a 330-bit long binary string
such that it's less than n, I convert this string also to a number of base two
power thirty, suppose the number is B. Now I add G, B times following the
elliptic curve group law. This is shared of the second party in the channel.

• After obtaining the share of the second party, that is BG, the first party adds
BG, A times following the elliptic curve group law and obtains ABG.

• In a similar way the second party computes BAG.

• Then my code printed both ABG and BAG, and I saw both the number are
the same, which is the final key obtained from the ECDH algorithm.

• I assumed AB is less than n.



To run the code, run the commands on terminal: gcc ECDH2102.c ./a.out
