#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#pragma comment(linker, "/STACK:996777217")

typedef unsigned long long INT_64;

const int MAX = 100000;

//  Генератор случайных чисел большой разрядности
//  переменная и константы генератора LineRand() 
static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//  функция установки первого случайного числа от часов 
//  компьютера 
void sRand() { srand(time(0)); RRand = (INT_64)rand(); }

//  функция генерации случайного числа 
//  линейный конгруэнтный генератор    Xi+1=(a*Xi+c)%m 
//  habr.com/ru/post/208178 
INT_64 LineRand()
{
	INT_64 y1, y2;
	y1 = (aRand * RRand + cRand) % mRand;
	y2 = (aRand * y1 + cRand) % mRand;
	RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
	return RRand;
}

//  Тест трудоёмкости операций случайного BST - дерева
void test_work() {
	//  создание дерева для 64 – разрядных ключей типа INT_64 
	struct BST* tree = NULL;
	//  массив для ключей, которые присутствуют в дереве  
	INT_64* m = new INT_64[MAX];
	INT_64 a;
	int step_add = 0, step_get = 0, step_del = 0, count = 1;
	//  установка первого случайного числа 
	sRand();
	//  заполнение дерева и массива элементами  
	//  со случайными ключами 
	for (int i = 0; i < MAX; i++)
	{
		m[i] = LineRand();
		add(&tree, m[i]);
	}
	number(tree, count);
	printf("Кол-во узлов в дереве до теста: %d\n", count);
	count = 1;
	for (int i = 0; i < MAX / 2; i++)
		if (i % 10 == 0)  //  10% промахов 
		{
			a = LineRand();
			remove(&tree, a, step_del);
			a = m[rand() % MAX];
			add(&tree, a, step_add);
			a = LineRand();
			get(&tree, a, step_get);
		}
		else  //  90% успешных операций 
		{
			int ind = rand() % MAX;
			remove(&tree, m[ind], step_del);
			INT_64 key = LineRand();
			add(&tree,key, step_add);
			m[ind] = key;
			a = m[rand() % MAX];
			get(&tree, a, step_get);
		}  //  конец теста
	number(tree, count);
	printf("Кол-во узлов в дереве после теста: %d\n", count);
	printf("Теоретическая трудоёмкость:\n");
	printf("1.39*log2(n)=%lf\n", 1.39 * (log((double)MAX) / log(2.0)));
	printf("Экспериментальная трудоёмкость:\n");
	printf("Вставка: %d\nПоиск: %d\nУдаление: %d", step_add / (MAX / 2), step_get / (MAX / 2), step_del / (MAX / 2));
	clear(tree);
}

int main() {
	system("chcp 1251");
	system("cls");
	test_work();
	_CrtDumpMemoryLeaks();
}
