#include <ncurses.h>
#include <string.h>

void start_menu(void);

void start_ncurses() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    start_menu();
}

void end_ncurses() {
    endwin();
}

void start_menu() {
    const char *banner[] = {
        "d8,                                                                            ",
        "`8P                                                                             ",
        "                                                                                ",
        "d88   d8888b   88bd88b  d888b8b   .d888b,                                       ",
        "?88  d8P' ?88  88P' ?8bd8P' ?88   ?8b,                                          ",
        "88b 88b  d88 d88   88P88b  ,88b    `?8b                                        ",
        "`88b`?8888P'd88'   88b`?88P'`88b`?888P'                                        ",
        "    )88                                                                           ",
        ",88P                                                                           ",
        "`?888P                                                                            ",
        "                                                        d8, d8b              d8b ",
        "                                                        `8P  88P              88P ",
        "                                                            d88              d88  ",
        "88bd88b d8888b d8888b d8888b   88bd8b,d88b ?88,.d88b,  88b888   d8888b d888888  ",
        "88P'  `d8b_,dPd8P' `Pd8P' ?88  88P'`?8P'?8b`?88'  ?88  88P?88  d8b_,dPd8P' ?88  ",
        "d88     88b    88b    88b  d88 d88  d88  88P  88b  d8P d88  88b 88b    88b  ,88b ",
        "d88'     `?888P'`?888P'`?8888P'd88' d88'  88b  888888P'd88'   88b`?888P'`?88P'`88b",
        "                                            88P'                               ",
        "                                            d88                                 ",
        "                                            ?8P                                 "
    };
    int num_lines = sizeof(banner) / sizeof(banner[0]);
    int banner_start_y = (LINES / 2) - num_lines + 9;

    char *buttons[] = { "YES", "NO!" };
    int selected = 0;
    int ch;

    while (1) {
        clear();
        
        box(stdscr, 0, 0);

        int y = LINES / 2;
        int x_ok = COLS / 2 - 10;
        int x_cancel = COLS / 2 + 7;
        
        for (int i = 0; i < num_lines; i++) {
            int x = (COLS - strlen(banner[i])) / 2;
            mvprintw(banner_start_y + i, x, "%s", banner[i]);
        }

        mvprintw(LINES / 2 - 2, COLS / 2 - 7, "Are you ready?");

        // Draw buttons
        if (selected == 0) attron(A_REVERSE);
        mvprintw(y, x_ok, "%s", buttons[0]);
        if (selected == 0) attroff(A_REVERSE);

        if (selected == 1) attron(A_REVERSE);
        mvprintw(y, x_cancel, "%s", buttons[1]);
        if (selected == 1) attroff(A_REVERSE);

        refresh();
        ch = getch();

        if (ch == KEY_LEFT || ch == 'h') {
            selected = (selected - 1 + 2) % 2;
        } else if (ch == KEY_RIGHT || ch == 'l') {
            selected = (selected + 1) % 2;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        }
    }

    clear();
    box(stdscr, 0, 0);

    if (selected == 0) {
        mvprintw(LINES / 2, COLS / 2 - 17, "You deem yourself prepared, then.");
    } else {
        mvprintw(LINES / 2, COLS / 2 - 13, "I knew it from first sight.");
    }

    refresh();
    getch();
}