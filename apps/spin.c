#include <stdio.h>

void sleep();

int main() {
    uint32_t flag = 0;
    uint32_t r = 0;
    uint32_t c = 0;
    char ch = 'X';
    for (int i = 0; i < 50000; ++i)
    {
        setChar(r, c ,ch);
        sleep();
        flag++;
        if (flag > 0 && flag < 80)
        {
            c++;
        }
        else if (flag >= 80 && flag < 103)
        {
            r++;
        }
        else if (flag >= 103 && flag < 182)
        {
            c--;
        }
        else if (flag >= 182 && flag < 205)
        {
            r--;
        }
        else if (flag == 205)
        {
            flag = 0;
        }

    }
    return 0;
}

void sleep() {
    for (size_t i = 0; i < 100000; ++i) {
        asm volatile("nop");
    }
}
