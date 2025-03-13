// 江威廷 B123245021 
// 09/19/2024
// 程式功能 : 使用遞回判斷騎士可否走完n*n之棋盤
#include <iostream>
#include<vector>
using namespace std;
int di[] = {0,-2, -1, 1, 2, 2, 1, -1, -2};	// 8 種行進方向之 i 座標，di[0]不使用 
int dj[] = {0,1, 2, 2, 1, -1, -2, -2, -1};	// 行進方向之 j 座標，dj[0]不使用 

class my{
public:
	int val,i,j,d;//紀錄該點之值val，座標(i, j)和嘗試之方向種類 d 
	my(){}
	my(int v,int i,int j,int d):val(v),i(i),j(j),d(d){}
};

void dfs(my &m,vector<vector<my>> &v){//my &m為當前走到的點， &v 需更新故加& 
	int d=m.d , va=m.val ,n=v.size();//d為當前要嘗試之方向，va當前之值 
	if(va==n*n){	//如填完，輸出並結束 
		for(int i=0;i<n;i++){	for(int j=0;j<n;j++)	printf("%3d",v[i][j].val);	cout<<endl;	}
		cout<<endl;										//格式化輸出 
		return;
	}
	
	while(d<=8){//嘗試最多 8 種方向 
		int i=m.i+ di[d] , j=m.j+ dj[d];//(i,j)為下一個到的點的座標 
		if(i<n&&i>=0&&j>=0&&j<n&&v[i][j].val==0){//如(i,j)在 v 陣列中且值為 0 
			v[i][j]={va+1,i,j,1};// 更新 v[i][j]並設方向從 1 開始 
			v[m.i][m.j].d=d;	// 更新當前點(m.i,m.j)使用之方向，未更新回朔時會進入無限遞迴!!!!! 
			return dfs(v[i][j],v);	//往下一個點處理 
		}else{
			d++;	//嘗試下一種方向 
		}
	}
	if(d==9){//8種方向都走不通，需回朔 
		if(m.i==0&&m.j==0){//如為出發點嘗試到第8種方向，則無解 
			cout<<"No solution"<<endl<<endl;	return;
		}
		v[m.i][m.j].val=0;//當前點之值變回 0 
		int ri,rj;
		for(int i=0;i<n;i++)	for(int j=0;j<n;j++)	if(v[i][j].val==va-1){	ri=i; rj=j;}//尋找前一個點之位置 
		v[ri][rj].d+=1;	//前一個行進點之方向 +1 
		return dfs(v[ri][rj],v); //處理前一個點 
	}
}

void solve(int n){
	if(n==1){	cout<<n<<endl<<endl;	return;	}	//n為1，輸出 1 
	vector<vector<my>> v(n,vector<my>(n));	//n*n之vector 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			v[i][j]={0,i,j,1};		//初始化vector 
		}
	}
	v[0][0]={1,0,0,3};//從(0,0)為 1 ，方向為第3種開始 
	dfs(v[0][0],v);
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

