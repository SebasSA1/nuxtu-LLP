# RSA algorithm C++

Implementation of the RSA encryption algorithm (C++11)


The attach files *@Encrypt.cpp* and *@Decrypt.cpp* perform the encryption and decryption process acording to a public key and a local key that enter as parameter

Considering that the prime numbers *p* and *q* that are usually taken are sought to be as large as possible (the algorithm bases its security on computational complexity) an implementation was made using large numbers in c ++. In this case, considering that no type of variable allows to store numbers greater than 10^{100}, an implementation is provided working with the numbers stored in string forms, in order not to cause or generate problems with the size of the variables (and to be able to work with more big  numbers than long double or uint64_t types).


The general idea was based on the book "The large integer case study in c++"
where it is suggested to work with the numbers treating them as strings.
Book of reference https://secure-media.collegeboard.org/apc/ap01.pdf.lr_7928.pdf

![slt-text](https://github.com/SebasSA1/nuxtu-LLP/blob/main/RSA.gif)

The solution presented is in charge of encrypting a message written only in capital letters, based on the criterias given in the following table to encrypt

|Letter | Code |
| ------------- | ------------- |
| Contenido de la celda  | Contenido de la celda  |
| Contenido de la celda  | Contenido de la celda  |
