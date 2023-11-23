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



In my implementation, I used the following notational convention :

• Every field element is 330 bits binary string out of which 329 bits
correspond to the value and the leftmost bit of the string stands for the sign
bit. I represent a 330 bits long binary string in a number of base two power
thirty. To represent this number I used a long integer array of size eleven.

• Used G, a, b, p, n are same as given in the P-256 curve.



To run the code, run the commands on terminal: 
'''
gcc ECDH2102.c -o ECDH && ./ECDH
'''

