#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>

int map[16][16] = {
   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0 },
   { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0 },
   { 0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0 },
   { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0 },
   { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0 },
   { 0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0 },
   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,1,0,0,0,1,1,0,0,1,1,1,0,1,1,0 },
   { 0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0 },
   { 0,1,0,0,0,0,1,0,0,1,1,0,1,1,1,0 },
   { 0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0 },
   { 0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0 },
   { 0,1,0,0,0,0,1,0,0,1,0,1,1,1,1,0 },
   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};
int hus_m;
int hus_n;
int wife_m;
int wife_n;
int pub_m;
int pub_n;
int home_m;
int home_n;
int mode; // 함수내에서 몇사분면인지 나타냄
int meet_flag = 0; // 
int first_out;
int last_in;
int end_flag = 0;


void show()
{
	int i;
	int j;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (map[i][j] == 0)
				printf("  ");
			else if (map[i][j] == 1)
				printf("■");
			else if (map[i][j] == 2)
				printf("ⓟ");
			else if (map[i][j] == 3)
				printf("ⓗ");
			else if (map[i][j] == 4)
				printf("ⓜ");
			else if (map[i][j] == 5)
				printf("ⓦ");
		}
		printf("\n");
	}
}


void wife_step()
{
	int random = rand() % 4;
	int wife1_m = wife_m;
	int wife1_n = wife_n;
	if (meet_flag == 0 && first_out == 1)
	{
		if (mode == 0)
		{
			if (random == 0)
				wife_m++;
			else if (random == 1)
				wife_m--;
			else if (random == 2)
				wife_n++;
			else if (random == 3)
				wife_n--;
			if (wife_n > 15 || wife_n < 0 || wife_m > 15 || wife_m < 8 || wife_n < 8 || map[wife_m][wife_n] == 1 || map[wife_m][wife_n] == 3)
			{
				wife_m = wife1_m;
				wife_n = wife1_n;
			}
		}
		else if (mode == 1)
		{
			if (random == 0)
				wife_m++;
			else if (random == 1)
				wife_m--;
			else if (random == 2)
				wife_n++;
			else if (random == 3)
				wife_n--;
			if (wife_n > 15 || wife_n < 0 || wife_m > 15 || wife_m < 8 || wife_n > 7 || map[wife_m][wife_n] == 1 || map[wife_m][wife_n] == 3)
			{
				wife_m = wife1_m;
				wife_n = wife1_n;
			}
		}
		map[wife1_m][wife1_n] = 0;
		map[wife_m][wife_n] = 5;
	}
	else if (meet_flag == 1)
	{
		return;
	}
}

