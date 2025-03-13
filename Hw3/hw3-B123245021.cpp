// ���§� B123245021 
// 09/19/2024
// �{���\�� : �ϥΦ۩w�qstack�P�_�M�h�i�_����n*n���ѽL 
#include <iostream>
#include<vector>
using namespace std;

int di[] = {0,-2, -1, 1, 2, 2, 1, -1, -2};	// 8 �ئ�i��V�� i �y�СAdi[0]���ϥ�
int dj[] = {0,1, 2, 2, 1, -1, -2, -2, -1};	// ��i��V�� j �y�� �Adj[0]���ϥ� 

//�ϥ�linked list��@stack
class Node{
public:
	int i,j,d;//��e�I��T�]�t �y��(i, j)�M���դ���V���� d 
	Node *next; //���V�U�Ӹ`�I 
	Node(int i,int j,int dd):i(i),j(j),next(NULL){	d=dd;	}
};

class st{//��stack��@ 
public:
	Node *top;//st���� 
	int size;//st�j�p 
	st(int n):size(0),top(NULL){}	//��l st
	
	void pop(){	//solve�禡�̦��]���X�j�餧����A�G���ݧP�_st�O�_���� 
		Node *t=top;
		top=top->next;	//top�`�I�]���������U�@�Ӥ��`�I(st�̪��A����e�@�ӳ̤W����) 
		delete t;	//�R�� st ���������`�I 
		size--;	//�j�p -1 
		return;
	}
	void push(int i,int j,int d){
		Node *t=new Node(i,j,d);//�s�W�`�I�ê�l 
		t->next=top;//�]�m�䤧next�`�I��top 
		top=t;//top�]���s�W���`�I 
		size++;//�j�p +1 
		return;
	}
	Node* topp(){	return top;	}	//��^�ثest�����`�I 
};

void solve(int n){
	if(n==1){	cout<<n<<endl<<endl;	return;	}	//n��1�A��X 1 
	vector<vector<int>> v;	
	int a=1;// push�q(0,0)��m�A��V�� 3 �}�l 	// ��l�� n*n ��vector�Aa ��������J���ȡAa=1�}�l
	//�ŧistack
	st s(n);	s.push(0,0,3);		v.assign(n,vector<int>(n,0));	v[0][0]=a++;
	while(1){
		Node *t=s.topp();//s(stack)�������I 
		while(t->d<=8){
			int ni=t->i+di[t->d], nj=t->j+dj[t->d] ;// (ni,nj)���U�ӹ����I���y�� 
			if(ni<n&&ni>=0&&nj>=0&&nj<n&&v[ni][nj]==0){//�p(ni,nj)�b v �}�C���B�Ȭ� 0 
				v[ni][nj]=a++;	//��s v[ni][nj]���ȡA�Ba+=1 
				s.push(ni,nj,1);	break;	//push�U���I(ni,nj)�A��V�q1�}�l�A�i s(stack)
			}else{
				t->d++;		//��s�ù��դU�@�ؤ�V 
			}
		}
		if(t->d==9){//8�ؤ�V�������q 
			if(t->i==0&&t->j==0){	//�p���X�o�I���ը��8�ؤ�V�A�h�L�� 
				cout<<"No solution"<<endl<<endl;	break;
			}
			v[t->i][t->j]=0;	//��e�I�����ܦ^ 0 
			a--;	//�^�ҡA�e�@���I�n��J�� a �n�� 1
			s.pop();	//pop�����q���I 
			s.top->d++;	//�e�@���I����V +1�A���դU�@�� 
		}
		if(s.size==n*n){//�p�񧹡A��X�õ��� 
			for(int i=0;i<n;i++){	for(int j=0;j<n;j++)	cout<<v[i][j]<<" ";	cout<<endl;	}
			cout<<endl;
			break;
		}
	}
}

int main(){
//�L�X n=1�B2�B3�B4�B5�B6 ������
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

