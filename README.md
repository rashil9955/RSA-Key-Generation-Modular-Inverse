
# Project 2C – RSA Key Generation & Modular Inverse

## Description
This project generates RSA public and private keys by calculating the **multiplicative inverse** of *e mod φ(n)* using the **Extended Euclidean Algorithm**.  
It ensures that *e* is relatively prime to *φ(n)* and computes *d = e⁻¹ mod φ(n)* for decryption.

## Features
- Validates user input primes *p* and *q*  
- Automatically computes:
  - *n = p × q*  
  - *φ(n) = (p - 1)(q - 1)*  
- Selects an encryption exponent *e* that is relatively prime to *φ(n)*  
- Computes private key *d* as modular inverse of *e mod φ(n)*

## Usage
```bash
make
./rsa_keygen
