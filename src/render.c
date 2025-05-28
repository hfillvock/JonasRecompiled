#include <ncurses.h>
#include <string.h>
#include <signal.h>

void start_menu(void);

void check_terminal_size(void);

void handle_winch(int sig) {
    (void)sig;
    resizeterm(0, 0);
}

void start_ncurses() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    check_terminal_size();

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

void check_terminal_size() {
    int rows, cols;
    const int required_rows = 40;
    const int required_cols = 120;
    
    signal(SIGWINCH, handle_winch);
    
    while (1) {
        getmaxyx(stdscr, rows, cols);
        
        if (rows >= required_rows && cols >= required_cols) {
            break;
        }
        
        clear();

        int box_height = 7;
        int box_width = 80;
        int start_row = (rows - box_height) / 2;
        int start_col = (cols - box_width) / 2;
        
        if (start_row < 0) start_row = 0;
        if (start_col < 0) start_col = 0;
        if (start_row + box_height >= rows) start_row = rows - box_height - 1;
        if (start_col + box_width >= cols) start_col = cols - box_width - 1;
        
        box(stdscr, 0, 0);
        
        char warning1[] = "This game requires a 120x40 terminal size";
        char warning2[] = "Please resize your terminal accordingly";
        char current_size[50];
        snprintf(current_size, sizeof(current_size), "Current size: %dx%d", cols, rows);
        
        mvprintw(start_row + 1, start_col + (box_width - strlen(warning1)) / 2, "%s", warning1);
        mvprintw(start_row + 2, start_col + (box_width - strlen(current_size)) / 2, "%s", current_size);
        mvprintw(start_row + 3, start_col + (box_width - strlen(warning2)) / 2, "%s", warning2);

        refresh(); 

        timeout(500);
        int ch = getch();
        timeout(-1);
        
        if (ch == ERR) {
            endwin();
            refresh();
            continue;
        }
        
        endwin();
        refresh();
    }
    
    clear();
    refresh();
}