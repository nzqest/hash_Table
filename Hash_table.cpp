#include"hash_table.h"


#define compare(a,b) strcmp((const char*)a,(const char *)b)
#define hash_func  SDBNHash


unsigned int SDBNHash(void *key){
	unsigned int hash = 0;
	char *str = (char*)key;

	while(*str){
	
	hash = (*str++)+(hash<<6)+(hash<<16)-hash;
	
	}
	return (hash & 0x7FFFFFFF);


}





//哈希函数根据key计算索引，定位hash桶的位置
int Hash(void *key,int TableSize){
	
	return hash_func(key)%TableSize;

}

//哈希表的初始化
Hashtable *InitHash(int TableSize){
	int i=0;
	Hashtable *Thash =NULL;

	if(TableSize<=0){
		TableSize=DEFAUTSIZE;
	}
	//给哈希表头分配内存
	Thash =(Hashtable*)malloc(sizeof(Hashtable));

	if(!Thash){
	
		printf("have no Hashtable be maked!\n");
		return NULL;
	}
	Thash->TableSize = TableSize;
	
	//分配成功后把哈希表头分配Talesize个索引
	Thash->Thelist = (List*)malloc(TableSize*sizeof(List));
	
	
	if(!Thash->Thelist){//若索引 没有分配成功，删掉Thash，
		
		printf("have no Hashtable be maked!\n");
		//Thash->Thelist=NULL;
		free(Thash);
		return NULL;

	}
	//给分配好的索引分配内存
	for(i=0;i<TableSize;i++){
		Thash->Thelist[i]=(ListNode*)malloc(sizeof(ListNode));
		if(!Thash->Thelist[i]){//防御式编程
		printf("have no Hashtable be maked!\n");
			free(Thash->Thelist);
			free(Thash);
			return NULL;
		}
		else{
			memset(Thash->Thelist[i],0,sizeof(ListNode));
		}

	
	}
	return Thash;	
}
//给定键值判断该键值对是否有元素
element find(Hashtable *HashTable,void *key){
	if(!HashTable||HashTable->TableSize==NULL)return NULL;

	int i=0;
	element e = NULL;
	List L = NULL;
	//计算索引key
	i = Hash(key,HashTable->TableSize);
	if(HashTable->Thelist==NULL)return NULL;
	L = HashTable->Thelist[i];
	
	e=L->next;

	//找到相同的键值对或者到了最后一个元素退出查找
	//while(e!=NULL&&e->key!=key) e=e->next;
	while(e!=NULL&&compare(e->key,key)!=0) e=e->next;
	return e;

}

//插入元素
void insertHashTable(Hashtable* HashTable,void* key,void *value){
	if(!HashTable)return ;

	element tmp=NULL,e=NULL;
	List L=NULL;

	//判断key是否存在
	e = find(HashTable,key);

	if(!e){
		//如果e返回是NULL证明键值为key的元素还不存在，所以分配内存
		//tmp = (element)malloc(sizeof(element));
		tmp = (element)malloc(sizeof(ListNode));
		if(!tmp){
		printf("error malloc! \n");
		return ;
		}
	
		//分配内存成功后需要进行插入元素，首先要对tmp变量操作

		//L = HashTable->Thelist[Hash(key,HashTable->TableSize)];//找到该键值对索引的头部节点
	
		int code = Hash(key,HashTable->TableSize);
		L = HashTable->Thelist[code];
		tmp->date = value;
		tmp->key = key;
		tmp->next	= L->next;
		L->next = tmp;


	}else
		printf("key have exist return !\n");
	


}	
	//删除元素
void deleteHashTable(Hashtable *HashTable,void* key){

	
	//通过键值对找到该哈希表的索引
	int i =Hash(key,HashTable->TableSize);
	element e=NULL,last=NULL;
	List L = NULL;

	//找到索引的头节点
	L= HashTable->Thelist[i];
	last =	L; 
	//L = L->next;
	e=L->next;
	//判断索引内的元素的键值对是否存在
	while(e&&e->key!=key){
	
	//last = L;
	//L=L->next;
	last = e;
	e=e->next;
	
	}
	if(e){//
		last->next=e->next;
		//delete	(e);
		free(e);
	}

}		

//获取元素
void *retrive(element e){

	return e?e->date:NULL;


}

//哈希表的销毁分三层
void destoyed(Hashtable *HashTable){
	element tmp=NULL,cur=NULL;
	List L=NULL;

	//第一层由哈希桶找到该桶中的各个元素,桶是从0开始一直到tabalsize
	for(int i=0;i<HashTable->TableSize;i++){
		L=HashTable->Thelist[i];
		//i=0，从第一层桶开始
		cur = HashTable->Thelist[i];
		//tmp = cur->next;
		cur = cur->next;
		while(cur){
			
			tmp = cur;
			cur = cur->next;
			free (tmp);
		
			}

		free(L);

		//突破一层桶后删除第一层桶的头节点
		
		}

		free(HashTable->Thelist);
		free(HashTable);
		HashTable->Thelist=NULL;
		HashTable=NULL;
		
}			

void Destory(Hashtable *HashTable) { 

	int i=0; List L = NULL;
	element cur = NULL, next = NULL;
	for (i=0; i < HashTable->TableSize; i++) { 
		L = HashTable->Thelist[i];
		cur = L->next;
	
	
	while (cur != NULL){
		next = cur->next; free(cur); cur = next;
		}
	free(L);
	}
	free(HashTable->Thelist);
	free(HashTable);
}