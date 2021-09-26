#include <stdio.h>
#include <locale.h>

#ifdef _WIN32
#   include <curses.h>
#else
#   include <ncurses.h>
#endif

#define KEY_ESCAPE 27

void print_help(char *program_name) {
    fprintf(stderr, "Usage: %s <filename>\n", program_name);
}

WINDOW *create_window(char *window_name) {
    WINDOW *window = newwin(0, 0, 0, 0);
    keypad(window, TRUE);
    scrollok(window, TRUE);
    box(window, 0, 0);
    mvwprintw(window, 0, 2, "%s", window_name);
    return window;
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
    int c;
    while((c = wgetch(window)) != KEY_ESCAPE) {
        box(window, 0, 0); 
        wrefresh(window);
    }
    return endwin();
}