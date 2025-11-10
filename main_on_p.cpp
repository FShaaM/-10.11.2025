k#include <iostream>

struct IntArray
{
	IntArray(int i) :
		k(1),
		a(new int[1])
	{
		*a = i;
	}

	~IntArray()
	{
		delete[] a;
	}

	int add(int i);
	int get(size_t id) const noexcept;
	/*int at(size_t id) const;*/
	size_t size() const noexcept;
	int last() const noexcept;

	int* a;
	size_t k;
};

int main()
{
	try
	{
		int next = 0;
		std::cin >> next;

		IntArray a(next);

		while (std::cin >> next)
		{
			a.add(next);
		}

		if (!std::cin && !std::cin.eof())
		{
			return 1;
		}

		size_t count = 1;

		for (size_t i = 0; i < a.size() - 1; ++i)
		{
			int d = a.get(i);

			count += !(d % a.last()) ? 1 : 0;
		}

		std::cout << count << "\n";
	}
	catch (...)
	{
		return 1;
	}
}


int IntArray::get(size_t id) const
{
	return a[id];
}

//int IntArray::at(size_t id) const
//{
//
//}

size_t IntArray::size() const noexcept
{
	return k;
}

int IntArray::last() const noexcept
{
	return get(size() - 1);
}

int IntArray::add(int i)
{
	int* dint = new int[size() + 1];

	for (size_t i = 0; i < size(); ++i)
	{
		dint[i] = get(i);
	}

	delete[] a;
	a = dint;
	++k;
}
