#if defined(__APPLE__)
#define _XOPEN_SOURCE_EXTENDED
#endif



#include <locale.h>
#include <wchar.h>
#include <wctype.h>  
#include <ncurses.h>
#include <unistd.h>
#include <string.h>


#define MAX_LEN 100

int main() {
    setlocale(LC_ALL, "");              
    initscr();
    start_color();
    cbreak();
    noecho();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(8));

    echo();
    mvprintw(0, 0, "Enter text: ");
    wchar_t wtext[MAX_LEN];
    getn_wstr((wint_t*)wtext, MAX_LEN - 1);       
    noecho();
    curs_set(0);

    int len = wcslen(wtext);
    int color_index = 0;

    clear();
    while (1) {
        int col = 0;
        for (int i = 0; i < len; i++) {
            int pair = (color_index + i) % 7 + 1;
            attron(COLOR_PAIR(pair));
            mvaddnwstr(0, col, &wtext[i], 1);  
            attroff(COLOR_PAIR(pair));
            int w = wcwidth(wtext[i]);         
            col += (w > 0 ? w : 1);
        }
        refresh();
        usleep(100000);
        color_index = (color_index + 1) % 7;
    }

    endwin();
    return 0;
}
