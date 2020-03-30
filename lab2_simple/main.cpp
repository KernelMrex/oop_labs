#include <iostream>
#include <set>
#include <vector>
#include <chrono>
#include <cmath>

std::set<int> GeneratePrimeNumbers(int upperBound);

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    auto primeNumbers = GeneratePrimeNumbers(100000000);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Amount of prime numbers generated: "
              << primeNumbers.size() << std::endl;
    std::cout << "Time spent: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
              << " seconds" << std::endl;
//    std::cout << "Found: ";
//    for (auto i : primeNumbers) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
    return 0;
}

std::set<int> GeneratePrimeNumbers(int upperBound) {
    std::set<int> primeNumbers;
    std::vector<bool> sieve(upperBound, true);

    primeNumbers.insert(2);

    for (int i = 3; i < upperBound - 1; i += 2) {
        if (!sieve[i]) {
            continue;
        }

        if (i < std::sqrt(upperBound - 1)) {
            for (int j = i * i; j < upperBound - 1; j += i) {
                sieve[j] = false;
            }
        }

        primeNumbers.insert(i);
    }

    return primeNumbers;
}
