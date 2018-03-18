void _start() {
    char *video = (char *) 0xb8000;
    *video = 'H';
    *(video + 2) = 'e';
}