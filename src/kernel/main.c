#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

enum App {
    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

static void runApp(enum App app, uint8_t *buffer);

static void showInfo();

void _start() {
    showInfo();
    disableCurser();
    uint8_t *buffer = (void *) 0x200000;
    while (true) {
        char ch = getchar();
        enum App app = -1;
        switch (ch) {
        case '1':
            app = TOP_LEFT;
            break;
        case '2':
            app = TOP_RIGHT;
            break;
        case '3':
            app = BOTTOM_LEFT;
            break;
        case '4':
            app = BOTTOM_RIGHT;
            break;
        default:
            break;
        }
        if (app != -1) {
            runApp(app, buffer);
        }
    }
}

static void runApp(enum App app, uint8_t *buffer) {
    char appName[] = {'A', 'P', 'P', '0', '.', 'E', 'X', 'E'};

    switch (app) {
    case TOP_LEFT:
        appName[3] = '1';
        break;
    case TOP_RIGHT:
        appName[3] = '2';
        break;
    case BOTTOM_LEFT:
        appName[3] = '3';
        break;
    case BOTTOM_RIGHT:
        appName[3] = '4';
        break;
    default:
        break;
    }
    if (appName[3] == '0') {
        return;
    }
    size_t size = loadFile(appName, buffer);
    if (size > 0) {
        uint32_t offset = *(uint32_t *) (buffer + 24) - 0x08048000;
        void (*appFn)() = (void (*)()) (buffer + offset);
        appFn();
        for (int i = 2; i < 25; ++i) {
            for (int j = 0; j < 80; ++j) {
                putchar(i, j, ' ');
                changeAttribute(i, j, false, false, WHITE, BLACK);
            }
        }
    }
}

static void showInfo() {
    char info[] = "16337060_zelin  16337063_kaifeng\0";
    const size_t infoLen = sizeof(info);
    const size_t cols = 80;
    const size_t paddings = (80 - infoLen) / 2;
    int j = 0;
    for (size_t i = 0; i < cols; ++i) {
        if (i < paddings || (cols - i - 1) < paddings) {
            putchar(0, i, ' ');
        } else {
            putchar(0, i, info[j++]);
        }
        putchar(1, i, '-');
    }
}