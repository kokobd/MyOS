#include <stdio.h>

void sleep();

int main() {
    uint32_t flag = 0;
    uint32_t r = 0;
    uint32_t c = 0;
    uint32_t rPrev = 0;
    uint32_t cPrev = 0;
    char ch = 'X';
    for (int i = 0; i < 25; ++i)
    {
        for (int j = 0; j < 80; ++j)
        {
            setChar(i, j, ' ');
        }
    }

    for (int i = 0; i < 50000; ++i) {
        setChar(r, c, ch);
        sleep();
        rPrev = r;
        cPrev = c;
        flag++;
        if (flag > 0 && flag < 80) {
            c++;
        } else if (flag >= 80 && flag < 104) {
            r++;
        } else if (flag >= 104 && flag < 183) {
            c--;
        } else if (flag >= 183 && flag < 207) {
            r--;
        } else if (flag == 207) {
            flag = 0;
        }
        setChar(rPrev, cPrev, ' ');
    }
    return 0;
}

void sleep() {
    for (size_t i = 0; i < 1000000; ++i) {
        asm volatile("nop");
    }
}
