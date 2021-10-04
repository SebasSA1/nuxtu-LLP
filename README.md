# RSA algorithm C++

Implementation of the RSA encryption algorithm (C++11)


The attach files *@Encrypt.cpp* and *@Decrypt.cpp* perform the encryption and decryption process acording to a public key and a local key that enter as parameter

Considering that the prime numbers *p* and *q* that are usually taken are sought to be as large as possible (the algorithm bases its security on computational complexity) an implementation was made using large numbers in c ++. In this case, considering that no type of variable allows to store numbers greater than 10^{100}, this implementation is provided to working with the numbers stored in string forms, in order not to cause or generate problems with the size of the variables and overflows.(and to be able to work with more big  numbers than long double or uint64_t types).


The general idea was based on the book "The large integer case study in c++"
where it is suggested to work with the numbers treating them as strings.
Book of reference https://secure-media.collegeboard.org/apc/ap01.pdf.lr_7928.pdf

![slt-text](https://github.com/SebasSA1/nuxtu-LLP/blob/main/RSA.gif)

The solution presented is in charge of encrypting a message written only in capital letters, based on the criterias given in the following table to encrypt

|Letter | Code |
| ------------- | ------------- |
| A | 1  |
| B | 2  |
| C | 3  |
| D | 4  |
| E | 5  |
| F | 6  |
| G | 7  |
| H | 8  |
| I | 9  |
| J | 10 |
| K | 11 |
| L | 12 |
| M | 13 |
| N | 14 |
| O | 15 |
| P | 16 |
| Q | 17 |
| R | 18 |
| S | 19 |
| T | 20 |
| U | 21 |
| V | 22 |
| W | 23 |
| X | 24 |
| Y | 25 |
| Z | 26 |
| Space | 26 |

