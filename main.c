#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <dos.h>

#define white "\033[37;47m"
#define	black "\033[30;40m"
#define	redback "\033[41m"
#define	redfont "\033[31m"
#define	greenback "\033[42m"
#define	greenfont "\033[32m"
#define	yellowback "\033[43m"
#define	yellowfont "\033[33m"
#define	blueback "\033[44m"
#define	bluefont "\033[34m"
#define reset "\033[0m"

#define w 40
#define h 10000
#define ph 15

bool gamestate = true;

void mapgen(void);
void obstaclegen(void);
void draw(void);
void copymap(void);
void colorload(void);
void hidecursor(void);
void gameover(void);


int x;
int y;
int zx = 0;
int zy = 0;
int count = 0;
int key;

int map[h][w];
int print_map[ph][w];

int main() {
    int a = 0;
    int b = w/2;
    srand(time(NULL));
    
    mapgen();
    obstaclegen();
    
    hidecursor();
    mainscreen();
    getchar();
    copymap();    
    print_map[1][b] = 3;
    
    colorload();    
    	
    while( gamestate == true)
    {
    	system("@cls||clear");
        copymap();
          
		if(GetKeyState(VK_LEFT) & 0x8000) 
		{	
			b -= 1;
		}
		else if(GetKeyState(VK_RIGHT) & 0x8000) 
		{
			b += 1;
		}
        print_map[1][b] = 3;
        draw();
        
		if(print_map[2][b] == 1 || print_map[2][b] == 4) gameover();  
		     
        }
    return 0;
}

void mainscreen()
{
	printf("welcome to \n\n");
	printf("######     #    ### #     # ######  ####### #     #    ######  #     # #     # #     # ####### ######\n#     #   # #    #  ##    # #     # #     # #  #  #    #     # #     # ##    # ##    # #       #     #\n#     #  #   #   #  # #   # #     # #     # #  #  #    #     # #     # # #   # # #   # #       #     #\n######  #     #  #  #  #  # ######  #     # #  #  #    ######  #     # #  #  # #  #  # #####   ######\n#   #   #######  #  #   # # #     # #     # #  #  #    #   #   #     # #   # # #   # # #       #   #\n#    #  #     #  #  #    ## #     # #     # #  #  #    #    #  #     # #    ## #    ## #       #    #\n#     # #     # ### #     # ######  #######  ## ##     #     #  #####  #     # #     # ####### #     #\n");
	printf("\n\nPress Space to Start");
}

void colorload()
{
	int i = 0;
	while(i < 5)
    	{
    		system("@cls||clear");
    		draw();
    		i++;
		}
}

void mapgen()
{
    int z = 0;
    for(x = 0; x < h; x++)
    {
        for(y = 0; y < w; y++)
        {
            if(x == 0)
            {
                z = w/4;
                if(y == z)
                {
                    map[x][y] = 1;
                    map[x][y + z*2] = 1;
                }
            }
            if(y == 0 || y == w - 1)
            {
                map[x][y] = 2;
            }
            
            if(x >= 1)
            {
                if(map[x-1][y] == 1 && y < w/2-1)
                {
                    if(y == 1 )								// right wall detection	
                    {
                        map[x][y + 1] = 1;
                        map[x][y + z * 2] = 1;
                    }
                    else if (y == w / 2 - 2)					// left wall detection
                    {
                        map[x][y - 1] = 1;
                        map[x][y + z * 2] = 1;
                    }
                    else										
                    {
                        map[x][y + (rand() % 3) - 1] = 1;
                        map[x][y + z * 2] = 1; 
                    }
                }
            }
        }
    }
}

void obstaclegen()
{
	int i = 0;
	int j = 0; 
    for(x = 5; x < h; x++)
    {
        for(y = 0; y < w; y++)
        {
        	if(map[x][y] == 1 && y < w / 2 - 1)
			{
				j = rand() % 2;
				if(j == 1)
				{	
					i = rand() % w / 2;
					if(i > 0 && i < w / 2) map[x][y + i] = 4;
				}
			}
		}
	}
}

void copymap()
{
    for(x = 0; x < ph; x++)
    {
        for(y = 0; y < w; y++)
        {
                print_map[x][y] = map[x + zx][y];
        }
        
    }
    zx++;
}

void draw()
{
    for(x = 0; x < ph; x++)
    {
        for(y = 0; y < w; y++)
        {
        	
        	if(print_map[x][y] == 0) printf(black "0" reset);
            if(print_map[x][y] == 1) printf(white "1" reset);
            if(print_map[x][y] == 2) printf(white "2" reset);
            if(print_map[x][y] == 3) printf(redback redfont "3" reset);
            switch(rand() % 4){
            	case 0:
            		if(print_map[x][y] == 4) printf(greenback greenfont "4" reset);
            		break;
            	case 1:
            		if(print_map[x][y] == 4) printf(redback redfont "4" reset);
            		break;
            	case 2:
            		if(print_map[x][y] == 4) printf(blueback bluefont "4" reset);
            		break;
            	case 3:
            		if(print_map[x][y] == 4) printf(yellowback yellowfont "4" reset);
            		break;
			} 	        	
        }
        printf("\n");
    }
}

void gameover()
{
	printf("\n\n");
	printf(" #####     #    #     # #######    ####### #     # ####### ######\n#     #   # #   ##   ## #          #     # #     # #       #     #\n#        #   #  # # # # #          #     # #     # #       #     #\n#  #### #     # #  #  # #####      #     # #     # #####   ###### \n#     # ####### #     # #          #     #  #   #  #       #   #  \n#     # #     # #     # #          #     #   # #   #       #    # \n #####  #     # #     # #######    #######    #    ####### #     #\n");
	printf("\n\tDein Score ist: %d",zx);
	getchar();
	
	return 0;
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

