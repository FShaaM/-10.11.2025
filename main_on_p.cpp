#include <iostream>

struct IntArray
{
	int add(int i);
	int get(size_t id) const;
};

int main()
{
	int next = 0;
	std::cin >> next;

	if (!std::cin)
		return 1;

	IntArray a;

	a.add(next);
}
