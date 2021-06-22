#include <stdio.h>

int getMask(int start, int end, int type){
    if (end > 31 || end < 0 || start > end || (type != 0 && type != 1) || start > 31 || start < 0){
        return 0;
    }
    unsigned int mask = ~(~0 << (end - start + 1)) << (start);
    if (start == 0 && end == 31){
        mask = -1;
    }
    if (type == 0){
        return ~mask;
    }
    return mask;
}

int getSubInt(int start, int stop, int num){
    if ((stop > 31 || stop < 0) || (start > 31 || start < 0) || (start > stop)){
        return 0;
    }
    unsigned int ret = ((getMask(start, stop, 1) & num));
    return ret >> start;
}

void printDashHex(int num){
    for (int i = 0; i < 8; i++){
        int retNum = getSubInt((31 - (i * 4)) - 4, 31 - (i * 4), num);
        if (retNum >= 9)
        {
            printf("%x", retNum);
        }
        else
        {
            printf("%c", retNum + 55);
        }
        if (i != 7)
        {
            printf("-");
        }
        else
        {
            printf("\n");
        }
    }
}

int main()
{
    printDashHex(0x12ab);
}
