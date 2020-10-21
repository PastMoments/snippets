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
    typedef std::vector<NumberType> NumberSetType;
    static NumberSetType hamming_nums;

    NumberSetType::size_type index = 0;
public:
    Hamming() {}
    NumberType operator()() {
        // create new numbers and merge
        if(hamming_nums.size() <= index){
            NumberSetType new_set;
	    new_set.reserve(hamming_nums.size()*3);
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::back_inserter(new_set), [](NumberType i) { return (ULONG_MAX/2 > i ?  2 * i : 1); });
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::back_inserter(new_set), [](NumberType i) { return (ULONG_MAX/3 > i ?  3 * i : 1); });
            std::transform(hamming_nums.begin(), hamming_nums.end(), std::back_inserter(new_set), [](NumberType i) { return (ULONG_MAX/5 > i ?  5 * i : 1); });
	    std::sort(new_set.begin(), new_set.end());

	    for(NumberType& new_num: new_set) {
                if(new_num > *hamming_nums.rbegin()){
                    hamming_nums.push_back(new_num);
		    break;
		}
	    }
        }
	NumberType val = hamming_nums[index];
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
