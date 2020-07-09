#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>



#define width 120
#define height 30

typedef	struct	S_object
{
	float		x;
	float		y;
	float		owidth;
	float		oheight;
	float		vertSpeed;
	BOOL		isFly;
}				T_object;

BOOL	isPosInMap(int x, int y);
BOOL	isCol(T_object t1, T_object t2);
void Init_obj(T_object	*obj, float xPos, float yPos, float o_width, float o_height);

T_object	mario;
T_object	*brick = NULL;
int			brickLength;
char		mas[height][width + 1];

void		createLevel()
{
	Init_obj(&mario, 59, 10, 3, 3);

	brickLength = 5;
	brick = (T_object*) malloc(sizeof(T_object) * brickLength);
	Init_obj(brick + 0, 40, 25, 40, 5);
	Init_obj(brick + 1, 80, 15, 10, 10);
	Init_obj(brick + 2, 100, 20, 20, 5);
	Init_obj(brick + 3, 140, 15, 10, 10);
	Init_obj(brick + 4, 170, 20, 40, 5);
}

void	set_object_pos(T_object *obj, float xPos, float yPos)
{
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void Init_obj(T_object	*obj, float xPos, float yPos, float o_width, float o_height)
{
	set_object_pos(obj, xPos, yPos);
	(*obj).owidth = o_width;
	(*obj).oheight = o_height;
	(*obj).vertSpeed = 0;
}

void	vertMoveObject(T_object *obj)
{
	(*obj).isFly = TRUE;
	(*obj).vertSpeed += 0.05;
	set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
	if (isCol(*obj, brick[0]))
	{
		(*obj).y -= (*obj).vertSpeed;
		(*obj).vertSpeed = 0;
		(*obj).isFly = FALSE;
	}
}

void	put_obj_onmap(T_object	obj)
{
	int i;
	int j;

	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iwidth = (int)round(obj.owidth);
	int iheight = (int)round(obj.oheight);
	i = ix;
	j = iy;

	while (i < ix + iwidth)
	{
		while (j < iy + iheight)
		{

			if (isPosInMap(i, j))
				mas[j][i] = '@';
			j++;
		}
		j = iy;
		i++;
	}
}

void	init()
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < height)
	{
		while (j < width)
		{
			if (i == 0 || j == 0 || j == width - 1 || i == height - 1)
				mas[i][j] = '#';
			else
				mas[i][j] = ' ';
			j++;
		}
		mas[i][j] = '\0';
		j = 0;
		i++;
	}
}

void 	show_Map()
{
	int 	i;
	i = 0;
	while (i < height)
	{
		printf("%s", mas[i]);
		printf("\n");
		i++;
	}
}

void	setcur(int x, int y)
{
	COORD	coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

BOOL	isPosInMap(int x, int y)
{
	return	((x >= 0) && (x < width) && (y >= 0) && (y < height));
}

BOOL	isCol(T_object t1, T_object t2)
{
	return ((t1.x + t1.owidth) > t2.x && (t2.x + t2.owidth) > t1.x &&
		(t1.y + t1.oheight) > t2.y && (t2.y + t2.oheight) > t1.y);
}

void	horMoveMap(float dx)
{
	brick[0].x += dx;
}

int		main(void)
{
	BOOL	run;
	int		i;

	run = TRUE;
	i = 0;
	createLevel();
	while (run)
	{
		setcur(0, 0);
		init();
		if (mario.isFly == FALSE && GetKeyState(VK_SPACE) < 0)
			mario.vertSpeed = -0.9;
		if (GetKeyState('A') < 0)
			horMoveMap(-1);
		if (GetKeyState('D') < 0)
			horMoveMap(1);
		vertMoveObject(&mario);
		put_obj_onmap(mario);
		while (i < brickLength)
		{
			put_obj_onmap(brick[i]);
			i++;
		}
		Sleep(10);
		show_Map();
		if (GetKeyState(VK_ESCAPE) < 0)
			run = FALSE;
	}
		return (0);
}
