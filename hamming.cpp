// Create a sorted list of Hamming numbers, i.e. numbers of the form 2^i * 3^j * 5^k,  (i,j,k >= 0)
// Implemented using a Generator Class

#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <climits>

class Hamming {        
    static std::set<unsigned long> hamming_nums;
    static std::set<unsigned long>::size_type largest_index; // largest confirmed pre-calculated index

    std::set<unsigned long>::size_type index = 0;
public:
    Hamming() {}
    unsigned long operator()() {
        // create new numbers and merge
        if(largest_index <= index){
            std::set<unsigned long> new_set;
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](unsigned long i) { return (ULONG_MAX/2 > i ?  2 * i : 1); });
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](unsigned long i) { return (ULONG_MAX/3 > i ?  3 * i : 1); });
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](unsigned long i) { return (ULONG_MAX/5 > i ?  5 * i : 1); });
            unsigned long new_val = *new_set.upper_bound(*hamming_nums.rbegin());
            hamming_nums.insert(new_val);

            ++largest_index;
        }
        std::set<unsigned long>::const_iterator current = std::next(hamming_nums.begin(), index);        
        ++index;
        return *current;
    }
};
std::set<unsigned long> Hamming::hamming_nums = {1};
std::set<unsigned long>::size_type Hamming::largest_index = 0;

int main() {
  std::vector<unsigned long> hammingVec(128);
  std::generate(hammingVec.begin(), hammingVec.end(), Hamming());

  for(const auto& i : hammingVec) {
      std::cout << i << " ";
  }
  std::cout << std::endl;
}
