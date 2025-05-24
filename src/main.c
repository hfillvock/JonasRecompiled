#include <ncurses.h>

int main(void) {
    // Initialize ncurses
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Dont echo keypresses
    keypad(stdscr, TRUE);   // Enable arrowkeys
    curs_set(0);            // Hide the cursor

    // Drawing a basic interface
    mvprintw(0, 0, "Hello World!");
    mvprintw(2, 0, "press 'q' to quit.");

    // Refresh the screen
    refresh();

    // Wait for user input
    int ch;
    while ((ch = getch()) != 'q') {
        mvprintw(4, 0, "you pressed: %c", ch);
        refresh();
    }
    
    endwin();
    
    return 0;
}