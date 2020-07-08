#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<memory.h>
#include<string.h>


using namespace std;

#define DEFAUTSIZE 16


typedef struct _LinkNode{
	_LinkNode *next;
	void* key;
	void *date;
}ListNode;

typedef ListNode *List;
typedef ListNode *element;

typedef struct _Hashtable{
	int TableSize;
	List *Thelist;
}Hashtable;


int Hash(void *key,int TableSize);									//哈希函数根据key计算索引，定位hash桶的位置
Hashtable *InitHash(int TableSize);									//哈希表的初始化
element find(Hashtable *HashTable,void* key);							//给定键值判断该键值对是否有元素
void insertHashTable(Hashtable* HashTable,void* key,void *value);		//插入元素
void deleteHashTable(Hashtable *HashTable,void* key);					//删除元素
void *retrive(element e);											//获取元素
void destoyed(Hashtable *HashTable);								//哈希表的销毁分三层
void Destory(Hashtable *HashTable);									//martiondestoryed
unsigned int SDBNHash(void *key);

