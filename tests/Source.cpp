#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <type_traits>
#include <vector>

template < typename T >
std::vector< T > make_random_vector(size_t size, T min_value, T max_value) {
	static_assert(std::is_arithmetic_v< T >, "T must be an arithmetic type");

	std::mt19937     prng{std::random_device{}()};
	std::vector< T > ret_v;
	ret_v.reserve(size);
	auto bi = std::back_inserter(ret_v);

	using dist_t = std::conditional_t< std::is_integral_v< T >,
		std::uniform_int_distribution< T >,
		std::uniform_real_distribution< T > >;

	dist_t dist{min_value, max_value};
	std::generate_n(bi, size, [&]() { return dist(prng); });

	return ret_v;
}

void print_vector(std::vector< int > wektor) {
	for(const int i : wektor)
		std::cout << i << " ";
	std::cout << std::endl;
}

bool czyWieksze(int i, int j) {
	return (i > j);
}

bool czyWiekszeOdSiedem(int i) {
	return (i > 7);
}

class czyWiekszeOda {
	public:
	czyWiekszeOda(int a_): a{a_} {}
	int  a;
	bool operator()(int i) { return (i > a); }
};

/* Æwiczenie I */

bool areBoolsEqual(char a, char b) {
	return (a == b);
}

bool areTwoCharsInaRow() {
	std::string s;
	std::cout << "Podaj zmienna typu string" << std::endl;
	std::cin >> s;
	std::string::iterator it = std::adjacent_find(s.begin(), s.end());
	if(it == s.end())
		return false;
	else {
		std::cout << "Znaleziono powtorzenie litery " << (*it) << std::endl;
		return true;
	}
}

int main() {
	if(areTwoCharsInaRow())
		std::cout << "Para znaleziona" << std::endl;
	else
		std::cout << "Para nie zostala znaleziona" << std::endl;
}

/* Po uruchomieniu otrzymano:
  Podaj zmienna typu string
  Football
  Znaleziono powtorzenie litery o
  Para znaleziona
*/