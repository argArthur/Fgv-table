#include <iostream>
#include <bitset>

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

int columnSum(const int state, const int column) 
{
    int m = 1<<(size - 1);
    int selector= 0;
    for (int i = 0; i < size; i++)
        selector = (selector << size) + m;
    
    const int selected = state & (selector >> column);
    return bitCount(selected);
}

bool isValidState(const int state, const bool c) 
{
    bool hasValues[size*2+1];
    if (c) for (int i = 0; i < size*2; i++) std::cout<<hasValues[i]<<' ';
    if (c) std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        if (c) std::cout<< rowSum(state, i) << " r | c " << columnSum(state, i) << '\n';
        hasValues[rowSum(state, i) - 1] = true;
        hasValues[columnSum(state, i) + size - 1] = true;
    }
    
    for (int i = 1; i < size*2; i++)
        if (hasValues[i] != true) return false;
    
    return true;
}

const int testState = 0b1111111110111001100010000;
int main()
{
    int count = 0;
    for (int state = 0; state < (1 << (size*size)) - 1; state++)
    {
        if (isValidState(state, false))
        {
            bool a = isValidState(state, true);
            count++;
            std::cout << "\nfound\n\n";
            std::cout << "is valid: " << a << std::endl;
            // std::cout << std::bitset<32>(state) << '\n';
            a = isValidState(state, true);
            std::cout << "is valid: " << a << std::endl;
            break;
        }
    }
    //std::cout << '\n' << isValidState(0b0001000010000100001000011, false) << '\n';
    std::cout << count << std::endl;
    
    return 0;
}
