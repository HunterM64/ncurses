#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD   4

char *choices[] = {
    "Add Card",
    "Change Card",
    "Remove Card",
    "Exit",
};

char *choices_nums[] = {
    "1", "2", "3", "4"
};

void clear_messages() {
    move(LINES -3, 0);
    clrtoeol();

    return;
}

int main() {
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;

    int choice = 0;
    int highlight = 1;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);
    // I have no idea what a calloc is 
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i)
            my_items[i] = new_item(choices_nums[i], choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F1 to Exit");
    post_menu(my_menu);
    refresh();

    while((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                clear_messages();

                if(highlight != n_choices) {
                    highlight++;
                }

                menu_driver(my_menu, REQ_DOWN_ITEM);
                
                break;

            case KEY_UP:
                clear_messages();

                if (highlight != 1) {
                    highlight--;
                }

                menu_driver(my_menu, REQ_UP_ITEM);
                
                break;

            case 10: /*ENTER*/
                choice = highlight;

                mvprintw(LINES - 3, 0, "You chose choice %d", choice);
                
                break;

        }
    }

    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();

}