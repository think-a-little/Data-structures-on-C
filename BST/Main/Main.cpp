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

//Генератор случайных чисел большой разрядности
//переменная и константы генератора LineRand() 
static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;



//функция установки первого случайного числа от часов 
//компьютера 
void sRand() { srand(time(0)); RRand = (INT_64)rand(); }

//функция генерации случайного числа 
//линейный конгруэнтный генератор    Xi+1=(a*Xi+c)%m 
//habr.com/ru/post/208178 
INT_64 LineRand()
{
	INT_64 y1, y2;
	y1 = (aRand * RRand + cRand) % mRand;
	y2 = (aRand * y1 + cRand) % mRand;
	RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
	return RRand;
}


//Тест трудоёмкости операций случайного BST - дерева

void test() {
	struct BST* tree = NULL;
	int val, count = 1;
	add(&tree, 9);
	add(&tree, 6);
	add(&tree, 17);
	add(&tree, 3);
	add(&tree, 8);
	add(&tree, 16);
	add(&tree, 20);
	add(&tree, 1);
	add(&tree, 4);
	add(&tree, 7);
	add(&tree, 12);
	add(&tree, 19);
	add(&tree, 21);
	add(&tree, 2);
	add(&tree, 5);
	add(&tree, 11);
	add(&tree, 14);
	add(&tree, 18);
	add(&tree, 10);
	add(&tree, 13);
	add(&tree, 15);
	print(tree);
	/*for (int i = 0; i < 21; i++) {
		printf("Введите значение: ");
		scanf_s("%d", &val);
		remove(&tree, val);
		if (tree != NULL) {
			print(tree);
		}
	}*/
	number(tree, count);
	printf("\nКол-во узлов в дереве до теста: %d\n", count);
	clear(tree);
}

void test_work() {
	//создание дерева для 64 – разрядных ключей типа INT_64 
	struct BST* tree = NULL;
	//массив для ключей, которые присутствуют в дереве  
	INT_64* m = new INT_64[MAX];
	INT_64 a;
	int step_add = 0, step_get = 0, step_del = 0, count = 1;
	//установка первого случайного числа 
	sRand();
	//заполнение дерева и массива элементами  
	//со случайными ключами 
	for (int i = 0; i < MAX; i++)
	{
		m[i] = LineRand();
		add(&tree, m[i]);
	}

	/*struct BST* tree = NULL;
	int arr[MAX], rand_key = 0, step_add = 0, step_get = 0, step_del = 0, count = 1;
	srand(time(NULL));
	for (int i = 0; i < MAX; i++) {
		arr[i] = rand();
		add(&tree, arr[i]);
	}*/
	number(tree, count);
	printf("Кол-во узлов в дереве до теста: %d\n", count);
	count = 1;


	for (int i = 0; i < MAX / 2; i++)
		if (i % 10 == 0) //10% промахов 
		{
			a = LineRand();
			remove(&tree, a, step_del);
			a = m[rand() % MAX];
			add(&tree, a, step_add);
			a = LineRand();
			get(&tree, a, step_get);
		}
		else  //90% успешных операций 
		{
			int ind = rand() % MAX;
			remove(&tree, m[ind], step_del);
			INT_64 key = LineRand();
			add(&tree,key, step_add);
			m[ind] = key;
			a = m[rand() % MAX];
			get(&tree, a, step_get);
		} //конец теста 
	

	/*for (int i = 0; i < MAX / 2; i++) {
		if (i % 10 == 0) {
			//  printf("счет %d\n", i);
			add(&tree, arr[i] % MAX, step_add);
			rand_key = 0;
			while (rand_key == 0) {
				rand_key = rand();
				for (int i = 0; i < MAX; i++) {
					if (rand_key == arr[i]) {
						rand_key = 0;
						break;
					}
				}
			}
			remove(&tree, rand_key, step_del);
			get(&tree, rand_key, step_get);
		}
		else {
			rand_key = 0;
			while (rand_key == 0) {
				rand_key = rand();
				for (int i = 0; i < MAX; i++) {
					if (rand_key == arr[i]) {
						rand_key = 0;
						break;
					}
				}
			}
			add(&tree, rand_key, step_add);
			get(&tree, arr[i] % MAX, step_get);
			remove(&tree, arr[i] % MAX, step_del);
			
		}
	}*/


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
	/*int N, val;
	printf("Введите число узлов: ");
	scanf_s("%d", &N);
	struct BST* tree = NULL;
	for (int i = 0; i < N; i++) {
		printf("Введите значение: ");
		scanf_s("%d", &val);
		add(&tree, val);
	}
	print(tree);
	for (int i = 0; i < N; i++) {
		printf("Введите значение: ");
		scanf_s("%d", &val);
		remove(&tree, val);
		if (tree != NULL) {
			print(tree);
		}
	}*/

	//clear(tree);
	test_work();
	_CrtDumpMemoryLeaks();
}
