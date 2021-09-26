#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
#   include <curses.h>
#else
#   include <ncurses.h>
#endif

#define KEY_ESCAPE 27

const size_t BUFFER_SIZE = 4096;

void print_help(char *program_name) {
    fprintf(stderr, "Usage: %s <filename>\n", program_name);
}

WINDOW *create_window(char *window_name) {
    WINDOW *window = newwin(0, 0, 0, 0);
    keypad(window, TRUE);
    scrollok(window, TRUE);
    box(window, 0, 0);
    mvwprintw(window, 0, 2, "%s", window_name);
    wmove(window, 1, 1);
    waddnstr(window, "Hello therajskdhsakjdhkjashdkjashdjka", COLS - 2);
    return window;
}

char **read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[BUFFER_SIZE];
    size_t sz = 0;

    size_t total_lines = 1;
    char **lines = calloc(1, sizeof(*lines));
    while(sz = fread(buffer, sizeof(buffer) / sizeof(*buffer), 1, file)) {

    }
    fclose(file);
    return lines;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_help(argv[0]);
        return 0;
    }
    char *filename = argv[1];

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    
    WINDOW *window = create_window(filename);
    bool done = false;
    do {
        werase(window);
        switch (wgetch(window))
        {
        case KEY_ESCAPE:
            done = true;
            break;
        
        default:
            break;
        }
    } while (!done);
    return endwin();
}