///
/// @file   prev_prime2.cpp
/// @brief  Test primesieve_prev_prime().
///
/// Copyright (C) 2017 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#include <primesieve.h>

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void check(int OK)
{
  if (OK)
    printf("   OK\n");
  else
  {
    printf("   ERROR\n");
    exit(1);
  }
}

int main()
{
  size_t size = 0;
  uint64_t* primes = (uint64_t*) primesieve_generate_primes(0, 100000, &size, UINT64_PRIMES);
  primesieve_iterator it;
  primesieve_init(&it);

  uint64_t i;
  uint64_t prime;
  uint64_t sum = 0;

  for (i = size - 1; i > 0; i--)
  {
    primesieve_skipto(&it, primes[i] + 1, 0);
    prime = primesieve_prev_prime(&it);
    printf("prev_prime(%" PRIu64 ") = %" PRIu64, primes[i] + 1, prime);
    check(prime == primes[i]);

    primesieve_skipto(&it, primes[i], 0);
    prime = primesieve_prev_prime(&it);
    printf("prev_prime(%" PRIu64 ") = %" PRIu64, primes[i], prime);
    check(prime == primes[i - 1]);
  }

  primesieve_skipto(&it, 1000000000, 0);

  // iterate over the primes below 10^9
  while ((prime = primesieve_prev_prime(&it)) > 0)
    sum += prime;

  printf("Sum of the primes below 10^9 = %" PRIu64, sum);
  check(sum == 24739512092254535ull);

  uint64_t p1 = primes[size - 1];
  uint64_t p2 = primes[size - 2];
  primesieve_skipto(&it, p2, p1);
  prime = primesieve_next_prime(&it);
  printf("next_prime(%" PRIu64 ") = %" PRIu64, p2, prime);
  check(prime == p1);

  prime = primesieve_prev_prime(&it);
  printf("prev_prime(%" PRIu64 ") = %" PRIu64, p1, prime);
  check(prime == p2);

  primesieve_skipto(&it, 18446744073709551615ull, 18446744073709551533ull);
  prime = primesieve_prev_prime(&it);
  printf("prev_prime(%" PRIu64 ") = %" PRIu64, 18446744073709551615ull, prime);
  check(prime == 18446744073709551557ull);

  primesieve_free(primes);
  primesieve_free_iterator(&it);

  printf("\n");
  printf("All tests passed successfully!\n");

  return 0;
}
