// 江威廷 B123245021 
// 09/19/2024
// 程式功能 : 使用自定義stack判斷騎士可否走完n*n之棋盤 
#include <iostream>
#include<vector>
using namespace std;

int di[] = {0,-2, -1, 1, 2, 2, 1, -1, -2};	// 8 種行進方向之 i 座標，di[0]不使用
int dj[] = {0,1, 2, 2, 1, -1, -2, -2, -1};	// 行進方向之 j 座標 ，dj[0]不使用 

//使用linked list實作stack
class Node{
public:
	int i,j,d;//當前點資訊包含 座標(i, j)和嘗試之方向種類 d 
	Node *next; //指向下個節點 
	Node(int i,int j,int dd):i(i),j(j),next(NULL){	d=dd;	}
};

class st{//基本stack實作 
public:
	Node *top;//st頂部 
	int size;//st大小 
	st(int n):size(0),top(NULL){}	//初始 st
	
	void pop(){	//solve函式裡有設跳出迴圈之條件，故不需判斷st是否為空 
		Node *t=top;
		top=top->next;	//top節點設為頂部之下一個之節點(st裡的，等於前一個最上面的) 
		delete t;	//刪除 st 之頂部之節點 
		size--;	//大小 -1 
		return;
	}
	void push(int i,int j,int d){
		Node *t=new Node(i,j,d);//新增節點並初始 
		t->next=top;//設置其之next節點為top 
		top=t;//top設成新增之節點 
		size++;//大小 +1 
		return;
	}
	Node* topp(){	return top;	}	//返回目前st頂部節點 
};

void solve(int n){
	if(n==1){	cout<<n<<endl<<endl;	return;	}	//n為1，輸出 1 
	vector<vector<int>> v;	
	int a=1;// push從(0,0)位置，方向為 3 開始 	// 初始化 n*n 之vector，a 為紀錄填入之值，a=1開始
	//宣告stack
	st s(n);	s.push(0,0,3);		v.assign(n,vector<int>(n,0));	v[0][0]=a++;
	while(1){
		Node *t=s.topp();//s(stack)頂部之點 
		while(t->d<=8){
			int ni=t->i+di[t->d], nj=t->j+dj[t->d] ;// (ni,nj)為下個嘗試點之座標 
			if(ni<n&&ni>=0&&nj>=0&&nj<n&&v[ni][nj]==0){//如(ni,nj)在 v 陣列中且值為 0 
				v[ni][nj]=a++;	//更新 v[ni][nj]之值，且a+=1 
				s.push(ni,nj,1);	break;	//push下個點(ni,nj)，方向從1開始，進 s(stack)
			}else{
				t->d++;		//更新並嘗試下一種方向 
			}
		}
		if(t->d==9){//8種方向都走不通 
			if(t->i==0&&t->j==0){	//如為出發點嘗試到第8種方向，則無解 
				cout<<"No solution"<<endl<<endl;	break;
			}
			v[t->i][t->j]=0;	//當前點之值變回 0 
			a--;	//回朔，前一個點要填入的 a 要減 1
			s.pop();	//pop走不通的點 
			s.top->d++;	//前一個點的方向 +1，嘗試下一種 
		}
		if(s.size==n*n){//如填完，輸出並結束 
			for(int i=0;i<n;i++){	for(int j=0;j<n;j++)	cout<<v[i][j]<<" ";	cout<<endl;	}
			cout<<endl;
			break;
		}
	}
}

int main(){
//印出 n=1、2、3、4、5、6 之情形
	cout<<"n=1"<<endl;
	solve(1);
	
	cout<<"n=2"<<endl;
	solve(2);
	
	cout<<"n=3"<<endl;
	solve(3);
	
	cout<<"n=4"<<endl;
	solve(4);
	
	cout<<"n=5"<<endl;
	solve(5);
	
	cout<<"n=6"<<endl;
	solve(6);

	return 0;
}

