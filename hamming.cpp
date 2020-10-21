// Create a sorted list of Hamming numbers, i.e. numbers of the form 2^i * 3^j * 5^k,  (i,j,k >= 0)
// Implemented using a Generator Class
// Note: Requires C++17 
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <climits>

class Hamming {
    typedef unsigned long NumberType;
    typedef std::set<NumberType> NumberSetType;
    static NumberSetType hamming_nums;
    constexpr static NumberType primes[3] = {2,3,5};
    constexpr static size_t num_primes = sizeof(primes)/sizeof(NumberType);

    NumberSetType::size_type index = 0;
public:
    Hamming() {}
    NumberType operator()() {
        while(hamming_nums.size() <= index){ // create new hamming numbers until we have enough
            NumberType vals[num_primes] = {0};
            for(size_t i = 0; i < num_primes; ++i) {
                NumberType p = primes[i];
                NumberType n = *hamming_nums.upper_bound(*hamming_nums.rbegin()/p);
                if(ULONG_MAX/p > n) { // overflow checking
                    vals[i] = p * n;
                }
                // 0 will mark overflowed values
            }

            // custom comparison function, like operator< except 0 is considered infinitely large
            NumberType new_val = *std::min_element(vals, vals+num_primes, [](NumberType i, NumberType j) { return (i == 0 ? false : (j == 0 ? true : i < j)); });
            if(new_val == 0) {
                return 0; // we've reached the largest value achievable with this int type
            }
            hamming_nums.insert(new_val);
        }

        NumberType val = *std::next(hamming_nums.begin(), index);
        ++index;
        return val;
    }
};
Hamming::NumberSetType Hamming::hamming_nums = {1};

int main() {
    std::vector<unsigned long> hammingVec(512);
    std::generate(hammingVec.begin(), hammingVec.end(), Hamming());
  
    for(const auto& i : hammingVec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
