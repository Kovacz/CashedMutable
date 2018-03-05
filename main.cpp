#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <chrono>

const unsigned N = 10000;
std::mt19937 gen { std::random_device()() };
std::uniform_int_distribution<int> uid(1000, N);

class CFoo
{
public:
	typedef unsigned u;
	CFoo() : data(nullptr), cashed_value(0), cashed(false) 
	{
		this->data = new int[N];
		std::generate(this->data, this->data + N, []() -> int { return uid(gen); });
	}
	CFoo(const CFoo &other)
	{
		
	}
	~CFoo() 
	{
		delete[] data;
	}
	void show_data() 
	{
		for (u i = 0; i < N; ++i) {
			std::cout << this->data[i] << " ";
		}
	}
	int get_cashed_value() const
	{
		return this->cashed_value;
	}
	int calculate() const
	{
		long long sum = 0;
		std::chrono::high_resolution_clock::time_point begin, end;
		if (this->cashed) {
			return this->cashed_value;
		}
		begin = std::chrono::high_resolution_clock::now();
		std::sort(data, data + N, [](const int a, const int b) -> int { return a > b; });
		for (u i = 0; i < N; ++i) {
			sum += data[i];
		}
		end = std::chrono::high_resolution_clock::now();
		cashed_value = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		cashed = true;
	}
private:
	int		*data;
	mutable double	cashed_value;
	mutable bool	cashed;
};

int main()
{
	CFoo cfoo;
	cfoo.calculate();
	cfoo.show_data();
	std::cout << "\n\nCached data time of the function: " << cfoo.get_cashed_value() << "us.\n\n";
	system("pause");
}
