/* Code originally from http://j.mearie.org/post/7462182919/spelt-number-to-decimal
   The original aimed at being as short as possible. I made some changes to make it
   more standards-compliant.
*/

#include <stdio.h>
long long int func(char *s)
{
  long long int n = 0, u = 0, m = 0, b = 0;
  int e, r;
  for (; n++ || (e = *s++ | 32) > 0; b = "ynwtsflrabg"[n %= 11] - e ? b : b * 8 + n)
    for (r = b % 64 - 25; e < 47 && b; b /= 8)
      for (n = 19; n; )
      {
        u = 1ll << 6177 % n-- * 4;
        if (!("1+DIY/.K430x9G(kC["[n] - 42 & 255 ^ b))
        {
          m +=
            (n > 15)?  n :
              (n > 9)? m % u * ~-u :
                (~r)?  n + !r * 16 :
                       n * 16;
          b = 0;
        }
      }
  return m;
}
int func2(char *s)
{
  int n = 0, u = 0, m = 0, b = 0;
  int e, r;
  for (; n++ || (e = *s++ | 32) > 0; b = "yntfgwslra"[n %= 10] - e ? b : b * 9 + n)
    for (r = b % 81 - 19; e < 47 && b; b /= 9)
      for (n = 17; n; )
      {
        u = 1 << 198 % n-- * 4;
        if (!("2+ADM-0a.4|1C;=j"[n] - 42 & 255 ^ b))
        {
          m +=
            (n > 13)?  n + 2 :
              (n > 9)? m % u * ~-u :
                (~r)?  n + !r * 16 :
                       n * 16;
          b = 0;
        }
      }
  return m;
}
int main(void)
{
  char spelt[] = "fifty thousand one hundred and one";
  long long int long_decimal = func(spelt);
  int decimal = func2(spelt);
  printf("%llx, %x\n", long_decimal, decimal);
  return 0;
}
