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


int Hash(void *key,int TableSize);									//��ϣ��������key������������λhashͰ��λ��
Hashtable *InitHash(int TableSize);									//��ϣ��ĳ�ʼ��
element find(Hashtable *HashTable,void* key);							//������ֵ�жϸü�ֵ���Ƿ���Ԫ��
void insertHashTable(Hashtable* HashTable,void* key,void *value);		//����Ԫ��
void deleteHashTable(Hashtable *HashTable,void* key);					//ɾ��Ԫ��
void *retrive(element e);											//��ȡԪ��
void destoyed(Hashtable *HashTable);								//��ϣ������ٷ�����
void Destory(Hashtable *HashTable);									//martiondestoryed
unsigned int SDBNHash(void *key);

