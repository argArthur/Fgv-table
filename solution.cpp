#include <iostream>

int size = 5;

int bitCount(unsigned int u)
{
    unsigned int uCount;

    uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
    return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}

int rowSum(const int state, const int row)
{
    const int selected = (state >> (size * row)) & ((1<<size) - 1);
    return bitCount(selected);
}

int selector;
int columnSum(const int state, const int column)
{
    const int selected = state & (selector >> column);
    return bitCount(selected);
}

int indexOf(int* array, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == element) return i;
    }
    
    return -1;
}

bool isValidState(const int state)
{
    bool hasValues[size*2];
    for (int i = 0; i < size*2; i++) hasValues[i] = false;
    for (int i = 0; i < size; i++)
    {
        const int row = rowSum(state, i);
        if (row == 0) return false; // prevent out of index
        if (hasValues[row - 1] == true) return false;
        hasValues[row - 1] = true;
        
        const int column = columnSum(state, i);
        if (column == 0) return false; // prevent out of index
        if (hasValues[column + size - 1] == true) return false;
        hasValues[column + size - 1] = true;
    }

    return true;
}


int main()
{
    clock_t start, end;

    start = clock();

    int m = 1<<(size - 1);
    selector= 0;
    for (int i = 0; i < size; i++)
        selector = (selector << size) + m;
        
    int count = 0;
    for (int state = 0; state < (1 << (size*size)) - 1; state++)
    {
        if (isValidState(state))
        {
            count++;
        }
    }

    end = clock();
    double elapsed = (double(end) - double(start))/CLOCKS_PER_SEC;
    
    std::cout << count << '\n';
    std::cout << "time: " << elapsed << " seconds" << std::endl;

    return 0;
}