int hus_step()
{
	int hus1_m = hus_m;
	int hus1_n = hus_n;
	if (meet_flag == 0)
	{
		if (rand() % 2 == 1)
		{
			if (rand() % 2 == 1)
			{
				hus_m += 1;
			}
			else
			{
				hus_m -= 1;
			}
		}
		else
		{
			if (rand() % 2 == 1)
			{
				hus_n += 1;
			}
			else
			{
				hus_n -= 1;
			}
		}
		if (hus_m < 0 || hus_m > 15 || hus_n < 0 || hus_n > 15 || map[hus_m][hus_n] == 1)
		{
			hus_m = hus1_m;
			hus_n = hus1_n;
		}
		else if (first_out == 1 && mode == 0 && (hus_m < 8 && hus_n < 8))
		{
			hus_m = hus1_m;
			hus_n = hus1_n;
		}
		else if (first_out == 1 && mode == 1 && (hus_m < 8 && hus_n > 7))
		{
			hus_m = hus1_m;
			hus_n = hus1_n;
		}
		else if (last_in == 1 && mode == 0 && (hus_m < 8 || hus_n < 8))
		{
			hus_m = hus1_m;
			hus_n = hus1_n;
		}
		else if (last_in == 1 && mode == 1 && (hus_m < 8 || hus_n > 7))
		{
			hus_m = hus1_m;
			hus_n = hus1_n;
		}
		else
		{
			if ((hus_m > 7 || hus_n > 7) && mode == 0)
				first_out = 1;
			if ((hus_m > 7 || hus_n < 8) && mode == 1)
				first_out = 1;
			if ((hus_m > 7 && hus_n > 7) && mode == 0)
				last_in = 1;
			if ((hus_m > 7 && hus_n < 8) && mode == 1)
				last_in = 1;
			if (hus_m == home_m && hus_n == home_n)
				end_flag = 1;
			if (hus_m == wife_m && hus_n == wife_n)
				meet_flag = 1;
			map[hus1_m][hus1_n] = 0;
			if (hus1_m == pub_m && hus1_n == pub_n)
				map[hus1_m][hus1_n] = 2;
			map[hus_m][hus_n] = 4;
		}
		return end_flag;
	}
	else if (meet_flag == 1)
	{
		show();
		int input = _getch();
		while (1)
		{
			if (input == 224)
			{
				int in = _getch();
				if (in == 72)
				{
					hus_m -= 1;
				}
				else if (in == 80)
				{
					hus_m += 1;
				}
				else if (in == 75)
				{
					hus_n -= 1;
				}
				else if (in == 77)
				{
					hus_n += 1;
				}
			}
			else
				continue;
			if (hus_m < 0 || hus_m > 15 || hus_n < 0 || hus_n > 15 || map[hus_m][hus_n] == 1)
			{
				hus_m = hus1_m;
				hus_n = hus1_n;
			}
			else if (first_out == 1 && mode == 0 && (hus_m < 8 && hus_n < 8))
			{
				hus_m = hus1_m;
				hus_n = hus1_n;
			}
			else if (first_out == 1 && mode == 1 && (hus_m < 8 && hus_n > 7))
			{
				hus_m = hus1_m;
				hus_n = hus1_n;
			}
			else if (last_in == 1 && mode == 0 && (hus_m < 8 || hus_n < 8))
			{
				hus_m = hus1_m;
				hus_n = hus1_n;
			}
			else if (last_in == 1 && mode == 1 && (hus_m < 8 || hus_n > 7))
			{
				hus_m = hus1_m;
				hus_n = hus1_n;
			}
			else
			{
				if (hus_m == home_m && hus_n == home_n)
					end_flag = 1;
				map[hus1_m][hus1_n] = 0;
				map[hus_m][hus_n] = 4;
			}
			system("cls");
			return end_flag;
		}
	}

}

void set_map()
{
	int toss = rand() % 2;
	if (toss == 0) //1사분면 일 시
	{
		map[2][0] = 2;// 펍의 위치를 나타냄
		map[11][11] = 3;// 집의 위치를 나타냄
		hus_m = 2;
		hus_n = 0;
		wife_m = 8;
		wife_n = 8;
		map[hus_m][hus_n] = 4; //남편이 움직여야 하므로 hus m,n 을 설정
		map[wife_m][wife_n] = 5; // 
		pub_m = 2;
		pub_n = 0;
		home_m = 11;
		home_n = 11;
		mode = 0;
	}
	else if (toss == 1) // 2사분면 일 시
	{
		map[3][14] = 2;// 펍의 위치를 나타냄
		map[11][3] = 3;// 집의 위치를 나타냄
		hus_m = 3;
		hus_n = 14;
		wife_m = 8;
		wife_n = 0;
		map[hus_m][hus_n] = 4; //남편이 움직여야 하므로 hus m,n 을 설정
		map[wife_m][wife_n] = 5; // 
		pub_m = 3;
		pub_n = 14;
		home_m = 11;
		home_n = 3;
		mode = 1;
	}
}

int main(void)
{
	srand(time(NULL));
	set_map();
	show();
	while (1)
	{
		Sleep(70);
		{
			system("cls");
			wife_step();
			if (hus_step() == 1)
			{
				show();
				break;
			}
			show();
		}
	}
	system("pause");
	return 0;
}