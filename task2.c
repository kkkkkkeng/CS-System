#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    return ~(~(x & ~y) & (~((~x) & y)));
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
    return x == 0x7fffffff;
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
int bitCount_standard(int x)
{
    return __builtin_popcount(x);
}
int bitMask(int highbit, int lowbit)
{
    return (~0) << (highbit + 1) ^ (~0) << (lowbit);
}
int bitMask_standard(int highbit, int lowbit)
{
    int x = 0;
    for (int i = lowbit; i <= highbit; i++)
    {
        x = x | (1 << i);
    }
    return x;
}
int addOK(int x, int y)
{
    return !!((x + y) >> 31 ^ (x >> 31)) & ((x + y) >> 31 ^ (y >> 31));
}
int addOK_standard(int x, int y)
{
    return ((x > 0 && y > 0) || (x < 0) && (y < 0)) && ((x + y) > 0 && x < 0 || (x + y) < 0 && x > 0);
}
int byteswap(int x, int n, int m)
{
    int mask = 0x000000ff;
    int nmask = x & (mask << (n << 3));
    int mmask = x & (mask << (m << 3));
    return (x ^ nmask ^ mmask) | ((nmask >> (n << 3) & mask) << (m << 3)) | ((mmask >> (m << 3) & mask) << (n << 3));
}
int byteswap_standard(int x, int n, int m)
{
    unsigned char *p = &x;
    unsigned char temp = *(p + n);
    *(p + n) = *(p + m);
    *(p + m) = temp;
    return x;
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
int bitParity_standard(int x)
{
    int cnt = 0;
    for (int i = 0; i < 32; i++)
    {
        if (x & 1)
        {
            cnt++;
        }
        x >>= 1;
    }
    return cnt % 2;
}
int randint()
{
    return rand() | (rand() << 16);
}
int main()
{
    srand((unsigned)time(NULL));
    char op;
    while (1)
    {
        printf("Enter operation (a: absVal, n: negate, A: bitAnd, O: bitOr, X: bitXor, T: isTmax, C: bitCount, M: bitMask, K: addOK, B: byteswap, g: bang, P: bitParity, R:random test q: quit): ");
        scanf("%c", &op);
        if (op == 'q')
        {
            break;
        }
        int x, y, n, m;
        switch (op)
        {
        case 'a':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom absVal: %d\n", absVal(x));
            printf("Standard absVal: %d\n", absVal_standard(x));
            break;
        case 'n':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom negate: %d\n", negate(x));
            printf("Standard negate: %d\n", negate_standard(x));
            break;
        case 'A':
            printf("Enter two integers: ");
            scanf("%d %d", &x, &y);
            printf("Custom bitAnd: %d\n", bitAnd(x, y));
            printf("Standard bitAnd: %d\n", bitAnd_standard(x, y));
            break;
        case 'O':
            printf("Enter two integers: ");
            scanf("%d %d", &x, &y);
            printf("Custom bitOr: %d\n", bitOr(x, y));
            printf("Standard bitOr: %d\n", x | y);
            break;
        case 'X':
            printf("Enter two integers: ");
            scanf("%d %d", &x, &y);
            printf("Custom bitXor: %d\n", bitXor(x, y));

            printf("Standard bitXor: %d\n", bitXor_standard(x, y));
            break;
        case 'T':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom isTmax: %d\n", isTmax(x));
            printf("Standard isTmax: %d\n", isTmax_standard(x));
            break;
        case 'C':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom bitCount: %d\n", bitCount(x));
            printf("Standard bitCount: %d\n", bitCount_standard(x));
            break;
        case 'M':
            printf("Enter two integers (highbit and lowbit): ");
            scanf("%d %d", &x, &y);
            printf("Custom bitMask: %d\n", bitMask(x, y));
            printf("Standard bitMask: %d\n", bitMask_standard(x, y));
            break;
        case 'K':
            printf("Enter two integers: ");
            scanf("%d %d", &x, &y);
            printf("Custom addOK: %d\n", addOK(x, y));
            printf("Standard addOK: %d\n", addOK_standard(x, y));
            break;
        case 'B':
            printf("Enter an integer and two byte positions (n and m): ");
            scanf("%d %d %d", &x, &n, &m);
            printf("Custom byteswap: %d\n", byteswap(x, n, m));
            printf("Standard byteswap: %d\n", byteswap_standard(x, n, m));
            break;
        case 'g':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom bang: %d\n", bang(x));
            printf("Standard bang: %d\n", bang_standard(x));
            break;
        case 'P':
            printf("Enter an integer: ");
            scanf("%d", &x);
            printf("Custom bitParity: %d\n", bitParity(x));
            printf("Standard bitParity: %d\n", bitParity_standard(x));
            break;
        case 'R':
            printf("Enter number of tests: ");
            int tests;
            scanf("%d", &tests);
            for (int i = 0; i < tests; i++)
            {
                printf("Test %d:\n", i + 1);
                int x = randint();
                printf("AbsVal:\n");
                printf("Custom absVal: %d ", absVal(x));
                printf("Standard absVal: %d\n", absVal_standard(x));
                if (absVal(x) != absVal_standard(x))
                    printf("Failed on %d\n", x);
                else{
                    printf("Passed on %d\n", x);
                }
                x = randint();
                printf("Negate:\n");
                printf("Custom negate: %d ", negate(x));
                printf("Standard negate: %d\n", negate_standard(x));
                if (negate(x) != negate_standard(x))    
                    printf("Failed on %d\n", x);
                else{
                    printf("Passed on %d\n", x);
                }
                int y = randint();
                printf("BitAnd:\n");
                printf("Custom bitAnd: %d ", bitAnd(x, y));
                printf("Standard bitAnd: %d\n", bitAnd_standard(x, y));
                if (bitAnd(x, y) != bitAnd_standard(x, y))  
                    printf("Failed on %d, %d\n", x, y);
                else{
                    printf("Passed on %d, %d\n", x, y);
                }   
                x = randint();
                y = randint();
                printf("BitOr:\n");
                printf("Custom bitOr: %d ", bitOr(x, y));
                printf("Standard bitOr: %d\n", x | y);
                if (bitOr(x, y) != (x | y))  
                    printf("Failed on %d, %d\n", x, y);
                else{
                    printf("Passed on %d, %d\n", x, y);
                }
                x = randint();
                y = randint();
                printf("BitXor:\n");
                printf("Custom bitXor: %d ", bitXor(x, y)); 
                printf("Standard bitXor: %d\n", bitXor_standard(x, y));
                if (bitXor(x, y) != bitXor_standard(x, y))  
                    printf("Failed on %d, %d\n", x, y);
                else{
                    printf("Passed on %d, %d\n", x, y);
                }
                x = randint();  
                printf("isTmax:\n");
                printf("Custom isTmax: %d ", isTmax(x));
                printf("Standard isTmax: %d\n", isTmax_standard(x));
                if (isTmax(x) != isTmax_standard(x))
                    printf("Failed on %d\n", x);
                else{
                    printf("Passed on %d\n", x);
                }
                x = randint();
                printf("BitCount:\n");
                printf("Custom bitCount: %d ", bitCount(x));
                printf("Standard bitCount: %d\n", bitCount_standard(x));
                if (bitCount(x) != bitCount_standard(x))
                    printf("Failed on %d\n", x);
                else{
                    printf("Passed on %d\n", x);    
                }
                int highbit = rand() % 32;
                int lowbit = rand() % (highbit + 1);
                printf("BitMask:\n");
                printf("Custom bitMask: %d ", bitMask(highbit, lowbit));
                printf("Standard bitMask: %d\n", bitMask_standard(highbit, lowbit));
                if (bitMask(highbit, lowbit) != bitMask_standard(highbit, lowbit))
                    printf("Failed on %d, %d\n", highbit, lowbit);
                else{
                    printf("Passed on %d, %d\n", highbit, lowbit);
                }
                x = randint();
                y = randint();
                printf("AddOK:\n");
                printf("Custom addOK: %d ", addOK(x, y));   
                printf("Standard addOK: %d\n", addOK_standard(x, y));
                if (addOK(x, y) != addOK_standard(x, y))
                    printf("Failed on %d, %d\n", x, y);
                else{
                    printf("Passed on %d, %d\n", x, y);
                }   
                x = randint();
                n = rand() % 4;
                m = rand() % 4; 
                printf("Byteswap:\n");
                printf("Custom byteswap: %d ", byteswap(x, n, m));
                printf("Standard byteswap: %d\n", byteswap_standard(x, n, m));
                if (byteswap(x, n, m) != byteswap_standard(x, n,   
m))
                    printf("Failed on %d, %d, %d\n", x, n, m);
                else{
                    printf("Passed on %d, %d, %d\n", x, n, m);
                }
                x = randint();
                printf("Bang:\n");
                printf("Custom bang: %d ", bang(x));    
                printf("Standard bang: %d\n", bang_standard(x));
                if (bang(x) != bang_standard(x))
                    printf("Failed on %d\n", x);    
                else{
                    printf("Passed on %d\n", x);    
                }
                x = randint();
                printf("BitParity:\n");
                printf("Custom bitParity: %d ", bitParity(x));
                printf("Standard bitParity: %d\n", bitParity_standard(x));
                if (bitParity(x) != bitParity_standard(x))
                    printf("Failed on %d\n", x);
                else{
                    printf("Passed on %d\n", x);
                }
                printf("\n");
            }
            break;
        default:
            printf("Invalid operation!\n");
            break; 
        }
        getchar();
    }
    return 0;
}