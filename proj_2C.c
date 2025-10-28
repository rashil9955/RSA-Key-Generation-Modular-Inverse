#include <stdio.h>
#include <stdint.h>



// Check if a number is prime
int isPrime(uint32_t num) {
    if (num < 2) return 0;
    if (num == 2 || num == 3) return 1;
    if (num % 2 == 0) return 0;

    for (uint32_t i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}




//---------------------------------------------
// Function 1: Compute multiplicative inverse
//---------------------------------------------
uint32_t modInverse(uint32_t n, uint32_t totient, uint32_t x) {
    int64_t t = 0, newt = 1;
    int64_t r = totient, newr = x;
    int64_t quotient, temp;

    while (newr != 0) {
        quotient = r / newr;

        temp = t;
        t = newt;
        newt = temp - quotient * newt;

        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }

    // If gcd(x, totient) != 1, no inverse exists
    if (r > 1)
        return (uint32_t)-1;

    // Ensure positive result
    if (t < 0)
        t += totient;

    return (uint32_t)t;
}

//---------------------------------------------
// Helper function: Compute gcd
//---------------------------------------------
uint32_t gcd(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//---------------------------------------------
// Function 2: Ask for p, q → compute e, n, φ(n), d
//---------------------------------------------
void computeInverseFromPrimes() {
    uint32_t p, q, n, totient, e, d;
do {
    printf("Enter prime p: ");
    scanf("%u", &p);
    if (!isPrime(p))
        printf("Error: %u is not a prime number. Try again.\n", p);
} while (!isPrime(p));

do {
    printf("Enter prime q: ");
    scanf("%u", &q);
    if (!isPrime(q))
        printf("Error: %u is not a prime number. Try again.\n", q);
} while (!isPrime(q));


    n = p * q;
    totient = (p - 1) * (q - 1);

    // Select e: relatively prime to p, q, and totient
    for (e = 2; e < totient; e++) {
        if (gcd(e, p) == 1 && gcd(e, q) == 1 && gcd(e, totient) == 1)
            break;
    }

    printf("Selected e = %u (relatively prime to p, q, and φ(n))\n", e);

    // Call Function 1
    d = modInverse(n, totient, e);

    if (d == (uint32_t)-1)
        printf("No multiplicative inverse exists for e = %u mod φ(n) = %u\n", e, totient);
    else {
        printf("\n=== Results ===\n");
        printf("p = %u\n", p);
        printf("q = %u\n", q);
        printf("n = %u\n", n);
        printf("φ(n) = %u\n", totient);
        printf("e = %u\n", e);
        printf("d = %u (multiplicative inverse of e mod φ(n))\n", d);
        printf("================\n");
    }
}

//---------------------------------------------
// Main program
//---------------------------------------------
int main() {
    uint32_t n, totient, x;
    uint32_t inverse;

    printf("\n=== PART 1: Compute Multiplicative Inverse ===\n");
    printf("Enter n: ");
    scanf("%u", &n);

    printf("Enter Totient(n): ");
    scanf("%u", &totient);

    printf("Enter x (less than Totient(n)): ");
    scanf("%u", &x);

    if (x >= totient) {
        printf("Error: x must be less than Totient(n)\n");
        return 1;
    }

    inverse = modInverse(n, totient, x);

    if (inverse == (uint32_t)-1)
        printf("No multiplicative inverse exists for %u mod %u\n", x, totient);
    else
        printf("Multiplicative inverse of %u mod %u is %u\n", x, totient, inverse);

    printf("\n=== PART 2: Compute using p & q ===\n");
    computeInverseFromPrimes();

    return 0;
}
