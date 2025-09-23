#include <stdio.h>
int absVal(int x)
{
    return ((x >> 31) ^ x) - (x >> 31);
}
int absVal_standard(int x)
{
    return x < 0 ? -x : x;
}
int negate(int x)
{
    return ~x + 1;
}
int negate_standard(int x)
{
    return -x;
}
int bitAnd(int x, int y)
{
    return ~(~x | ~y);
}
int bitAnd_standard(int x, int y)
{
    return x & y;
}
int bitOr(int x, int y)
{
    return ~(~x & ~y);
}
int bitXor(int x, int y)
{
    return ~(~(x & ~y)) & (~((~x) & y));
}
int bitXor_standard(int x, int y)
{
    return x ^ y;
}
int isTmax(int x)
{
    return !(x ^ (~(1 << 31)));
}
int isTmax_standard(int x)
{
    return x == 0x7ffffff;
}
int bitCount(int x)
{
    int mask1 = 0x55555555;
    x = (x & mask1) + ((x >> 1) & mask1);
    int mask2 = 0x33333333;
    x = (x & mask2) + ((x >> 2) & mask2);
    int mask3 = 0x0f0f0f0f;
    x = (x & mask3) + ((x >> 4) & mask3);
    int mask4 = 0x00ff00ff;
    x = (x & mask4) + ((x >> 8) & mask4);
    int mask5 = 0x0000ffff;
    x = (x & mask5) + ((x >> 16) & mask5);
    return x;
}
int bitCount_standard(int x){
    return __builtin_pop_count(x);
}
int bitMask(int highbit, int lowbit)
{
    return 1 << 31 >> (highbit - 1) ^ (1 << 31 >> (lowbit - 1));
}
int bitMask_standard(int highbit,int lowbit){
    int x = 0;
    for (int i = lowbit; i <= highbit; i++)
    {
        x = x | 0x80000000 >> (lowbit-1);
    }
    return x;
}
int addOK(int x, int y)
{
    return !!((x + y) >> 31 ^ (x >> 31)) & ((x + y) >> 31 ^ (y >> 31));
}
int addOK_standard(int x, int y)
{
    return x * y > 0 && (x + y) * x < 0;
}
int byteswap(int x, int n, int m)
{
    int mask = 0x000000ff;
    int nmask = x & (mask << (n << 3));
    int mmask = x & (mask << (m << 3));
    return x ^ nmask ^ mmask | (nmask >> (n << 3) & mask << (m << 3)) | mmask >> (m << 3) & mask << (n << 3);
}
int bang(int x)
{
    return (x >> 31 | (~x + 1) >> 31) + 1;
}
int bang_standard(int x)
{
    return x == 0;
}
int bitParity(int x)
{
    int x1 = x << 16 ^ x;
    int x2 = x1 << 8 ^ x1;
    int x3 = x2 << 4 ^ x2;
    int x4 = x3 << 2 ^ x3;
    int x5 = x4 << 1 ^ x4;
    return !!(x5 >> 31);
}
int bitParity(int x){
    int cnt = 0;
    for (int i = 0; i < 32;i++){
        if(x&1){
            cnt++;
        }
        x >>= 1;
    }
    return cnt % 2;
}
int main()
{
    printf("%d\n", bitParity(4));
    return 0;
}