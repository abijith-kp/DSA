#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define safe_strlen(string)     \
    ({ (string) ?               \
          strlen(string):       \
          (size_t)0; })

char *strings[3] = {"broood", "bananaaa", "hiphophiphop"};

int *encode_string(char *string)
{
    int l=safe_strlen(string);
    int *encode = (int *)calloc(sizeof(int), l);

    int i=0, j=0, f=0, t;
    char list[26] = "abcdefghijklmnopqrstuvwxyz";

    for(i=0; string[i] != '\0'; i++)
    {
        f = 0;
        for(j=25; j>=0; j--)
        {
            if((list[j] == string[i]) && (f == 0))
            {
                t = list[j];
                encode[i] = j;
                f = 1;
                if(j == 0)
                    break;
            }
            if((f == 1) || (f == 2)) {
                if(f == 1) {
                    f = 2;
                    continue;
                }
                list[j+1] = list[j];
            }
        }
        list[0] = t;
    }

    return encode;
}

char *decode_string(int *encode, int l)
{
    int i=0, j=0;
    char t, list[26] = "abcdefghijklmnopqrstuvwxyz";
    char *decode = (char *)calloc(sizeof(char), l);

    for(i=0; i<l; i++)
    {
        t = list[encode[i]];
        for(j=encode[i]-1; j>=0; j--)
        {
            list[j+1] = list[j];
        }
        list[0] = t;
        decode[i] = t;
    }

    return decode;
}

int main(int argc, char **argv)
{
    int l=0, i=0, j=0, *encode;
    char *decode;

    for(j=0; j<3; j++)
    {
        l = safe_strlen(strings[j]);
        encode = encode_string(strings[j]);
        printf("\n");
        for(i=0; i<l; i++)
            printf("%d ", encode[i]);

        decode = decode_string(encode, l);
        printf("\n%s\n", decode);
    }

    return 0;
}
