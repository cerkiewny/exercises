#include<ncurses.h>
#include<array>
#include<random>

class board{
    public:
        enum direction {up, down, left, right};

    private:
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution;
        std::default_random_engine generator2;
        std::uniform_int_distribution<int> distribution2;
        bool game_over;

        std::array< int, 16 > fields;
    public:
        board() : distribution(0,16), distribution2(0,4), game_over(false) { fields.fill(0); addrand(); print_fields();}
        void refreshBoard(){
            addrand();
            game_over = false;
            fields.fill(0);
            print_fields();
        }

        void addrand(){
            int field = distribution(generator);
            int value = distribution2(generator2);
            bool seen0 = false;
            for(int i = 0; i < 16; i++){
                if(fields[i] == 0){ seen0 = true ;}
            }
            if(seen0 == false){
                game_over = true;
                return;
            }

            if (value < 3){
                value = 1;
            }
            else{
                value = 2;
            }

            while(fields[field] != 0){
                field = distribution(generator);
            }
            fields[field] = value;
        }

        void step(direction dir){
            if(game_over) return;
            switch (dir){
                case(up):
                    if(!moveUp()) return;
                    break;
                case(down):
                    if(!moveDown()) return;
                    break;
                case(left):
                    if(!moveLeft()) return;
                    break;
                case(right):
                    if(!moveRight()) return;
                    break;
            }
            clear();
            addrand();
            print_fields();
            refresh();
        };
    bool moveUp(){
        bool change = true;
        bool ret = false;
        while(change){
            change = false;
            for(int i = 4; i < 16; i ++){
                if( fields[i - 4] == 0 && fields[i] != 0){
                    change = true;
                    ret = true;
                    fields[i - 4] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        for(int i = 4; i < 16; i ++){
            if( fields[i - 4] == fields[i] && fields[i] != 0){
                ret = true;
                fields[i - 4]++;
                fields[i] = 0;
            }
        }
        change = true;
        while(change){
            change = false;
            for(int i = 4; i < 16; i ++){
                if( fields[i - 4] == 0 && fields[i] != 0){
                    change = true;
                    ret = true;
                    fields[i - 4] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        return ret;
    }
    bool moveDown(){
        bool ret = false;
        bool change = true;
        while(change){
            change = false;
            for(int i = 11; i >= 0; i--){
                if( fields[i + 4] == 0 && fields[i] != 0){
                    ret = true;
                    change = true;
                    fields[i + 4] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        for(int i = 11; i >= 0; i--){
            if( fields[i + 4] == fields[i] && fields[i] != 0){
                ret = true;
                fields[i + 4]++;
                fields[i] = 0;
            }
        }
        change = true;
        while(change){
            change = false;
            for(int i = 11; i >= 0; i--){
                if( fields[i + 4] == 0 && fields[i] != 0){
                    ret = true;
                    change = true;
                    fields[i + 4] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        return ret;
    }

    bool moveLeft(){
        bool ret = false;
        bool change = true;
        while(change){
            change = false;
            for(int i = 0; i < 16; i++){
                if( i % 4 == 0){
                    continue;
                }
                if( fields[i - 1] == 0 && fields[i] != 0){
                    ret = true;
                    change = true;
                    fields[i - 1] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        for(int i = 0; i < 16; i++){
            if( i % 4 == 0){
                continue;
            }
            if( fields[i - 1] == fields[i] && fields[i] != 0){
                ret = true;
                fields[i - 1]++;
                fields[i] = 0;
            }
        }
        change = true;
        while(change){
            change = false;
            for(int i = 0; i < 16; i++){
                if( i % 4 == 0){
                    continue;
                }
                if( fields[i - 1] == 0 && fields[i] != 0){
                    change = true;
                    ret = true;
                    fields[i - 1] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        return ret;
    }
    bool moveRight(){
        bool ret = false;
        bool change = true;
        while(change){
            change = false;
            for(int i = 15; i >= 0; i--){
                if( (i + 1 )% 4 == 0){
                    continue;
                }
                if( fields[i + 1] == 0 && fields[i] != 0){
                    change = true;
                    ret = true;
                    fields[i + 1] = fields[i];
                    fields[i] = 0;
                }
            }
        }
        for(int i = 15; i >= 0; i--){
            if( ( i + 1 ) % 4 == 0){
                continue;
            }
            if( fields[i + 1] == fields[i] && fields[i] != 0){
                ret = true;
                fields[i + 1]++;
                fields[i] = 0;
            }
        }
        change = true;
        while(change){
            change = false;
            for(int i = 15; i >= 0; i--){
                if( ( i + 1) % 4 == 0){
                    continue;
                }
                if( fields[i + 1] == 0 && fields[i] != 0){
                    ret = true;
                    change = true;
                    fields[i + 1]++;
                    fields[i] = 0;
                }
            }
        }
        return ret;
    }

    void print_fields(){
        if(game_over){ printw ( "Press N to try again\n"); }
        for(int i = 0; i < 16; i++){
            printw("%i ", fields[i]);
            if((i + 1)% 4 == 0 && i != 0){
                printw("\n");
            }
        }
    }
};


bool curses_started = false;

void endCurses() {
    if (curses_started && !isendwin())
    endwin();
}


void startCurses() {
    if (curses_started) {
        refresh();
    }
    else {
        initscr();
        cbreak();
        noecho();
        intrflush(stdscr, false);
        keypad(stdscr, true);
        curses_started = true;
    }
}


int main(){
    startCurses();
    bool end = false;
    board bd = board();
    while(!end){
        int ch = getch();
        switch(ch){
            case('q'):
                end = true;
                endCurses();
                break;
            case('n'):
                bd.refreshBoard();
                break;
            case(KEY_UP):
                bd.step(board::direction::up);
                break;
            case(KEY_DOWN):
                bd.step(board::direction::down);
                break;
            case(KEY_LEFT):
                bd.step(board::direction::left);
                break;
            case(KEY_RIGHT):
                bd.step(board::direction::right);
                break;
        }
    }
}
