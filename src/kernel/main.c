#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

enum App {
    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

static void runApp(enum App app, uint8_t *buffer);

void _start() {
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
    // runApp(TOP_LEFT, buffer);
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
        void (*appFn)() = (void (*)()) buffer;
        appFn();
    }
}