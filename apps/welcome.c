#include <stdio.h>

int main() {
    char msg[] =
            "Welcome to MyOS alpha 0.1 !!!\n"
            "Copyright 2018 Zelin Feng, Kaifeng Gong\n"
            "This software is distributed under MIT license, "
            "which means, there is absolutely NO WARRANTY FOR ANY "
            "PARTICULAR PURPOSES\n\0";
    puts(msg);
    return 0;
}
