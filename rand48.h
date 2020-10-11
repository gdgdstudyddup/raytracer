#ifndef DRAND48_H  
#define DRAND48_H  
#define mm 0x100000000LL  
#define cc 0xB16  
#define aa 0x5DEECE66DLL  
  
#include <stdlib.h>  
  
static unsigned long long seed = 1;  
  
double drand48(void)  
{  
    seed = (aa * seed + cc) & 0xFFFFFFFFFFFFLL;  
    unsigned int x = seed >> 16;  
    return  ((double)x / (double)mm);  
      
}  
  
void srand48(unsigned int i)  
{  
    seed  = (((long long int)i) << 16) | rand();  
}  
  
#endif //DRAND48_H