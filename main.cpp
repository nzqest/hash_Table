#include"hash_table.h"
#include<Windows.h>
#include<vector>
#include<string.h>
#include<string>

typedef struct _S{
	
	char elems[20];
}S;

int main(void){


	S s[20];
	//char elems[5][20];
	int count=0;
	string str;
	
	ifstream filename;
	filename.open("user.txt");

	if(filename.fail()){
		cerr<<"error open!"<<endl;
		exit(-1);
			

	}

	while(1){

		

		if(filename.eof())  {//判断文件是否结束
			break;
		}
		filename>>s[count].elems;
		if(filename.eof()) break;
		count++;
		
		}
	filename.close();
	
	cout<<"count="<<count<<endl;
	//cout<<"s"<<sizeof(s)<<"\t"<<"s0"<<sizeof(s[0])<<endl;
	for(int i=0;i<=count;i++){

	cout<<s[i].elems<<endl;
	
	}

	char *test="AADSABBSASADDD";
	Hashtable *Hash=InitHash(1024);
	char cur[5]={'\0'};
	strncpy_s(cur,test+1,4);
	/*bool isMatch = false;
	for(int i=0;i<sizeof(elems)/sizeof(elems[0]);i++){
		
		if(strncmp(test+1,elems[i],4)==0){
			
			isMatch=true;
			printf("找到了匹配的基因%s,确认是色盲\n",elems[i]);
			break;
			}
		
		}*/

	//if(isMatch==false)printf("检测基因正常\n");
	//insertHashTable(Hash,elems[0],elems[0]);
	//insertHashTable(Hash,elems[1],elems[1]);
	//insertHashTable(Hash,elems[2],elems[2]);
	//insertHashTable(Hash,elems[3],elems[3]);

	insertHashTable(Hash,s[0].elems,s[0].elems);
	insertHashTable(Hash,s[1].elems,s[1].elems);
	//insertHashTable(Hash,*v[1].str,v[1]);

		element e=find(Hash,cur);

		if(e){
		//printf("已经找到%s\t",e);
			cout<<"Have fouding"<<(const char*)retrive(e);
		}else{
		printf("have no found elems[%s]",cur);
		}
	
	printf("\n");

	system("pause");
	return 0;
}