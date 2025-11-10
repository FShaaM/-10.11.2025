#include <iostream>

struct IntArray
{
	int add(int i);
	int get(size_t id) const;
	size_t size() const;
};

int main()
{
	int next = 0;
	std::cin >> next;

	if (!std::cin)
		return 1;

	IntArray a;

	a.add(next);

	//ввод

	for (size_t i = 0; i < a.size(); ++i)
	{
		int d = a.get(i);
		//
	}
}
