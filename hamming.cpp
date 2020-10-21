// Create a sorted list of Hamming numbers, i.e. numbers of the form 2^i * 3^j * 5^k,  (i,j,k >= 0)
// Implemented using a Generator Class

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

    NumberSetType::size_type index = 0;
public:
    Hamming() {}
    NumberType operator()() {
        // create new numbers and merge
        if(hamming_nums.size() <= index){
            NumberSetType new_set;
            std::transform(hamming_nums.upper_bound(*hamming_nums.rbegin()/2), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](NumberType i) { return (ULONG_MAX/2 > i ?  2 * i : 1); });
            std::transform(hamming_nums.upper_bound(*hamming_nums.rbegin()/3), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](NumberType i) { return (ULONG_MAX/3 > i ?  3 * i : 1); });
            std::transform(hamming_nums.upper_bound(*hamming_nums.rbegin()/5), hamming_nums.end(), std::inserter(new_set, new_set.end()), [](NumberType i) { return (ULONG_MAX/5 > i ?  5 * i : 1); });
            NumberType new_val = *new_set.upper_bound(*hamming_nums.rbegin());
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
