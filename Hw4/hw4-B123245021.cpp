// ���§� B123245021 
// 09/19/2024
// �{���\�� : �ϥλ��^�P�_�M�h�i�_����n*n���ѽL
#include <iostream>
#include<vector>
using namespace std;
int di[] = {0,-2, -1, 1, 2, 2, 1, -1, -2};	// 8 �ئ�i��V�� i �y�СAdi[0]���ϥ� 
int dj[] = {0,1, 2, 2, 1, -1, -2, -2, -1};	// ��i��V�� j �y�СAdj[0]���ϥ� 

class my{
public:
	int val,i,j,d;//�������I����val�A�y��(i, j)�M���դ���V���� d 
	my(){}
	my(int v,int i,int j,int d):val(v),i(i),j(j),d(d){}
};

void dfs(my &m,vector<vector<my>> &v){//my &m����e���쪺�I�A &v �ݧ�s�G�[& 
	int d=m.d , va=m.val ,n=v.size();//d����e�n���դ���V�Ava��e���� 
	if(va==n*n){	//�p�񧹡A��X�õ��� 
		for(int i=0;i<n;i++){	for(int j=0;j<n;j++)	printf("%3d",v[i][j].val);	cout<<endl;	}
		cout<<endl;										//�榡�ƿ�X 
		return;
	}
	
	while(d<=8){//���ճ̦h 8 �ؤ�V 
		int i=m.i+ di[d] , j=m.j+ dj[d];//(i,j)���U�@�Ө쪺�I���y�� 
		if(i<n&&i>=0&&j>=0&&j<n&&v[i][j].val==0){//�p(i,j)�b v �}�C���B�Ȭ� 0 
			v[i][j]={va+1,i,j,1};// ��s v[i][j]�ó]��V�q 1 �}�l 
			v[m.i][m.j].d=d;	// ��s��e�I(m.i,m.j)�ϥΤ���V�A����s�^�Үɷ|�i�J�L�����j!!!!! 
			return dfs(v[i][j],v);	//���U�@���I�B�z 
		}else{
			d++;	//���դU�@�ؤ�V 
		}
	}
	if(d==9){//8�ؤ�V�������q�A�ݦ^�� 
		if(m.i==0&&m.j==0){//�p���X�o�I���ը��8�ؤ�V�A�h�L�� 
			cout<<"No solution"<<endl<<endl;	return;
		}
		v[m.i][m.j].val=0;//��e�I�����ܦ^ 0 
		int ri,rj;
		for(int i=0;i<n;i++)	for(int j=0;j<n;j++)	if(v[i][j].val==va-1){	ri=i; rj=j;}//�M��e�@���I����m 
		v[ri][rj].d+=1;	//�e�@�Ӧ�i�I����V +1 
		return dfs(v[ri][rj],v); //�B�z�e�@���I 
	}
}

void solve(int n){
	if(n==1){	cout<<n<<endl<<endl;	return;	}	//n��1�A��X 1 
	vector<vector<my>> v(n,vector<my>(n));	//n*n��vector 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			v[i][j]={0,i,j,1};		//��l��vector 
		}
	}
	v[0][0]={1,0,0,3};//�q(0,0)�� 1 �A��V����3�ض}�l 
	dfs(v[0][0],v);
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

