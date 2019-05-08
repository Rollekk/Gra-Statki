#include <allegro.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <functional>

#define board_size 40
#define number_of_elements 12
#define window_size_x (board_size*(number_of_elements+4))
#define window_size_y (board_size*(number_of_elements+4))

using namespace std;

inline void init()
{
    allegro_init();

    install_keyboard();
    install_mouse();

    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, window_size_x, window_size_y, 0, 0);


    show_mouse( screen );
    unscare_mouse();
}
inline void deinit()
{
    clear_keybuf();
    allegro_exit();
}
void read_score()
{
    int scores_amount=5;
    char temp[50];

    FILE *player_score;
    player_score = fopen("player_score.txt", "r");

    if(player_score)
    {
        if(fgets(temp, 50, player_score) != NULL);
        scores_amount = atoi(temp);

        int score_tab[scores_amount];

        for(int i=0; i<scores_amount; i++)
        {
            if(fgets(temp, 50, player_score) != NULL);
            score_tab[i] = atoi(temp);
        }

        fclose(player_score);

        sort( score_tab, score_tab + scores_amount, greater < int >() );


        if(scores_amount>5)
        {
            for(int i=0; i<5; i++)
            {
                textprintf_ex( screen, font, 310, 190+i*50, makecol( 255, 255, 255 ), -1, "%d", score_tab[i] );
            }
        }
    }
    else
    {
        textprintf_ex( screen, font, 50, 60, makecol( 255, 0, 0 ), -1, "Brak wynikow do wyswietlenia" );
    }
}

