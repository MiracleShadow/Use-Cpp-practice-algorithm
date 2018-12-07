#include<stdio.h>
#include<math.h>
#include<string.h>

int main()
{
    char ch1[100] = {"dasfdf2112"}, ch2[100];
    int i;
    for(i = 0; ch1[i] != '\0'; ++i) {
        ch2[i] = ch1[i];
    }
    ch2[i] = '\0';
    puts(ch2);
    return 0;
}