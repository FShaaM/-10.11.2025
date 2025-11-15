#include <iostream>
#include <fstream>
#include <exception>

struct IntArray
{
    int* data;
    size_t size;

    IntArray(int i);
    ~IntArray();
    IntArray(const IntArray& rhs);
    IntArray& operator = (const IntArray& rhs);
    IntArray(IntArray&& rhs);
    IntArray& operator = (IntArray&& rhs);

    void add(int i);
    int get(size_t id) const noexcept;
    size_t getsize() const noexcept;
    int last() const noexcept;
};

struct IntMatrix
{
    IntArray arr = IntArray(0);
    size_t rows = 0;
    size_t cols = 0;

    std::istream& Fill(std::istream& In);
    void Set() const noexcept;
    int Add_Fill_Rows(size_t num, int x);
    int Add_Fill_Cols(size_t num, int x);
};



int main(int argc, const char** argv)
{
    try
    {
        IntMatrix mat;

        if (argc < 2)
        {
            std::cerr << "ERROR: need an argument" << "\n";
            return 1;
        }

        std::ifstream InPut(argv[1]);

        if (!(InPut.is_open()))
        {
            std::cerr << "ERROR: " << argv[1] << " file wasn't opened" << "\n";
            return 1;
        }

        if (!mat.Fill(InPut))
        {
            std::cerr << "ERROR: " << argv[1] << " contains bad elements" << "\n";
            return 1;
        }

        InPut.close();

        size_t FirComm = 0, SecComm = 0;

        int command;
        while (std::cin >> command && !std::cin.eof())
        {
            if (!(std::cin >> FirComm >> SecComm))
            {
                std::cerr << "ERROR: the command parameters must be numbers" << "\n";
                return 3;
            }

            if (command == 1)
            {
                if (mat.Add_Fill_Rows(FirComm, SecComm) == 1)
                    return 3;
            }
            else if (command == 2)
            {
                if (mat.Add_Fill_Cols(FirComm, SecComm) == 1)
                    return 3;
            }
            else if (command == 3)
            {
                if (mat.Add_Fill_Rows(FirComm, 0) == 1)
                    return 3;
                if (mat.Add_Fill_Cols(SecComm, 0) == 1)
                    return 3;
            }
            else
            {
                std::cerr << "EROOR: there is no such command" << "\n";
                return 3;
            }

            mat.Set();
        }

        if (!std::cin && !std::cin.eof())
        {
            std::cerr << "ERROR: the command must be a number" << "\n";
            return 3;
        }
    }
    catch (const std::bad_alloc&)
    {
        return 2;
    }
}

IntArray::IntArray(int i) :
    size(1),
    data(new int[1])
{
    *data = i;
}

IntArray::~IntArray()
{
    delete[] data;
}

IntArray::IntArray(IntArray&& rhs) :
    data(rhs.data),
    size(rhs.size)
{
    rhs.data = nullptr;
}

IntArray& IntArray::operator = (IntArray&& rhs)
{
    delete[] data;
    data = rhs.data;
    size = rhs.getsize();

    rhs.data = nullptr;
    return *this;
}

IntArray::IntArray(const IntArray& rhs) :
    data(new int[rhs.getsize()]),
    size(rhs.getsize())
{
    for (size_t i = 0; i < rhs.getsize(); ++i)
        data[i] = rhs.get(i);
}

int IntArray::get(size_t id) const noexcept
{
    return data[id];
}

size_t IntArray::getsize() const noexcept
{
    return size;
}

int IntArray::last() const noexcept
{
    return get(getsize() - 1);
}

void IntArray::add(int i)
{
    int* dint = new int[getsize() + 1];

    for (size_t k = 0; k < getsize(); ++k)
    {
        dint[k] = get(k);
    }

    dint[getsize()] = i;

    delete[] data;
    data = dint;
    ++size;
}

IntArray& IntArray:: operator = (const IntArray& rhs)
{
    size = rhs.getsize();
    int* p = new int[rhs.getsize()];

    for (size_t i = 0; i < rhs.getsize(); ++i)
        p[i] = rhs.get(i);

    delete[] data;
    data = p;
    size = rhs.getsize();

    return *this;
}

std::istream& IntMatrix::Fill(std::istream& In)
{
    if (!(In >> rows >> cols))
    {
        std::cerr << "ERROR: Bad rows/cols" << "\n";

        rows = 0;
        cols = 0;

        return In;
    }
    else if (rows == 0 || cols == 0)
    {
        std::cerr << "ERROR: Zero matrix dimensions" << "\n";
        return In;
    }

    try
    {
        delete[] arr.data;
        arr.data = new int[rows * cols];
        arr.size = rows * cols;
    }
    catch (const std::bad_alloc&)
    {
        std::cerr << "ERROR: memory allocation error" << "\n";

        arr.data = nullptr;
        arr.size = 0;
        rows = 0;
        cols = 0;

        throw;
    }

    size_t counter = 0;

    for (; counter < arr.size && In >> arr.data[counter]; ++counter);

    if (counter != arr.size)
    {
        std::cerr << "ERROR: matrix reading error, " << counter << " elements were read" << "\n";

        delete[] arr.data;
        arr.data = nullptr;
        arr.size = 0;
        rows = 0;
        cols = 0;
    }

    return In;
}

void IntMatrix::Set() const noexcept
{
    std::cout << "\n";

    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << arr.data[i * cols];
        for (size_t j = 1; j < cols; ++j)
            std::cout << " " << arr.data[i * cols + j];
        std::cout << "\n";
    }

        std::cout << "\n";
}

int IntMatrix::Add_Fill_Rows(size_t num, int x)
{
    if (num > rows)
    {
        std::cerr << "ERROR: there are only " << rows << " rows in the matrix" << "\n";
        return 1;
    }

    int* p = new int[cols * (rows + 1)] {};

    for (size_t k = 0; k < num; ++k)
    {
        for (size_t m = 0; m < cols; ++m)
            p[m + k * cols] = arr.data[m + k * cols];
    }

    for (size_t m = 0; m < cols; ++m)
        p[m + num * cols] = x;

    for (size_t k = num + 1; k < rows + 1; ++k)
    {
        for (size_t m = 0; m < cols; ++m)
            p[m + k * cols] = arr.data[m + (k - 1) * cols];
    }

    delete[] arr.data;
    arr.data = p;
    p = nullptr;
    ++rows;
    arr.size = rows * cols;

    return 0;
}
