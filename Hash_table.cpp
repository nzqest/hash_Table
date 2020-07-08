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





//��ϣ��������key������������λhashͰ��λ��
int Hash(void *key,int TableSize){
	
	return hash_func(key)%TableSize;

}

//��ϣ��ĳ�ʼ��
Hashtable *InitHash(int TableSize){
	int i=0;
	Hashtable *Thash =NULL;

	if(TableSize<=0){
		TableSize=DEFAUTSIZE;
	}
	//����ϣ��ͷ�����ڴ�
	Thash =(Hashtable*)malloc(sizeof(Hashtable));

	if(!Thash){
	
		printf("have no Hashtable be maked!\n");
		return NULL;
	}
	Thash->TableSize = TableSize;
	
	//����ɹ���ѹ�ϣ��ͷ����Talesize������
	Thash->Thelist = (List*)malloc(TableSize*sizeof(List));
	
	
	if(!Thash->Thelist){//������ û�з���ɹ���ɾ��Thash��
		
		printf("have no Hashtable be maked!\n");
		//Thash->Thelist=NULL;
		free(Thash);
		return NULL;

	}
	//������õ����������ڴ�
	for(i=0;i<TableSize;i++){
		Thash->Thelist[i]=(ListNode*)malloc(sizeof(ListNode));
		if(!Thash->Thelist[i]){//����ʽ���
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
//������ֵ�жϸü�ֵ���Ƿ���Ԫ��
element find(Hashtable *HashTable,void *key){
	if(!HashTable||HashTable->TableSize==NULL)return NULL;

	int i=0;
	element e = NULL;
	List L = NULL;
	//��������key
	i = Hash(key,HashTable->TableSize);
	if(HashTable->Thelist==NULL)return NULL;
	L = HashTable->Thelist[i];
	
	e=L->next;

	//�ҵ���ͬ�ļ�ֵ�Ի��ߵ������һ��Ԫ���˳�����
	//while(e!=NULL&&e->key!=key) e=e->next;
	while(e!=NULL&&compare(e->key,key)!=0) e=e->next;
	return e;

}

//����Ԫ��
void insertHashTable(Hashtable* HashTable,void* key,void *value){
	if(!HashTable)return ;

	element tmp=NULL,e=NULL;
	List L=NULL;

	//�ж�key�Ƿ����
	e = find(HashTable,key);

	if(!e){
		//���e������NULL֤����ֵΪkey��Ԫ�ػ������ڣ����Է����ڴ�
		//tmp = (element)malloc(sizeof(element));
		tmp = (element)malloc(sizeof(ListNode));
		if(!tmp){
		printf("error malloc! \n");
		return ;
		}
	
		//�����ڴ�ɹ�����Ҫ���в���Ԫ�أ�����Ҫ��tmp��������

		//L = HashTable->Thelist[Hash(key,HashTable->TableSize)];//�ҵ��ü�ֵ��������ͷ���ڵ�
	
		int code = Hash(key,HashTable->TableSize);
		L = HashTable->Thelist[code];
		tmp->date = value;
		tmp->key = key;
		tmp->next	= L->next;
		L->next = tmp;


	}else
		printf("key have exist return !\n");
	


}	
	//ɾ��Ԫ��
void deleteHashTable(Hashtable *HashTable,void* key){

	
	//ͨ����ֵ���ҵ��ù�ϣ�������
	int i =Hash(key,HashTable->TableSize);
	element e=NULL,last=NULL;
	List L = NULL;

	//�ҵ�������ͷ�ڵ�
	L= HashTable->Thelist[i];
	last =	L; 
	//L = L->next;
	e=L->next;
	//�ж������ڵ�Ԫ�صļ�ֵ���Ƿ����
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

//��ȡԪ��
void *retrive(element e){

	return e?e->date:NULL;


}

//��ϣ������ٷ�����
void destoyed(Hashtable *HashTable){
	element tmp=NULL,cur=NULL;
	List L=NULL;

	//��һ���ɹ�ϣͰ�ҵ���Ͱ�еĸ���Ԫ��,Ͱ�Ǵ�0��ʼһֱ��tabalsize
	for(int i=0;i<HashTable->TableSize;i++){
		L=HashTable->Thelist[i];
		//i=0���ӵ�һ��Ͱ��ʼ
		cur = HashTable->Thelist[i];
		//tmp = cur->next;
		cur = cur->next;
		while(cur){
			
			tmp = cur;
			cur = cur->next;
			free (tmp);
		
			}

		free(L);

		//ͻ��һ��Ͱ��ɾ����һ��Ͱ��ͷ�ڵ�
		
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