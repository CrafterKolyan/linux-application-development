#include <stdlib.h>
#include <locale.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) < (b)) ? (b) : (a))
#endif

#ifdef _WIN32
#   include <curses.h>
#else
#   include <ncurses.h>
#endif

#define KEY_ESCAPE 27

struct Lines {
    char **lines;
    int total_lines;
};

void print_help(char *program_name) {
    fprintf(stderr, "Usage: %s <filename>\n", program_name);
}

WINDOW *create_window() {
    WINDOW *window = newwin(0, 0, 0, 0);
    keypad(window, TRUE);
    scrollok(window, TRUE);
    return window;
}

struct Lines read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    size_t sz = ftell(file);
    
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc((sz + 1) * sizeof(*buffer));
    size_t read_size = fread(buffer, 1, sz, file);
    buffer[read_size] = 0;
    fclose(file);

    size_t lines_capacity = 1;
    struct Lines lines;
    lines.lines = malloc(lines_capacity * sizeof(*lines.lines));
    lines.total_lines = 0;

    size_t start = 0;
    for (size_t i = 0; i < sz; ++i) {
        if (buffer[i] == '\n') {
            if (lines.total_lines >= lines_capacity) {
                lines_capacity *= 2;
                lines.lines = realloc(lines.lines, lines_capacity * sizeof(*lines.lines));
            }

            lines.lines[lines.total_lines++] = buffer + start;
            buffer[i] = 0;
            start = i + 1;
        }
    }
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

    struct Lines lines = read_file(filename);
    WINDOW *window = create_window(filename);
    bool done = false;

    int offsetY = 0;
    do {
        werase(window);
        box(window, 0, 0);
        mvwprintw(window, 0, 2, "%s", filename);
        for (int i = 1; (i < window->_maxy) && (i + offsetY - 1 < lines.total_lines); ++i) {
            mvwaddnstr(window, i, 1, lines.lines[i + offsetY - 1],  window->_maxx - 1);
        }
        wrefresh(window);

        switch (wgetch(window))
        {
        case KEY_ESCAPE:
            done = true;
            break;

        case ' ':
        case KEY_DOWN:
            offsetY = min(offsetY + 1, lines.total_lines - 1);
            break;

        case KEY_UP:
            offsetY = max(offsetY - 1, 0);
            break;
        
        default:
            break;
        }
    } while (!done);

    free(lines.lines[0]);
    free(lines.lines);

    delwin(window);
    return endwin();
}