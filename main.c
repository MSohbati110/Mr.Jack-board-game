#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int jack_id,turn,flashlight=0,round=1,visible=1,victory=2;
int cards[8] = {0,0,0,0,0,0,0,0},SH_cards[8] = {0,0,0,0,0,0,0,0},SH_cards_t=8;
int coords_x[8] = {6,5,3,5,9,5,1,4},coords_y[8] = {7,1,7,5,6,13,5,9};

struct
{
    int type;
    char condition[5];
}map[9][13];

void reed_map ()
{
    int i,j;
    FILE *f_map;
    f_map = fopen("map.txt","r");
    for (i=0;i<9;i++)
    {
        for (j=0;j<13;j++)
        {
            fscanf(f_map,"%d",&map[i][j].type);
            fscanf(f_map,"%s",&map[i][j].condition);
        }
    }
    fclose(f_map);
}
void show_map ()
{
    int i,j,t;
    char x[18][7][5];
    char y[21][3];

    // showing types

    for (i=0;i<18;i++)
    {
        if (i%2 == 0)
        {
            for (j=0;j<6;j++)
            {
                if (map[i/2][2*j +1].type == 0)
                {
                    if (map[i/2][2*j +1].condition[0] == 'N')
                    {
                        x[i][j][0] = ' ';
                        x[i][j][1] = ' ';
                        x[i][j][2] = '\0';
                    }
                    else
                    {
                        x[i][j][0] = map[i/2][2*j +1].condition[0];
                        x[i][j][1] = map[i/2][2*j +1].condition[1];
                        x[i][j][2] = '\0';
                    }
                }
                if (map[i/2][2*j +1].type == 1)
                {
                    x[i][j][0] = '*';
                    x[i][j][1] = '*';
                    x[i][j][2] = '\0';
                }
                if (map[i/2][2*j +1].type == 2)
                {
                    x[i][j][0] = 'h';
                    x[i][j][1] = 'o';
                    x[i][j][2] = 'l';
                    x[i][j][3] = 'e';
                    x[i][j][4] = '\0';
                }
                if (map[i/2][2*j +1].type == 3)
                {
                    x[i][j][0] = 'l';
                    x[i][j][1] = 'a';
                    x[i][j][2] = 'm';
                    x[i][j][3] = 'p';
                    x[i][j][4] = '\0';
                }
                if (map[i/2][2*j +1].type == 4)
                {
                    x[i][j][0] = 'o';
                    x[i][j][1] = 'u';
                    x[i][j][2] = 't';
                    x[i][j][3] = '\0';
                }
            }
        }
        if (i%2 == 1)
        {
            for (j=0;j<7;j++)
            {
                if (map[i/2][2*j].type == 0)
                {
                    if (map[i/2][2*j].condition[0] == 'N')
                    {
                        x[i][j][0] = ' ';
                        x[i][j][1] = ' ';
                        x[i][j][2] = '\0';
                    }
                    else
                    {
                        x[i][j][0] = map[i/2][2*j].condition[0];
                        x[i][j][1] = map[i/2][2*j].condition[1];
                        x[i][j][2] = '\0';
                    }
                }
                if (map[i/2][2*j].type == 1)
                {
                    x[i][j][0] = '*';
                    x[i][j][1] = '*';
                    x[i][j][2] = '\0';
                }
                if (map[i/2][2*j].type == 2)
                {
                    x[i][j][0] = 'h';
                    x[i][j][1] = 'o';
                    x[i][j][2] = 'l';
                    x[i][j][3] = 'e';
                    x[i][j][4] = '\0';
                }
                if (map[i/2][2*j].type == 3)
                {
                    x[i][j][0] = 'l';
                    x[i][j][1] = 'a';
                    x[i][j][2] = 'm';
                    x[i][j][3] = 'p';
                    x[i][j][4] = '\0';
                }
                if (map[i/2][2*j].type == 4)
                {
                    x[i][j][0] = 'o';
                    x[i][j][1] = 'u';
                    x[i][j][2] = 't';
                    x[i][j][3] = '\0';
                }
            }
        }
    }

    // showing conditions

    y[0][0] = map[0][5].condition[0];
    y[0][1] = '\0';
    y[1][0] = map[0][0].condition[0];
    y[1][1] = '\0';
    if (map[0][2].condition[0] == 'O')
    {
        y[2][0] = ' ';
        y[2][1] = ' ';
    }
    else if (map[0][2].condition[0] == 'R')
    {
        y[2][0] = 'r';
        y[2][1] = ' ';
    }
    else if (strlen(map[0][2].condition) == 4)
    {
        y[2][0] = 'r';
        y[2][1] = '4';
    }
    else if (strlen(map[0][2].condition) == 3)
    {
        y[2][0] = 'r';
        y[2][1] = '3';
    }
    else if (strlen(map[0][2].condition) == 2)
    {
        y[2][0] = 'r';
        y[2][1] = '2';
    }
    else
    {
        y[2][0] = 'r';
        y[2][1] = '1';
    }
    y[2][2] = '\0';
    y[3][0] = map[0][10].condition[0];
    y[3][1] = '\0';
    y[4][0] = map[0][12].condition[0];
    y[4][1] = '\0';
    if (map[1][5].condition[0] == 'O')
    {
        y[5][0] = ' ';
        y[5][1] = ' ';
    }
    else if (map[1][5].condition[0] == 'R')
    {
        y[5][0] = 'r';
        y[5][1] = ' ';
    }
    else if (strlen(map[1][5].condition) == 4)
    {
        y[5][0] = 'r';
        y[5][1] = '4';
    }
    else if (strlen(map[1][5].condition) == 3)
    {
        y[5][0] = 'r';
        y[5][1] = '3';
    }
    else if (strlen(map[1][5].condition) == 2)
    {
        y[5][0] = 'r';
        y[5][1] = '2';
    }
    else
    {
        y[5][0] = 'r';
        y[5][1] = '1';
    }
    y[5][2] = '\0';
    if (map[1][11].condition[0] == 'O')
    {
        y[6][0] = ' ';
        y[6][1] = ' ';
    }
    else if (map[1][11].condition[0] == 'R')
    {
        y[6][0] = 'r';
        y[6][1] = ' ';
    }
    else if (strlen(map[1][11].condition) == 4)
    {
        y[6][0] = 'r';
        y[6][1] = '4';
    }
    else if (strlen(map[1][11].condition) == 3)
    {
        y[6][0] = 'r';
        y[6][1] = '3';
    }
    else if (strlen(map[1][11].condition) == 2)
    {
        y[6][0] = 'r';
        y[6][1] = '2';
    }
    else
    {
        y[6][0] = 'r';
        y[6][1] = '1';
    }
    y[6][2] = '\0';
    y[7][0] = map[1][2].condition[0];
    y[7][1] = '\0';
    if (map[3][7].condition[0] == 'O')
    {
        y[8][0] = ' ';
        y[8][1] = ' ';
    }
    else if (map[3][7].condition[0] == 'R')
    {
        y[8][0] = 'r';
        y[8][1] = ' ';
    }
    else if (strlen(map[3][7].condition) == 4)
    {
        y[8][0] = 'r';
        y[8][1] = '4';
    }
    else if (strlen(map[3][7].condition) == 3)
    {
        y[8][0] = 'r';
        y[8][1] = '3';
    }
    else if (strlen(map[3][7].condition) == 2)
    {
        y[8][0] = 'r';
        y[8][1] = '2';
    }
    else
    {
        y[8][0] = 'r';
        y[8][1] = '1';
    }
    y[8][2] = '\0';
    y[9][0] = map[3][10].condition[0];
    y[9][1] = '\0';
    y[10][0] = map[4][6].condition[0];
    y[10][1] = '\0';
    if (map[5][5].condition[0] == 'O')
    {
        y[11][0] = ' ';
        y[11][1] = ' ';
    }
    else if (map[5][5].condition[0] == 'R')
    {
        y[11][0] = 'r';
        y[11][1] = ' ';
    }
    else if (strlen(map[5][5].condition) == 4)
    {
        y[11][0] = 'r';
        y[11][1] = '4';
    }
    else if (strlen(map[5][5].condition) == 3)
    {
        y[11][0] = 'r';
        y[11][1] = '3';
    }
    else if (strlen(map[5][5].condition) == 2)
    {
        y[11][0] = 'r';
        y[11][1] = '2';
    }
    else
    {
        y[11][0] = 'r';
        y[11][1] = '1';
    }
    y[11][2] = '\0';
    y[12][0] = map[5][2].condition[0];
    y[12][1] = '\0';
    if (map[7][1].condition[0] == 'O')
    {
        y[13][0] = ' ';
        y[13][1] = ' ';
    }
    else if (map[7][1].condition[0] == 'R')
    {
        y[13][0] = 'r';
        y[13][1] = ' ';
    }
    else if (strlen(map[7][1].condition) == 4)
    {
        y[13][0] = 'r';
        y[13][1] = '4';
    }
    else if (strlen(map[7][1].condition) == 3)
    {
        y[13][0] = 'r';
        y[13][1] = '3';
    }
    else if (strlen(map[7][1].condition) == 2)
    {
        y[13][0] = 'r';
        y[13][1] = '2';
    }
    else
    {
        y[13][0] = 'r';
        y[13][1] = '1';
    }
    y[13][2] = '\0';
    if (map[7][7].condition[0] == 'O')
    {
        y[14][0] = ' ';
        y[14][1] = ' ';
    }
    else if (map[7][7].condition[0] == 'R')
    {
        y[14][0] = 'r';
        y[14][1] = ' ';
    }
    else if (strlen(map[7][7].condition) == 4)
    {
        y[14][0] = 'r';
        y[14][1] = '4';
    }
    else if (strlen(map[7][7].condition) == 3)
    {
        y[14][0] = 'r';
        y[14][1] = '3';
    }
    else if (strlen(map[7][7].condition) == 2)
    {
        y[14][0] = 'r';
        y[14][1] = '2';
    }
    else
    {
        y[14][0] = 'r';
        y[14][1] = '1';
    }
    y[14][2] = '\0';
    y[15][0] = map[7][11].condition[0];
    y[15][1] = '\0';
    y[16][0] = map[7][0].condition[0];
    y[16][1] = '\0';
    y[17][0] = map[8][7].condition[0];
    y[17][1] = '\0';
    if (map[8][11].condition[0] == 'O')
    {
        y[18][0] = ' ';
        y[18][1] = ' ';
    }
    else if (map[8][11].condition[0] == 'R')
    {
        y[18][0] = 'r';
        y[18][1] = ' ';
    }
    else if (strlen(map[8][11].condition) == 4)
    {
        y[18][0] = 'r';
        y[18][1] = '4';
    }
    else if (strlen(map[8][11].condition) == 3)
    {
        y[18][0] = 'r';
        y[18][1] = '3';
    }
    else if (strlen(map[8][11].condition) == 2)
    {
        y[18][0] = 'r';
        y[18][1] = '2';
    }
    else
    {
        y[18][0] = 'r';
        y[18][1] = '1';
    }
    y[18][2] = '\0';
    y[19][0] = map[8][0].condition[0];
    y[19][1] = '\0';
    y[20][0] = map[8][12].condition[0];
    y[20][1] = '\0';
    printf("         1     2     3     4     5     6     7     8     9     10    11    12    13       \n");
    printf("\n");
    printf("             .....       .....       .....       .....       .....       .....            \n");
    printf("            .     .     .     .     .     .     .     .     .     .     .     .           \n");
    printf("       .....  %s   .....  %s   ..... %s  .....  %s   .....  %s   .....  %s   .....        \n",x[0][0],x[0][1],x[0][2],x[0][3],x[0][4],x[0][5]);
    printf("      .     .     .     .     .     .  %s  .     .     .     .     .     .     .     .    \n",y[0]);
    printf("1    .  %s  ..... %s  .....  %s   .....  %s   .....  %s   ..... %s  .....  %s  .          \n",x[1][0],x[1][1],x[1][2],x[1][3],x[1][4],x[1][5],x[1][6]);
    printf("      .  %s  .     . %s  .     .     .     .     .     .     .     .  %s  .     .  %s  .  \n",y[1],y[2],y[3],y[4]);
    printf("       .....  %s   .....  %s   ..... %s  .....  %s   .....  %s   ..... %s  .....          \n",x[2][0],x[2][1],x[2][2],x[2][3],x[2][4],x[2][5]);
    printf("      .     .     .     .     .     . %s  .     .     .     .     .     . %s  .     .     \n",y[5],y[6]);
    printf("2    .  %s   ..... %s  .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .      \n",x[3][0],x[3][1],x[3][2],x[3][3],x[3][4],x[3][5],x[3][6]);
    printf("      .     .*****.  %s  .     .     .*****.     .*****.     .     .     .     .     .    \n",y[7]);
    printf("       .....**%s***.....  %s   .....**%s***.....**%s***.....  %s   .....  %s   .....      \n",x[4][0],x[4][1],x[4][2],x[4][3],x[4][4],x[4][5]);
    printf("      .     .*****.     .     .     .*****.     .*****.     .     .     .     .     .     \n");
    printf("3    .  %s   .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .    \n",x[5][0],x[5][1],x[5][2],x[5][3],x[5][4],x[5][5],x[5][6]);
    printf("      .     .*****.     .*****.     .     .     .     .     .*****.     .     .     .     \n");
    printf("       .....**%s***.....**%s***.....  %s   ..... %s  .....**%s***.....  %s   .....        \n",x[6][0],x[6][1],x[6][2],x[6][3],x[6][4],x[6][5]);
    printf("      .     .*****.*****.*****.     .     .     . %s  .     .*****.     .     .     .     \n",y[8]);
    printf("4    .  %s   .....**%s***.....  %s   .....  %s   .....  %s   ..... %s  .....  %s   .      \n",x[7][0],x[7][1],x[7][2],x[7][3],x[7][4],x[7][5],x[7][6]);
    printf("      .     .*****.*****.     .     .*****.     .*****.     .     .  %s  .     .     .    \n",y[9]);
    printf("       .....**%s***.....  %s   .....**%s***.....**%s***.....  %s   .....  %s   .....      \n",x[8][0],x[8][1],x[8][2],x[8][3],x[8][4],x[8][5]);
    printf("      .     .*****.     .     .     .*****.     .*****.     .     .*****.     .     .     \n");
    printf("5    .  %s   .....  %s   .....  %s   ..... %s  .....  %s   .....**%s***.....  %s   .      \n",x[9][0],x[9][1],x[9][2],x[9][3],x[9][4],x[9][5],x[9][6]);
    printf("      .     .     .     .*****.     .     .  %s  .     .     .*****.*****.*****.     .    \n",y[10]);
    printf("       .....  %s   .....**%s***..... %s  .....  %s   .....**%s***.....**%s***.....        \n",x[10][0],x[10][1],x[10][2],x[10][3],x[10][4],x[10][5]);
    printf("      .     .     .     .*****.     . %s  .     .     .     .*****.*****.*****.     .     \n",y[11]);
    printf("6    .  %s   ..... %s  .....  %s   .....  %s   .....  %s   .....**%s***.....  %s   .      \n",x[11][0],x[11][1],x[11][2],x[11][3],x[11][4],x[11][5],x[11][6]);
    printf("      .     .     .  %s  .     .     .*****.     .*****.     .     .*****.*****.     .    \n",y[12]);
    printf("       .....  %s   .....  %s   .....**%s***.....**%s***.....  %s   .....**%s***.....      \n",x[12][0],x[12][1],x[12][2],x[12][3],x[12][4],x[12][5]);
    printf("      .     .     .     .     .     .*****.     .*****.     .     .     .*****.     .     \n");
    printf("7    .  %s   .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .    \n",x[13][0],x[13][1],x[13][2],x[13][3],x[13][4],x[13][5],x[13][6]);
    printf("      .     .     .     .     .     .     .     .     .     .     .     .     .     .     \n");
    printf("       ..... %s  .....  %s   .....  %s   ..... %s  .....  %s   ..... %s  .....            \n",x[14][0],x[14][1],x[14][2],x[14][3],x[14][4],x[14][5]);
    printf("      .     . %s  .     .     .     .     .     . %s  .     .     .     .  %s  .     .    \n",y[13],y[14],y[15]);
    printf("8    . %s  .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .....  %s   .      \n",x[15][0],x[15][1],x[15][2],x[15][3],x[15][4],x[15][5],x[15][6]);
    printf("      .  %s  .     .     .     .     .     .     .     .     .*****.     .     .     .    \n",y[16]);
    printf("       .....  %s   .....  %s   .....  %s   ..... %s  .....**%s***..... %s  .....          \n",x[16][0],x[16][1],x[16][2],x[16][3],x[16][4],x[16][5]);
    printf("      .     .     .     .     .     .     .     .  %s  .     .*****.*****. %s  .     .    \n",y[17],y[18]);
    printf("9    .  %s  .....  %s   .....  %s   .....  %s   .....  %s   .....**%s***.....  %s  .      \n",x[17][0],x[17][1],x[17][2],x[17][3],x[17][4],x[17][5],x[17][6]);
    printf("      .  %s  .     .     .     .     .     .     .     .     .     .*****.     .  %s  .   \n",y[19],y[20]);
    printf("       .....       .....       .....       .....       .....       .....       .....      \n");
    printf("\n\n");
    printf("round %d\n",round);
    if (visible == 0)
    {
        printf("jack is invisible\n\n");
    }
    if (visible == 1)
    {
        printf("jack is visible\n\n");
    }
}
void jack_identity ()
{
    printf("so i want you 2 to choose your character between jack and detective\n");
    sleep(5);
    int r;
    r = rand();
    if (r%8 == 0)
    {
       jack_id = 1;
    }
    if (r%8 == 1)
    {
       jack_id = 2;
    }
    if (r%8 == 2)
    {
       jack_id = 3;
    }
    if (r%8 == 3)
    {
       jack_id = 4;
    }
    if (r%8 == 4)
    {
       jack_id = 5;
    }
    if (r%8 == 5)
    {
       jack_id = 6;
    }
    if (r%8 == 6)
    {
       jack_id = 7;
    }
    if (r%8 == 7)
    {
       jack_id = 8;
    }
    SH_cards[jack_id -1] = 1;
    SH_cards_t--;
    printf("Now Detective Do not look at the monitor\n");
    sleep(4);
    printf("The identity of Jack is :\n");
    sleep(2);
    printf(".\n");
    sleep(2);
    printf(".\n");
    sleep(2);
    printf(".\n");
    sleep(2);
    if (jack_id == 1)
    {
        printf("Sherlock Holmes   aka   SH");
    }
    if (jack_id == 2)
    {
        printf("John Watson   aka   JW");
    }
    if (jack_id == 3)
    {
        printf("John Smith   aka   JS");
    }
    if (jack_id == 4)
    {
        printf("Inspector Lestrade   aka   IL");
    }
    if (jack_id == 5)
    {
        printf("Miss Stealthy   aka   MS");
    }
    if (jack_id == 6)
    {
        printf("Sergeant Goodley   aka   SG");
    }
    if (jack_id == 7)
    {
        printf("William Gull   aka   WG");
    }
    if (jack_id == 8)
    {
        printf("Jeremy Bert   aka   JB");
    }
    sleep(5);
    system("cls");
}
void welcom ()
{
    printf("welcome to the Mr jack game\n");
    sleep(10);
    printf("What?!\n");
    sleep(3);
    printf("What are you waiting for?!\n");
    sleep(3);
    printf("you want me to explain the rules?\n");
    sleep(3);
    printf("nah i am tooooooo lazy to explain the game for you, but you can check it in here i guess: www.aparat.com/v/gaiNR\n");
    sleep(3);
    printf("But with a small change : characters can not stay in holes\n");
    sleep(7);
    printf("now Lets begin the game\n");
    printf("Hope u like it\n");
    sleep(5);
    system("cls");
}
void jack_visible ()
{
    int x,y,t=0,x1,y1;
    x = coords_x[jack_id-1]-1;
    y = coords_y[jack_id-1]-1;
    if (y%2 == 0)
    {
        if (((map[x-1][y].type == 3 && map[x-1][y].condition[0] != 'O') || (map[x-1][y].type == 0 && map[x-1][y].condition[0] != 'N')) && x >= 1)
        {
            t=1;
        }
        if (((map[x][y-1].type == 3 && map[x][y-1].condition[0] != 'O') || (map[x][y-1].type == 0 && map[x][y-1].condition[0] != 'N')) && y >= 1)
        {
            t=1;
        }
        if (((map[x][y+1].type == 3 && map[x][y+1].condition[0] != 'O') || (map[x][y+1].type == 0 && map[x][y+1].condition[0] != 'N')) && y <= 11)
        {
            t=1;
        }
        if (((map[x+1][y-1].type == 3 && map[x+1][y-1].condition[0] != 'O') || (map[x+1][y-1].type == 0 && map[x+1][y-1].condition[0] != 'N')) && x <= 7 && y >= 1)
        {
            t=1;
        }
        if (((map[x+1][y].type == 3 && map[x+1][y].condition[0] != 'O') || (map[x+1][y].type == 0 && map[x+1][y].condition[0] != 'N')) && x <= 7)
        {
            t=1;
        }
        if (((map[x+1][y+1].type == 3 && map[x+1][y+1].condition[0] != 'O') || (map[x+1][y+1].type == 0 && map[x+1][y+1].condition[0] != 'N')) && x <= 7 && y <= 11)
        {
            t=1;
        }
    }
    if (y%2 == 1)
    {
        if (((map[x-1][y-1].type == 3 && map[x-1][y-1].condition[0] != 'O') || (map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')) && x >= 1 && y >= 1)
        {
            t=1;
        }
        if (((map[x-1][y].type == 3 && map[x-1][y].condition[0] != 'O') || (map[x-1][y].type == 0 && map[x-1][y].condition[0] != 'N')) && x >= 1)
        {
            t=1;
        }
        if (((map[x-1][y+1].type == 3 && map[x-1][y+1].condition[0] != 'O') || (map[x-1][y+1].type == 0 && map[x-1][y+1].condition[0] != 'N')) && x >= 1 && y <= 11)
        {
            t=1;
        }
        if (((map[x][y-1].type == 3 && map[x][y-1].condition[0] != 'O') || (map[x][y-1].type == 0 && map[x][y-1].condition[0] != 'N')) && y >= 1)
        {
            t=1;
        }
        if (((map[x][y+1].type == 3 && map[x][y+1].condition[0] != 'O') || (map[x][y+1].type == 0 && map[x][y+1].condition[0] != 'N')) && y <= 11)
        {
            t=1;
        }
        if (((map[x+1][y].type == 3 && map[x+1][y].condition[0] != 'O') || (map[x+1][y].type == 0 && map[x+1][y].condition[0] != 'N')) && x <= 7)
        {
            t=1;
        }
    }
    x1 = coords_x[1]-1;
    y1 = coords_y[1]-1;
    if (flashlight == 1)
    {
        while (x1 >= 0)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            x1--;
        }
    }
    if (flashlight == 2)
    {
        while (x1 >= 0 && y1 <= 12)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            if (y1%2 == 1)
            {
                x1--;
            }
            y1++;
        }
    }
    if (flashlight == 3)
    {
        while (x1 <= 8 && y1 <= 12)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            if (y1%2 == 0)
            {
                x1++;
            }
            y1++;
        }
    }
    if (flashlight == 4)
    {
        while (x1 <= 8)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            x1++;
        }
    }
    if (flashlight == 5)
    {
        while (x1 <= 8 && y1 >= 0)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            if (y1%2 == 0)
            {
                x1++;
            }
            y1--;
        }
    }
    if (flashlight == 6)
    {
        while (x1 >= 0 && y1 >= 0)
        {
            if (map[x1][y1].type == 1)
            {
                break;
            }
            if (x == x1 && y == y1)
            {
                t=1;
                break;
            }
            if (y1%2 == 1)
            {
                x1--;
            }
            y1--;
        }
    }
    if (t == 0)
    {
        visible = 0;
    }
    if (t == 1)
    {
        visible = 1;
    }
}
int turn_identifier (int x)
{
    sleep(5);
    if (x==1 || x==4 || x==6 || x==7 || x==9 || x==12 || x==14 || x==15 || x==17 || x==20 || x==22 || x==23 || x==25 || x==28 || x==30 || x==31)
    {
        printf("it's Detective's turn\n\n");
        return 0;
    }
    else
    {
        printf("it's Jack's turn\n\n");
        return 1;
    }
    sleep(5);
}
void four_card (int x)
{
    sleep(3);
    int r,i=0;
    if (x == 1)
    {
        printf("4 cards for the round are :\n");
        while (i != 4)
        {
            r = rand();
            r = r%8;
            if (cards[r] == 0)
            {
                cards[r] = 1;
                i++;
            }
        }
    }
    if (x == 2)
    {
        printf("The remaining 3 cards are : \n");
    }
    if (x == 3)
    {
        printf("The remaining 2 cards are : \n");
    }
    if (x == 4)
    {
        printf("The remaining card is : \n");
    }
    sleep(5);
    i=1;
    if (cards[0] == 1)
    {
        printf("%d - Sherlock Holmes   aka   SH\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : Pick a card\t\t\t\t\t\t");
        printf("Ability turn : After Movement\n");
        i++;
        sleep(3);
    }
    if (cards[1] == 1)
    {
        printf("%d - John Watson   aka   JW\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : flashlight\t\t\t\t\t\t");
        printf("Ability turn : After Movement\n");
        i++;
        sleep(3);
    }
    if (cards[2] == 1)
    {
        printf("%d - John Smith   aka   JS\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : Move a lamp to a off lamp\t\t\t\t");
        printf("Ability turn : Before or After Movement\n");
        i++;
        sleep(3);
    }
    if (cards[3] == 1)
    {
        printf("%d - Inspector Lestrade   aka   IL\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : Move a gate block to another gate\t\t\t");
        printf("Ability turn : Before or After Movement\n");
        i++;
        sleep(3);
    }
    if (cards[4] == 1)
    {
        printf("%d - Miss Stealthy   aka   MS\t\t",i);
        printf("Movement : 1-4\t\t");
        printf("Ability : can move through houses\t\t\t\t");
        printf("Ability turn : with Movement\n");
        i++;
        sleep(3);
    }
    if (cards[5] == 1)
    {
        printf("%d - Sergeant Goodley   aka   SG\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : move Maximum 3 Charecter 3 places in total\t\t");
        printf("Ability turn : Before or After Movement\n");
        i++;
        sleep(3);
    }
    if (cards[6] == 1)
    {
        printf("%d - William Gull   aka   WG\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : Change his place with another Character\t\t");
        printf("Ability turn : Ability or Movement\n");
        i++;
        sleep(3);
    }
    if (cards[7] == 1)
    {
        printf("%d - Jeremy Bert   aka   JB\t\t",i);
        printf("Movement : 1-3\t\t");
        printf("Ability : Move a hole block to another hole\t\t\t");
        printf("Ability turn : Before or After Movement\n");
        i++;
        sleep(3);
    }
    printf("\n");
}
void SH ()///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int x,y,i,r;
    printf("Choose where you want to go : ");
    scanf("%d %d",&x,&y);
    if (jack_id == 1 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
    {
        victory = 1;
        return;
    }
    if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
    {
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
        {
            if (jack_id == 1)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
        {
            if (jack_id == 2)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 3)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
        {
            if (jack_id == 4)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 5)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 6)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 7)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
        {
            if (jack_id == 8)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
    }
    map[coords_x[0]-1][coords_y[0]-1].condition[0] = 'N';
    map[coords_x[0]-1][coords_y[0]-1].condition[1] = '\0';
    map[x-1][y-1].condition[0] = 'S';
    map[x-1][y-1].condition[1] = 'H';
    map[x-1][y-1].condition[2] = '\0';
    coords_x[0] = x;
    coords_y[0] = y;
    printf("Now your ability\n");
    sleep(3);
    if (SH_cards_t != 0)
    {
        if (turn == 1)
        {
            printf("Detective Do not look at the monitor\n");
        }
        if (turn == 0)
        {
            printf("Jack Do not look at the monitor\n");
        }
        sleep(5);
        printf("one of the innocent people is : \n");
        sleep(3);
        printf(".\n");
        sleep(3);
        printf(".\n");
        sleep(3);
        printf(".\n");
        sleep(3);
    }
    if (SH_cards_t == 1)
    {
        for (i=0;i<8;i++)
        {
            if (SH_cards[i] == 0)
            {
                SH_cards[i] = 1;
                if (i == 0)
                {
                    printf("Sherlock Holmes   aka   SH\n");
                }
                if (i == 1)
                {
                    printf("John Watson   aka   JW\n");
                }
                if (i == 2)
                {
                    printf("John Smith   aka   JS\n");
                }
                if (i == 3)
                {
                    printf("Inspector Lestrade   aka   IL\n");
                }
                if (i == 4)
                {
                    printf("Miss Stealthy   aka   MS\n");
                }
                if (i == 5)
                {
                    printf("Sergeant Goodley   aka   SG\n");
                }
                if (i == 6)
                {
                    printf("William Gull   aka   WG\n");
                }
                if (i == 7)
                {
                    printf("Jeremy Bert   aka   JB\n");
                }
                break;
            }
        }
    }
    else if (SH_cards_t == 0)
    {
        printf("there is no card left\n");
    }
    else
    {
        while (1 == 1)
        {
            r = rand();
            r = r%8;
            if (SH_cards[r] == 0)
            {
                SH_cards[r] = 1;
                if (r == 0)
                {
                    printf("Sherlock Holmes   aka   SH\n");
                }
                if (r == 1)
                {
                    printf("John Watson   aka   JW\n");
                }
                if (r == 2)
                {
                    printf("John Smith   aka   JS\n");
                }
                if (r == 3)
                {
                    printf("Inspector Lestrade   aka   IL\n");
                }
                if (r == 4)
                {
                    printf("Miss Stealthy   aka   MS\n");
                }
                if (r == 5)
                {
                    printf("Sergeant Goodley   aka   SG\n");
                }
                if (r == 6)
                {
                    printf("William Gull   aka   WG\n");
                }
                if (r == 7)
                {
                    printf("Jeremy Bert   aka   JB\n");
                }
                break;
            }
        }
    }
    cards[0] = 2;
    sleep(3);
}
void JW ()/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int x,y;
    printf("Choose where you want to go : ");
    scanf("%d %d",&x,&y);
    if (jack_id == 2 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
    {
        victory = 1;
        return;
    }
    if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
    {
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
        {
            if (jack_id == 1)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
        {
            if (jack_id == 2)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 3)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
        {
            if (jack_id == 4)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 5)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 6)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 7)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
        {
            if (jack_id == 8)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
    }
    map[coords_x[1]-1][coords_y[1]-1].condition[0] = 'N';
    map[coords_x[1]-1][coords_y[1]-1].condition[1] = '\0';
    map[x-1][y-1].condition[0] = 'J';
    map[x-1][y-1].condition[1] = 'W';
    map[x-1][y-1].condition[2] = '\0';
    coords_x[1] = x;
    coords_y[1] = y;
    printf("Now your ability\n");
    printf("Choose which side you want to point your flashlight : \n");
    printf("1- top\t\t2- top right\t\t3- bottom right\t\t4- bottom\t\t5- bottom left\t\t6- top left \n");
    scanf("%d",&flashlight);
    cards[1] = 2;
    sleep(3);
}
void JS ()/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a,x,y,x1,x2,y1,y2,q,i;
    printf("you want to move first or do your ability ?\n");
    printf("1- Move\t\t\t");
    printf("2- ability\n");
    scanf("%d",&a);
    if (a == 1)
    {
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 3 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[2]-1][coords_y[2]-1].condition[0] = 'N';
        map[coords_x[2]-1][coords_y[2]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'J';
        map[x-1][y-1].condition[1] = 'S';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[2] = x;
        coords_y[2] = y;
        printf("Now your ability\n");
        printf("Choose which lamp you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which off lamp you want to turn on : ");
        scanf("%d %d",&x2,&y2);
        for (i=0;i<5;i++)
        {
            q = map[x1-1][y1-1].condition[i];
            map[x1-1][y1-1].condition[i] = map[x2-1][y2-1].condition[i];
            map[x2-1][y2-1].condition[i] = q;
        }
    }
    if (a == 2)
    {
        printf("Choose which lamp you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which off lamp you want to turn on : ");
        scanf("%d %d",&x2,&y2);
        for (i=0;i<5;i++)
        {
            q = map[x1-1][y1-1].condition[i];
            map[x1-1][y1-1].condition[i] = map[x2-1][y2-1].condition[i];
            map[x2-1][y2-1].condition[i] = q;
        }
        printf("Now your move\n");
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 3 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[2]-1][coords_y[2]-1].condition[0] = 'N';
        map[coords_x[2]-1][coords_y[2]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'J';
        map[x-1][y-1].condition[1] = 'S';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[2] = x;
        coords_y[2] = y;
    }
    cards[2] = 2;
    sleep(3);
}
void IL ()///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a,x,y,x1,x2,y1,y2;
    printf("you want to move first or do your ability ?\n");
    printf("1- Move\t\t\t");
    printf("2- ability\n");
    scanf("%d",&a);
    if (a == 1)
    {
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 4 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[3]-1][coords_y[3]-1].condition[0] = 'N';
        map[coords_x[3]-1][coords_y[3]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'I';
        map[x-1][y-1].condition[1] = 'L';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[3] = x;
        coords_y[3] = y;
        printf("Now your ability\n");
        printf("Choose which gate block you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which gate you want to block : ");
        scanf("%d %d",&x2,&y2);
        map[x1-1][y1-1].condition[0] = 'O';
        map[x2-1][y2-1].condition[0] = 'C';
    }
    if (a == 2)
    {
        printf("Choose which gate block you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which gate you want to block : ");
        scanf("%d %d",&x2,&y2);
        map[x1-1][y1-1].condition[0] = 'O';
        map[x2-1][y2-1].condition[0] = 'C';
        printf("Now your move\n");
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 4 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[3]-1][coords_y[3]-1].condition[0] = 'N';
        map[coords_x[3]-1][coords_y[3]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'I';
        map[x-1][y-1].condition[1] = 'L';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[3] = x;
        coords_y[3] = y;
    }
    cards[3] = 2;
    sleep(3);
}
void MS ()///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int x,y;
    printf("Choose where you want to go : ");
    scanf("%d %d",&x,&y);
    if (jack_id == 5 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
    {
        victory = 1;
        return;
    }
    if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
    {
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
        {
            if (jack_id == 1)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
        {
            if (jack_id == 2)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 3)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
        {
            if (jack_id == 4)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
        {
            if (jack_id == 5)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 6)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
        {
            if (jack_id == 7)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
        if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
        {
            if (jack_id == 8)
            {
                victory = 0;
                return;
            }
            else
            {
                victory = 1;
                return;
            }
        }
    }
    map[coords_x[4]-1][coords_y[4]-1].condition[0] = 'N';
    map[coords_x[4]-1][coords_y[4]-1].condition[1] = '\0';
    map[x-1][y-1].condition[0] = 'M';
    map[x-1][y-1].condition[1] = 'S';
    map[x-1][y-1].condition[2] = '\0';
    coords_x[4] = x;
    coords_y[4] = y;
    cards[4] = 2;
    sleep(3);
}
void SG ()////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a,x,y,n,m,i,x1,y1,x2,y2;
    printf("you want to move first or do your ability ?\n");
    printf("1- Move\t\t\t");
    printf("2- ability\n");
    scanf("%d",&a);
    if (a == 1)
    {
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 6 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[5]-1][coords_y[5]-1].condition[0] = 'N';
        map[coords_x[5]-1][coords_y[5]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'S';
        map[x-1][y-1].condition[1] = 'G';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[5] = x;
        coords_y[5] = y;
        printf("Now your ability\n");
        printf("how many character you want to move ? (1 or 2 or 3)\n");
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            printf("Choose a Character to move it : \n");
            printf("1- SH\t2- JW\t3- JS\t4- IL\t5- MS\t6- WG\t7- JB \n");
            scanf("%d",&m);
            printf("where you want to move it : ");
            scanf("%d %d",&x1,&y1);
            if (m == 1)
            {
                map[coords_x[0]-1][coords_y[0]-1].condition[0] = 'N';
                map[coords_x[0]-1][coords_y[0]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'S';
                map[x1-1][y1-1].condition[1] = 'H';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[0];
                y2 = coords_y[0];
                coords_x[0] = x1;
                coords_y[0] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 2)
            {
                map[coords_x[1]-1][coords_y[1]-1].condition[0] = 'N';
                map[coords_x[1]-1][coords_y[1]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'W';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[1];
                y2 = coords_y[1];
                coords_x[1] = x1;
                coords_y[1] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 3)
            {
                map[coords_x[2]-1][coords_y[2]-1].condition[0] = 'N';
                map[coords_x[2]-1][coords_y[2]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'S';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[2];
                y2 = coords_y[2];
                coords_x[2] = x1;
                coords_y[2] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 4)
            {
                map[coords_x[3]-1][coords_y[3]-1].condition[0] = 'N';
                map[coords_x[3]-1][coords_y[3]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'I';
                map[x1-1][y1-1].condition[1] = 'L';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[3];
                y2 = coords_y[3];
                coords_x[3] = x1;
                coords_y[3] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 5)
            {
                map[coords_x[4]-1][coords_y[4]-1].condition[0] = 'N';
                map[coords_x[4]-1][coords_y[4]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'M';
                map[x1-1][y1-1].condition[1] = 'S';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[4];
                y2 = coords_y[4];
                coords_x[4] = x1;
                coords_y[4] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 6)
            {
                map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'N';
                map[coords_x[6]-1][coords_y[6]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'W';
                map[x1-1][y1-1].condition[1] = 'G';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[6];
                y2 = coords_y[6];
                coords_x[6] = x1;
                coords_y[6] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 7)
            {
                map[coords_x[7]-1][coords_y[7]-1].condition[0] = 'N';
                map[coords_x[7]-1][coords_y[7]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'B';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[7];
                y2 = coords_y[7];
                coords_x[7] = x1;
                coords_y[7] = y1;
                x1 = x2;
                y1 = y2;
            }
        }
    }
    if (a == 2)
    {
        printf("how many character you want to move ? (1 or 2 or 3)\n");
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            printf("Choose a Character to move it : \n");
            printf("1- SH\t2- JW\t3- JS\t4- IL\t5- MS\t6- WG\t7- JB \n");
            scanf("%d",&m);
            printf("where you want to move it : ");
            scanf("%d %d",&x1,&y1);
            if (m == 1)
            {
                map[coords_x[0]-1][coords_y[0]-1].condition[0] = 'N';
                map[coords_x[0]-1][coords_y[0]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'S';
                map[x1-1][y1-1].condition[1] = 'H';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[0];
                y2 = coords_y[0];
                coords_x[0] = x1;
                coords_y[0] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 2)
            {
                map[coords_x[1]-1][coords_y[1]-1].condition[0] = 'N';
                map[coords_x[1]-1][coords_y[1]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'W';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[1];
                y2 = coords_y[1];
                coords_x[1] = x1;
                coords_y[1] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 3)
            {
                map[coords_x[2]-1][coords_y[2]-1].condition[0] = 'N';
                map[coords_x[2]-1][coords_y[2]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'S';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[2];
                y2 = coords_y[2];
                coords_x[2] = x1;
                coords_y[2] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 4)
            {
                map[coords_x[3]-1][coords_y[3]-1].condition[0] = 'N';
                map[coords_x[3]-1][coords_y[3]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'I';
                map[x1-1][y1-1].condition[1] = 'L';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[3];
                y2 = coords_y[3];
                coords_x[3] = x1;
                coords_y[3] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 5)
            {
                map[coords_x[4]-1][coords_y[4]-1].condition[0] = 'N';
                map[coords_x[4]-1][coords_y[4]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'M';
                map[x1-1][y1-1].condition[1] = 'S';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[4];
                y2 = coords_y[4];
                coords_x[4] = x1;
                coords_y[4] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 6)
            {
                map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'N';
                map[coords_x[6]-1][coords_y[6]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'W';
                map[x1-1][y1-1].condition[1] = 'G';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[6];
                y2 = coords_y[6];
                coords_x[6] = x1;
                coords_y[6] = y1;
                x1 = x2;
                y1 = y2;
            }
            if (m == 7)
            {
                map[coords_x[7]-1][coords_y[7]-1].condition[0] = 'N';
                map[coords_x[7]-1][coords_y[7]-1].condition[1] = '\0';
                map[x1-1][y1-1].condition[0] = 'J';
                map[x1-1][y1-1].condition[1] = 'B';
                map[x1-1][y1-1].condition[2] = '\0';
                x2 = coords_x[7];
                y2 = coords_y[7];
                coords_x[7] = x1;
                coords_y[7] = y1;
                x1 = x2;
                y1 = y2;
            }
        }
        printf("Now your move\n");
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 6 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[5]-1][coords_y[5]-1].condition[0] = 'N';
        map[coords_x[5]-1][coords_y[5]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'S';
        map[x-1][y-1].condition[1] = 'G';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[5] = x;
        coords_y[5] = y;
    }
    cards[5] = 2;
    sleep(3);
}
void WG ()//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a,x,y,n,x1,y1;
    printf("you want to move or do your ability ?\n");
    printf("1- Move\t\t\t");
    printf("2- ability\n");
    scanf("%d",&a);
    if (a == 1)
    {
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 7 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'N';
        map[coords_x[6]-1][coords_y[6]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'W';
        map[x-1][y-1].condition[1] = 'G';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[6] = x;
        coords_y[6] = y;
    }
    if (a == 2)
    {
        printf("Choose a Character to change place with : \n");
        printf("1- SH\t2- JW\t3- JS\t4- IL\t5- MS\t6- SG\t7- JB \n");
        scanf("%d",&n);
        if (n == 1)
        {
            x1 = coords_x[0];
            y1 = coords_y[0];
            coords_x[0] = coords_x[6];
            coords_y[0] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[0]-1][coords_y[0]-1].condition[0] = 'S';
            map[coords_x[0]-1][coords_y[0]-1].condition[1] = 'H';
        }
        if (n == 2)
        {
            x1 = coords_x[1];
            y1 = coords_y[1];
            coords_x[1] = coords_x[6];
            coords_y[1] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[1]-1][coords_y[1]-1].condition[0] = 'J';
            map[coords_x[1]-1][coords_y[1]-1].condition[1] = 'W';
        }
        if (n == 3)
        {
            x1 = coords_x[2];
            y1 = coords_y[2];
            coords_x[2] = coords_x[6];
            coords_y[2] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[2]-1][coords_y[2]-1].condition[0] = 'J';
            map[coords_x[2]-1][coords_y[2]-1].condition[1] = 'S';
        }
        if (n == 4)
        {
            x1 = coords_x[3];
            y1 = coords_y[3];
            coords_x[3] = coords_x[6];
            coords_y[3] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[3]-1][coords_y[3]-1].condition[0] = 'I';
            map[coords_x[3]-1][coords_y[3]-1].condition[1] = 'L';
        }
        if (n == 5)
        {
            x1 = coords_x[4];
            y1 = coords_y[4];
            coords_x[4] = coords_x[6];
            coords_y[4] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[4]-1][coords_y[4]-1].condition[0] = 'M';
            map[coords_x[4]-1][coords_y[4]-1].condition[1] = 'S';
        }
        if (n == 6)
        {
            x1 = coords_x[5];
            y1 = coords_y[5];
            coords_x[5] = coords_x[6];
            coords_y[5] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[5]-1][coords_y[5]-1].condition[0] = 'S';
            map[coords_x[5]-1][coords_y[5]-1].condition[1] = 'G';
        }
        if (n == 7)
        {
            x1 = coords_x[7];
            y1 = coords_y[7];
            coords_x[7] = coords_x[6];
            coords_y[7] = coords_y[6];
            coords_x[6] = x1;
            coords_y[6] = y1;
            map[coords_x[6]-1][coords_y[6]-1].condition[0] = 'W';
            map[coords_x[6]-1][coords_y[6]-1].condition[1] = 'G';
            map[coords_x[7]-1][coords_y[7]-1].condition[0] = 'J';
            map[coords_x[7]-1][coords_y[7]-1].condition[1] = 'B';
        }
    }
    cards[6] = 2;
    sleep(3);
}
void JB ()//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a,x,y,x1,x2,y1,y2;
    printf("you want to move first or do your ability ?\n");
    printf("1- Move\t\t\t");
    printf("2- ability\n");
    scanf("%d",&a);
    if (a == 1)
    {
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 8 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[7]-1][coords_y[7]-1].condition[0] = 'N';
        map[coords_x[7]-1][coords_y[7]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'J';
        map[x-1][y-1].condition[1] = 'B';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[7] = x;
        coords_y[7] = y;
        printf("Now your ability\n");
        printf("Choose which hole block you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which hole you want to block : ");
        scanf("%d %d",&x2,&y2);
        map[x1-1][y1-1].condition[0] = 'O';
        map[x2-1][y2-1].condition[0] = 'C';
    }
    if (a == 2)
    {
        printf("Choose which hole block you want to move : ");
        scanf("%d %d",&x1,&y1);
        printf("Choose which hole you want to block : ");
        scanf("%d %d",&x2,&y2);
        map[x1-1][y1-1].condition[0] = 'O';
        map[x2-1][y2-1].condition[0] = 'C';
        printf("Now your move\n");
        printf("Choose where you want to go : ");
        scanf("%d %d",&x,&y);
        if (jack_id == 8 && visible == 0 && map[x-1][y-1].type == 4 && map[x-1][y-1].condition[0] == 'O')
        {
            victory = 1;
            return;
        }
        if (turn == 0 && map[x-1][y-1].type == 0 && map[x-1][y-1].condition[0] != 'N')
        {
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'H')
            {
                if (jack_id == 1)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'W')
            {
                if (jack_id == 2)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 3)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'I' && map[x-1][y-1].condition[1] == 'L')
            {
                if (jack_id == 4)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'M' && map[x-1][y-1].condition[1] == 'S')
            {
                if (jack_id == 5)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'S' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 6)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'W' && map[x-1][y-1].condition[1] == 'G')
            {
                if (jack_id == 7)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
            if (map[x-1][y-1].condition[0] == 'J' && map[x-1][y-1].condition[1] == 'B')
            {
                if (jack_id == 8)
                {
                    victory = 0;
                    return;
                }
                else
                {
                    victory = 1;
                    return;
                }
            }
        }
        map[coords_x[7]-1][coords_y[7]-1].condition[0] = 'N';
        map[coords_x[7]-1][coords_y[7]-1].condition[1] = '\0';
        map[x-1][y-1].condition[0] = 'J';
        map[x-1][y-1].condition[1] = 'B';
        map[x-1][y-1].condition[2] = '\0';
        coords_x[7] = x;
        coords_y[7] = y;
    }
    cards[7] = 2;
    sleep(3);
}
void action ()
{
    int a,n,i,m=0;
    if (turn == 1)
    {
        printf("Jack pick a card : \n");
    }
    if (turn == 0)
    {
        printf("Detective pick a card : \n");
    }
    scanf("%d",&n);
    if (n == 1)
    {
        for (i=0;i<8;i++)
        {
            if (cards[i] == 1)
            {
                a = i+1;
                break;
            }
        }
    }
    if (n == 2)
    {
        for (i=0;i<8;i++)
        {
            if (cards[i] == 1)
            {
                m++;
            }
            if (m == 2)
            {
                a = i+1;
                break;
            }
        }
    }
    if (n == 3)
    {
        for (i=0;i<8;i++)
        {
            if (cards[i] == 1)
            {
                m++;
            }
            if (m == 3)
            {
                a = i+1;
                break;
            }
        }
    }
    if (n == 4)
    {
        for (i=0;i<8;i++)
        {
            if (cards[i] == 1)
            {
                m++;
            }
            if (m == 4)
            {
                a = i+1;
                break;
            }
        }
    }
    if (a == 1)
    {
        SH();
        cards[0] = 2;
    }
    if (a == 2)
    {
        JW();
        cards[1] = 2;
    }
    if (a == 3)
    {
        JS();
        cards[2] = 2;
    }
    if (a == 4)
    {
        IL();
        cards[3] = 2;
    }
    if (a == 5)
    {
        MS();
        cards[4] = 2;
    }
    if (a == 6)
    {
        SG();
        cards[5] = 2;
    }
    if (a == 7)
    {
        WG();
        cards[6] = 2;
    }
    if (a == 8)
    {
        JB();
        cards[7] = 2;
    }
    system("cls");
}
void End_Game ()
{
    system("cls");
    if (victory == 0)
    {
        printf("Detective wins\n");
    }
    if (victory == 1)
    {
        printf("Jack wins\n");
        printf("the identity of Jack was : \n");
        if (jack_id == 1)
        {
            printf("Sherlock Holmes   aka   SH\n");
        }
        if (jack_id == 2)
        {
            printf("John Watson   aka   JW\n");
        }
        if (jack_id == 3)
        {
            printf("John Smith   aka   JS\n");
        }
        if (jack_id == 4)
        {
            printf("Inspector Lestrade   aka   IL\n");
        }
        if (jack_id == 5)
        {
            printf("Miss Stealthy   aka   MS\n");
        }
        if (jack_id == 6)
        {
            printf("Sergeant Goodley   aka   SG\n");
        }
        if (jack_id == 7)
        {
        printf("William Gull   aka   WG\n");
        }
        if (jack_id == 8)
        {
            printf("Jeremy Bert   aka   JB\n");
        }
    }
}
int main()
{
    int i,j,k,q=0;
    time_t t = time(NULL);
    srand(t);
    welcom();
    jack_identity();
    reed_map();
    for (i=0;i<8;i++)
    {
        for (j=0;j<4;j++)
        {
            show_map();
            turn = turn_identifier(4*i + j + 1);
            four_card(j+1);
            action();
            if (victory != 2)
            {
                q=1;
                break;
            }
        }
        if (q == 1)
        {
            break;
        }
        round++;
        jack_visible();
        if (i == 0)
        {
            for (j=0;j<9;j++)
            {
                for (k=0;k<13;k++)
                {
                    if (map[j][k].type == 3 && strlen(map[j][k].condition) == 1 && map[j][k].condition[0] == 'r')
                    {
                        map[j][k].condition[0] = 'O';
                        map[j][k].condition[1] = '\0';
                        map[j][k].condition[2] = '\0';
                        map[j][k].condition[3] = '\0';
                        map[j][k].condition[4] = '\0';
                    }
                }
            }
        }
        if (i == 1)
        {
            for (j=0;j<9;j++)
            {
                for (k=0;k<13;k++)
                {
                    if (map[j][k].type == 3 && strlen(map[j][k].condition) == 2)
                    {
                        map[j][k].condition[0] = 'O';
                        map[j][k].condition[1] = '\0';
                    }
                }
            }
        }
        if (i == 2)
        {
            for (j=0;j<9;j++)
            {
                for (k=0;k<13;k++)
                {
                    if (map[j][k].type == 3 && strlen(map[j][k].condition) == 3)
                    {
                        map[j][k].condition[0] = 'O';
                        map[j][k].condition[1] = '\0';
                    }
                }
            }
        }
        if (i == 3)
        {
            for (j=0;j<9;j++)
            {
                for (k=0;k<13;k++)
                {
                    if (map[j][k].type == 3 && strlen(map[j][k].condition) == 4)
                    {
                        map[j][k].condition[0] = 'O';
                        map[j][k].condition[1] = '\0';
                    }
                }
            }
        }
        if (i%2 == 1)
        {
            for (k=0;k<8;k++)
            {
                cards[k] = 0;
            }
        }
        if (i == 7)
        {
            victory = 1;
        }
    }
    End_Game();
    return 0;
}
