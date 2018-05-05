#include <myos/core/cctype>

namespace myos::core {

int islower(int ch) {
    return (ch >= 'a' && ch <= 'z');
}

int isupper(int ch) {
    return (ch >= 'A' && ch <= 'Z');
}

int isalpha(int ch) {
    return islower(ch) || isupper(ch);
}

int isdigit(int ch) {
    return ch >= '0' && ch <= '9';
}

int isalnum(int ch) {
    return isdigit(ch) || isalpha(ch);
}

int isspace(int ch) {
    return ch == 0x20 || ch == 0x0c || ch == 0x0a || ch == 0x0d || ch == 0x09 || ch == 0x0b;
}

int tolower(int ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - ('A' - 'a');
    }
    return ch;
}

int toupper(int ch) {
    if (ch >= 'a' && ch <= 'z') {
        ch = ch + ('A' - 'a');
    }
    return ch;
}

}

#ifndef UNIT_TEST

extern "C" {

int islower(int ch) {
    return myos::core::islower(ch);
}

int isupper(int ch) {
    return myos::core::isupper(ch);
}

int isalpha(int ch) {
    return myos::core::isalnum(ch);
}

int isdigit(int ch) {
    return myos::core::isdigit(ch);
}

int isalnum(int ch) {
    return myos::core::isalnum(ch);
}

int isspace(int ch) {
    return myos::core::isspace(ch);
}

int tolower(int ch) {
    return myos::core::tolower(ch);
}

int toupper(int ch) {
    return myos::core::toupper(ch);
}

}

#endif