void save_score(int score)
{
    int scores_amount=5;
    char temp[50];

    FILE *player_score;
    player_score = fopen("player_score.txt", "r");

    if(player_score)
    {
        if(fgets(temp, 50, player_score) != NULL);
        scores_amount = atoi(temp);

        int score_tab[scores_amount+1];

        score_tab[scores_amount] = score;

        for(int i=0; i<scores_amount; i++)
        {
            if(fgets(temp, 50, player_score) != NULL);
            score_tab[i] = atoi(temp);
        }

        fclose(player_score);

        player_score = fopen("player_score.txt", "w");

        sort( score_tab, score_tab + scores_amount, greater < int >() );

        fprintf(player_score, "%d\n", scores_amount+1);

        for(int i=0; i<10; i++)
        {
            fprintf(player_score, "%d\n", score_tab[i]);
        }

        fclose(player_score);
    }
    else
    {
        fclose(player_score);

        player_score = fopen("player_score.txt", "w");
        fprintf(player_score, "%d\n", score);

        fclose(player_score);
    }
}
bool check_board(int board[number_of_elements][number_of_elements], int i, int j)
{
    if(board[i][j]>0 || board[i+1][j]>0 || board[i-1][j]>0 || board[i][j+1]>0 || board[i][j-1]>0 ||
            board[i+1][j+1]>0 || board[i+1][j-1]>0 || board[i-1][j+1]>0 || board[i-1][j-1]>0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
void generate_ships(int board[number_of_elements][number_of_elements])
{
    srand( time( NULL ) );

    for(int i=0; i<number_of_elements; i++)
    {
        for(int j=0; j<number_of_elements; j++)
        {
            board[i][j] = 0;
        }
    }


    bool ship4=TRUE;

    while(ship4)
    {
        int i = rand()%number_of_elements;
        int j = rand()%number_of_elements;
        int direction = rand()%8;

        if(check_board(board, i, j))
        {

            if(direction == 0)
            {
                if((i+3)<number_of_elements && check_board(board, i+1, j) && check_board(board, i+2, j) &&
                        check_board(board, i+3, j))
                {
                    board[i][j] = 2;
                    board[i+1][j] = 2;
                    board[i+2][j] = 2;
                    board[i+3][j] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 1)
            {
                if((i-3)>0 && check_board(board, i-1, j) && check_board(board, i-2, j) && check_board(board, i-3, j))
                {
                    board[i][j] = 2;
                    board[i-1][j] = 2;
                    board[i-2][j] = 2;
                    board[i-3][j] = 2;
                    ship4=FALSE;
                }
            }

            {
                if((j+3)<number_of_elements && check_board(board, i, j+1) && check_board(board, i, j+2) &&
                        check_board(board, i, j+3))
                {
                    board[i][j] = 2;
                    board[i][j+1] = 2;
                    board[i][j+2] = 2;
                    board[i][j+3] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 3)
            {
                if((j-3)>0 && check_board(board, i, j-1) && check_board(board, i, j-2) && check_board(board, i, j-3))
                {
                    board[i][j] = 2;
                    board[i][j-1] = 2;
                    board[i][j-2] = 2;
                    board[i][j-3] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 4)
            {
                if(((i+3)<number_of_elements) && ((j+3)<number_of_elements) && check_board(board, i+1, j+1) &&
                        check_board(board, i+2, j+2) && check_board(board, i+3, j+3))
                {
                    board[i][j] = 2;
                    board[i+1][j+1] = 2;
                    board[i+2][j+2] = 2;
                    board[i+3][j+3] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 5)
            {
                if(((i-3)>0) && ((j+3)<number_of_elements) && check_board(board, i-1, j+1) && check_board(board, i-2, j+2) &&
                        check_board(board, i-3, j+3))
                {
                    board[i][j] = 2;
                    board[i-1][j+1] = 2;
                    board[i-2][j+2] = 2;
                    board[i-3][j+3] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 6)
            {
                if(((i+3)<number_of_elements) && ((j-3)>0) && check_board(board, i+1, j-1) && check_board(board, i+2, j-2) &&
                        check_board(board, i+3, j-3))
                {
                    board[i][j] = 2;
                    board[i+1][j-1] = 2;
                    board[i+2][j-2] = 2;
                    board[i+3][j-3] = 2;
                    ship4=FALSE;
                }
            }

            if(direction == 7)
            {
                if(((i-3)>0) && ((j-3)>0) && check_board(board, i-1, j-1) && check_board(board, i-2, j-2) &&
                        check_board(board, i-3, j-3))
                {
                    board[i][j] = 2;
                    board[i-1][j-1] = 2;
                    board[i-2][j-2] = 2;
                    board[i-3][j-3] = 2;
                    ship4=FALSE;
                }
            }
        }
    }



    for(int szt2=0; szt2<2; szt2++)
    {
        bool ship3=TRUE;

        while(ship3)
        {
            int i = rand()%number_of_elements;
            int j = rand()%number_of_elements;
            int direction = rand()%8;

            if(check_board(board, i, j))
            {

                if(direction == 0)
                {
                    if((i+2)<number_of_elements && check_board(board, i+1, j) && check_board(board, i+2, j))
                    {
                        board[i][j] = 2;
                        board[i+1][j] = 2;
                        board[i+2][j] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 1)
                {
                    if((i-2)>0&& check_board(board, i-1, j) && check_board(board, i-2, j))
                    {
                        board[i][j] = 2;
                        board[i-1][j] = 2;
                        board[i-2][j] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 2)
                {
                    if((j+2)<number_of_elements&& check_board(board, i, j+1) && check_board(board, i, j+2))
                    {
                        board[i][j] = 2;
                        board[i][j+1] = 2;
                        board[i][j+2] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 3)
                {
                    if((j-2)>0&& check_board(board, i, j-1) && check_board(board, i, j-2))
                    {
                        board[i][j] = 2;
                        board[i][j-1] = 2;
                        board[i][j-2] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 4)
                {
                    if(((i+2)<number_of_elements) && ((j+2)<number_of_elements) && check_board(board, i+1, j+1) &&
                            check_board(board, i+2, j+2))
                    {
                        board[i][j] = 2;
                        board[i+1][j+1] = 2;
                        board[i+2][j+2] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 5)
                {
                    if(((i-2)>0) && ((j+2)<number_of_elements) && check_board(board, i-1, j+1) && check_board(board, i-2, j+2))
                    {
                        board[i][j] = 2;
                        board[i-1][j+1] = 2;
                        board[i-2][j+2] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 6)
                {
                    if(((i+2)<number_of_elements) && ((j-2)>0) && check_board(board, i+1, j-1) && check_board(board, i+2, j-2))
                    {
                        board[i][j] = 2;
                        board[i+1][j-1] = 2;
                        board[i+2][j-2] = 2;
                        ship3=FALSE;
                    }
                }

                if(direction == 7)
                {
                    if(((i-2)>0) && ((j-2)>0) && check_board(board, i-1, j-1) && check_board(board, i-2, j-2))
                    {
                        board[i][j] = 2;
                        board[i-1][j-1] = 2;
                        board[i-2][j-2] = 2;
                        ship3=FALSE;
                    }
                }
            }
        }
    }


    for(int szt3=0; szt3<3; szt3++)
    {
        bool ship2=TRUE;

        while(ship2)
        {
            int i = rand()%number_of_elements;
            int j = rand()%number_of_elements;
            int direction = rand()%8;

            if(check_board(board, i, j))
            {

                if(direction == 0)
                {
                    if((i+1)<number_of_elements && check_board(board, i+1, j))
                    {
                        board[i][j] = 2;
                        board[i+1][j] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 1)
                {
                    if((i-1)>0 && check_board(board, i-1, j))
                    {
                        board[i][j] = 2;
                        board[i-1][j] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 2)
                {
                    if((j+1)<number_of_elements && check_board(board, i, j+1))
                    {
                        board[i][j] = 2;
                        board[i][j+1] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 3)
                {
                    if((j-1)>0 && check_board(board, i, j-1))
                    {
                        board[i][j] = 2;
                        board[i][j-1] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 4)
                {
                    if(((i+1)<number_of_elements) && ((j+1)<number_of_elements) && check_board(board, i+1, j+1))
                    {
                        board[i][j] = 2;
                        board[i+1][j+1] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 5)
                {
                    if(((i-1)>0) && ((j+1)<number_of_elements) && check_board(board, i-1, j+1))
                    {
                        board[i][j] = 2;
                        board[i-1][j+1] = 2;
                        ship2=FALSE;
                    }
                }
                if(direction == 6)
                {
                    if(((i+1)<number_of_elements) && ((j-1)>0) && check_board(board, i+1, j-1))
                    {
                        board[i][j] = 2;
                        board[i+1][j-1] = 2;
                        ship2=FALSE;
                    }
                }

                if(direction == 7)
                {
                    if(((i-1)>0) && ((j-1)>0) && check_board(board, i-1, j-1))
                    {
                        board[i][j] = 2;
                        board[i-1][j-1] = 2;
                        ship2=FALSE;
                    }
                }
            }
        }
    }

    for(int szt4=0; szt4<4; szt4++)
    {
        bool ship=TRUE;

        while(ship)
        {
            int i = rand()%number_of_elements;
            int j = rand()%number_of_elements;

            if(check_board(board, i, j))
            {
                board[i][j] = 2;
                ship = FALSE;
            }
        }
    }
}

int computer_fire(int board[number_of_elements][number_of_elements], BITMAP * screen, int stopper, int player_score)
{
    BITMAP * computer_hit = NULL;
    BITMAP * computer_miss = NULL;
    BITMAP * lose = NULL;

    lose = load_bmp("lose.bmp", default_palette);
     if( !lose )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania bitmapy lose" );
        allegro_exit();
    }
    computer_miss = load_bmp( "computer_miss.bmp", default_palette);
     if( !computer_miss )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania bitmapy computer_miss" );
        allegro_exit();
    }
    computer_hit = load_bmp( "computer_hit.bmp", default_palette );
     if( !computer_hit )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania bitmapy computer_hit" );
        allegro_exit();
    }

    int hit = 20;

    bool roll = TRUE;

    while(roll)
    {
        if(stopper == 0)
        {
            break;
        }
        int i = rand()%12;
        int j = rand()%12;

        if(board[i][j] == 0)
        {

            masked_blit(computer_miss, screen, 0, 0, 527, 87, window_size_x, window_size_y);
            rest(500);
            board[i][j] = 1;
            roll = FALSE;
        }

        if(board[i][j] == 2)
        {

            masked_blit(computer_hit, screen, 0, 0, 527, 87, window_size_x, window_size_y);
            rest(500);
            board[i][j] = 3;
            hit = hit-1;
        }
        if(hit == 0)
        {
            masked_blit(lose, screen, 0, 0, 0, 0, window_size_x, window_size_y);
            textprintf_ex( screen, font, 320, 280, makecol( 255, 255, 255), -1, "%d", player_score );
            rest(3000);
            return hit;
        }

    }
        return hit;
}
void print_map(int board[number_of_elements][number_of_elements])
{
    BITMAP * playing_board = NULL;

    playing_board = load_bmp( "playing_board.bmp", default_palette );
    if( !playing_board )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania bitmapy playing_board" );
        allegro_exit();
    }
    blit(playing_board, screen, 0, 0, 0, 0, window_size_x, window_size_y);

    for(int i=1; i<number_of_elements+1; i++)
    {
        for(int j=1; j<number_of_elements+1; j++)
        {

            if(board[i-1][j-1] == 1)
            {
                circlefill(screen, (board_size*j)+(board_size/2), (board_size*i)+(board_size/2)+board_size, 3, makecol(255, 255, 255));
            }

            if(board[i-1][j-1] == 2)
            {
                rect(screen, board_size*j, board_size*i+board_size, (board_size*j)+board_size, (board_size*i)+2*board_size, makecol(255, 255, 255));
            }

            if(board[i-1][j-1] == 3)
            {
                rect(screen, board_size*j, board_size*i+board_size, (board_size*j)+board_size, (board_size*i)+2*board_size, makecol(255, 255, 255));
                line(screen, board_size*j, board_size*i+board_size, (board_size*j)+board_size, (board_size*i)+2*board_size, makecol(255, 0, 0));
                line(screen, board_size*j, (board_size*i)+2*board_size, (board_size*j)+board_size, board_size*i+board_size, makecol(255, 0, 0));
            }
        }
    }
}
void print_map_hid(int board[number_of_elements][number_of_elements])
{

    for(int i=1; i<number_of_elements+1; i++)
    {
        for(int j=1; j<number_of_elements+1; j++)
        {
            if(board[i-1][j-1] == 1)
            {
                circlefill(screen, (board_size*j)+(board_size/2), (board_size*i)+(board_size/2)+board_size, 3, makecol(255, 255, 255));
            }
            if(board[i-1][j-1] == 3)
            {
                rect(screen, board_size*j, board_size*i+board_size, (board_size*j)+board_size, (board_size*i)+2*board_size, makecol(255, 255, 255));
                line(screen, board_size*j, board_size*i+board_size, (board_size*j)+board_size, (board_size*i)+2*board_size, makecol(255, 0, 0));
                line(screen, board_size*j, (board_size*i)+2*board_size, (board_size*j)+board_size, board_size*i+board_size, makecol(255, 0, 0));
            }
        }
    }
}
int bitmapa()
{

    BITMAP * board = NULL;
    BITMAP * aim = NULL;
    BITMAP * menu = NULL;
    BITMAP * menu_strip = NULL;
    BITMAP * background_menu = NULL;
    BITMAP * help = NULL;
    BITMAP * playing_board = NULL;
    BITMAP * enter = NULL;
    BITMAP * enter_black = NULL;
    BITMAP * player_hit = NULL;
    BITMAP * player_miss = NULL;
    BITMAP * player_already = NULL;
    BITMAP * win = NULL;
    BITMAP * player_dead = NULL;
    BITMAP * score = NULL;
    BITMAP * esc = NULL;

    board = create_bitmap( window_size_x, window_size_y);

    if( !board )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad tworzenia board" );
        allegro_exit();
        return 0;
    }

    aim = load_bmp( "aim.bmp", default_palette );
    if( !aim )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania aim" );
        allegro_exit();
        return 0;
    }

    menu_strip = load_bmp("menu_strip.bmp", default_palette );
    if( !menu_strip )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania stzalki" );
        allegro_exit();
        return 0;
    }

    playing_board = load_bmp( "playing_board.bmp", default_palette );
    if( !playing_board )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania playing_board" );
        allegro_exit();
    }

    menu = load_bmp( "menu3.bmp", default_palette );
    if( !menu )

    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania menu" );
        allegro_exit();
        return 0;
    }

    background_menu = load_bmp("background_menu.bmp", default_palette);
    if (!background_menu)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania tla" );
        allegro_exit();
        return 0;
    }

    help = load_bmp("help.bmp", default_palette);
    if (!help)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania help" );
        allegro_exit();
        return 0;
    }
    player_already = load_bmp("player_already.bmp", default_palette);
    if (!player_already)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania player_already" );
        allegro_exit();
        return 0;
    }
    player_miss = load_bmp("player_miss.bmp", default_palette);
    if (!player_miss)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania player_miss" );
        allegro_exit();
        return 0;
    }
    player_hit = load_bmp("player_hit.bmp", default_palette);
    if (!player_hit)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania player_hit" );
        allegro_exit();
        return 0;
    }
    enter = load_bmp("enter.bmp", default_palette);
    if (!enter)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania enter" );
        allegro_exit();
        return 0;
    }
    enter_black = load_bmp("enter_black.bmp", default_palette);
    if (!enter_black)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania enter_black" );
        allegro_exit();
        return 0;
    }
    win = load_bmp("win.bmp", default_palette);
    if( !win )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania win" );
        allegro_exit();
        return 0;
    }
    player_dead = load_bmp("player_dead.bmp", default_palette);
    if(!player_dead)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania win" );
        allegro_exit();
        return 0;
    }
    score = load_bmp( "score.bmp", default_palette );
    if( !score )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania score" );
        allegro_exit();
    }
     esc = load_bmp( "esc.bmp", default_palette );
    if( !esc )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Blad wczytania esc" );
        allegro_exit();
        return 0;
    }
    int menu_pos=0, menu_pos_hid=1;
    int menu_strip_x = 0, menu_strip_y = board_size;

    int stopper = 1;

    int background_menu_x = 0;
    int background_menu_y = 0;

    int menu_x = 0;
    int menu_y = 0;

    int player_board[number_of_elements][number_of_elements];
    int computer_board[number_of_elements][number_of_elements];

    do
    {
        if(key[KEY_UP])
        {
            if(menu_strip_y>(board_size*1.5))
            {
                menu_strip_y=menu_strip_y-(board_size*1.5);
                menu_pos_hid-=1;
            }
        }

        if(key[KEY_DOWN])
        {
            if(menu_strip_y<(((number_of_elements/2)-1.5)*board_size))
            {
                menu_strip_y=menu_strip_y+(board_size*1.5);
                menu_pos_hid+=1;

            }
        }

        if( key[ KEY_ENTER ] )
        {
            menu_pos = menu_pos_hid;
        }

        rest(200);
        clear_bitmap(board);
        draw_sprite(board, background_menu, background_menu_x, background_menu_y);
        draw_sprite(board, menu_strip, menu_strip_x, menu_strip_y+143);
        draw_sprite(board, menu, menu_x, menu_y);
        blit( board, screen, 0, 0, 0, 0, window_size_x, window_size_y );

        if(menu_pos == 1)
        {
            int computer_hp = 1;
            int start = 1;
            int turn = 0;

            int player_score = 100;

            generate_ships(player_board);
            generate_ships(computer_board);

            bool refresh_map = TRUE;
            bool next = FALSE;

            while((computer_hp>0))
            {
                int aim_x = board_size, aim_y = board_size*2;
                menu_pos = 0;

                if(start == 1)
                {
                    stopper = 1;
                    clear_bitmap(board);
                    print_map(player_board);
                    rest(2000);
                    start = 0;
                }

                refresh_map = TRUE;
                next = TRUE;

                if(turn==0)
                {
                    while(next)
                    {
                        if(key[KEY_ESC])
                        {
                            stopper = 0;
                            break;
                        }
                        if(computer_hp == 0)
                        {
                            masked_blit(win, screen, 0, 0, 0, 0, window_size_x, window_size_y);
                            textprintf_ex( screen, font, 320, 280, makecol( 255, 255, 255), -1, "%d", player_score );
                            rest(3000);
                            stopper = 0;
                            break;
                        }
                        if(refresh_map)
                        {

                            blit(playing_board, screen, 0, 0, 0, 0, window_size_x, window_size_y);
                            print_map_hid(computer_board);
                            clear_bitmap(board);
                            refresh_map = FALSE;
                        }

                        if( key[ KEY_LEFT ] )
                        {
                            if(aim_x>board_size)
                            {
                                aim_x=aim_x-board_size;
                                blit(playing_board, screen, 0,0,0,0, window_size_x,window_size_y);
                                print_map_hid(computer_board);
                            }
                        }

                        if( key[ KEY_RIGHT ] )
                        {
                            if(aim_x<(number_of_elements*board_size))
                            {
                                aim_x=aim_x+board_size;
                                blit(playing_board, screen, 0,0,0,0, window_size_x,window_size_y);
                                print_map_hid(computer_board);
                            }
                        }

                        if( key[ KEY_UP ] )
                        {
                            if(aim_y>2*board_size)
                            {
                                aim_y=aim_y-board_size;
                                blit(playing_board, screen, 0,0,0,0, window_size_x,window_size_y);
                                print_map_hid(computer_board);

                            }
                        }

                        if( key[ KEY_DOWN ] )
                        {
                            if(aim_y<(number_of_elements*board_size)+board_size)
                            {
                                aim_y=aim_y+board_size;
                                blit(playing_board, screen, 0,0,0,0, window_size_x,window_size_y);
                                print_map_hid(computer_board);
                            }
                        }

                        if( key[ KEY_SPACE ] )
                        {
                            if(computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] == 1)
                            {
                                masked_blit(player_already,screen, 0, 0,527, 87, window_size_x, window_size_y);
                                rest(1000);
                            }
                            if(computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] == 0)
                            {
                                masked_blit(player_miss,screen, 0, 0,527, 87, window_size_x, window_size_y);
                                computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] = 1;

                                rest(1000);

                                refresh_map = TRUE;
                                next = FALSE;
                                player_score--;
                            }
                            if(computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] == 4)
                            {
                                masked_blit(player_dead,screen, 0, 0,527, 87, window_size_x, window_size_y);
                                rest(1000);
                            }
                            if(computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] == 3)
                            {
                                masked_blit(player_already,screen, 0, 0,527, 87, window_size_x, window_size_y);
                                rest(1000);
                            }
                            if(computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] == 2)
                            {
                                masked_blit(player_hit,screen, 0, 0,527, 87, window_size_x, window_size_y);
                                computer_board[(aim_y-2*board_size)/board_size][(aim_x-board_size)/board_size] = 3;

                                rest(1000);
                                computer_hp =computer_hp-1;
                                refresh_map = TRUE;
                                player_score+=5;
                            }

                        }

                        rest(200);
                        masked_blit(aim, screen, 0, 0, aim_x, aim_y, aim->w, aim->h );
                    }
                    turn = 1;
                }
                else
                {
                    if(key[KEY_ESC])
                    {
                        stopper = 0;
                        break;
                    }
                    if(computer_hp == 0)
                    {
                        save_score(player_score);
                        masked_blit(win, screen, 0, 0, 0, 0, window_size_x, window_size_y);
                        textprintf_ex( screen, font, 320, 280, makecol( 255, 255, 255), -1, "%d", player_score );
                        rest(3000);
                        stopper = 0;
                        break;

                    }
                    print_map(player_board);
                    if(computer_fire(player_board, screen,stopper, player_score) == 0)
                    {
                        stopper = 0;
                        break;
                    }
                    rest(500);
                    print_map(player_board);
                    refresh_map = FALSE;

                    while( !key[ KEY_ENTER ])
                    {
                        masked_blit(enter, screen,0,0,530, 152, window_size_x,window_size_y);
                        rest(200);
                        blit(enter_black, screen, 0, 0, 530, 152, window_size_x, window_size_y);
                        rest(200);
                    }
                    turn = 0;
                }
            }
        }
        if(menu_pos == 2)
        {
            clear_bitmap(board);
            blit( score, screen, 0, 0, 0, 0, window_size_x, window_size_y );
            read_score();

            while( !key[KEY_ESC])
            {
             masked_blit(esc, screen,0,0,303, 464, window_size_x,window_size_y);
             rest(200);
             blit(enter_black, screen, 0, 0, 303, 464, window_size_x, window_size_y);
             rest(200);
            }
            menu_pos = 0;
        }

        if(menu_pos == 3)
        {
            clear_bitmap(board);
            blit(help, screen, 0, 0, 0, 0, window_size_x, window_size_y);

            while( !key[KEY_ESC]);
            menu_pos = 0;
        }
    }
    while(menu_pos!=4);
    return 0;
}

int main()
{
    init();
    bitmapa();
    deinit();
    return 0;
}
END_OF_MAIN();
