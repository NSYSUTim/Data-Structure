// 江威廷 B123245021 
// 10/09/2024
// 程式功能 : 使用 linked_list 處理兩多項式之乘法與加法 

#include <iostream>

using namespace std;

class Node{
public:
	int coef,expo;	//coef係數，expo次方 
	Node *next;		//題目有指定要next節點，但沒pre節點，故不用 
	Node(int co,int ex):coef(co),expo(ex),next(NULL){}	//constructor
};

class Poly{		//linked list
public:
	Node *first;	//首項 first 
	Poly():first(NULL){}
	Poly(const Poly &p){	//copy constructor
		this->first=NULL;
		Node *temp=p.first;
		while(temp!=NULL){
			this->add_node(temp->coef,temp->expo);
			temp=temp->next;
		}
	}
	
	void add_node(int co,int ex){	//新增該插入項(co*x^ex) 
		if(ex<0){	//次方小於零 
			cout<<"ex can't be negative"<<endl;
			return;
		}
		if(first==NULL){	//尚未有首項 
			first=new Node(co,ex);
			return;
		}
		int f=0,s=f;//f用來記錄 插入項 的前一個位置，s用來記錄 插入項 的後面一個位置，等一下會從頭找到這兩個節點，因為沒有使用pre節點 
		Node *temp=first;	//temp用來找到 插入項 在目前多項式中要加入的那個位置的下一個的節點。像是次方 3 在10 5 2裡找，temp就會找到 2 那一項，因為要插在5和2中間 
		while(temp!=NULL){
			if(ex<temp->expo){	//如要插入項目的次方小於目前temp的次方，則繼續，因需由大排到小 
				f++;
				s=f;
			}else if(ex==temp->expo){	//如 插入項次方 等於temp的次方，則找到位置並記錄 
				s=f+1;	break;	//因為 插入項 的次方已經出現在多項式裡了，所以 插入項 的下一個節點不會是temp，會是temp的next節點，temp為 插入項 為要修改合併的項 
			}else	break;	//找到位置，break; 
			temp=temp->next;
		}
		f--;	//temp的前一個位置 
		Node *fn=first,*sn=first;	//取得 插入項 前(fn) 後(sn)之節點，first，second 
		for(int i=0;i<f;i++)	fn=fn->next;
		for(int i=0;i<s;i++)	sn=sn->next;
		
		if(s-f==2){//插入項 的次方已出現在多項式
			Node *del=fn->next;
			if(temp->coef+co==0){	//如相加(合併)後此項會抵消(刪除) 
				if(f==-1){	//要刪除之次方項為首項 
					first=fn->next;	//first更新
					delete fn;	//刪除原本的first(fn) 
				}else{	//抵銷但 非 首項 
					fn->next=sn;	//使linked_list越過插入項	(把fn的next設為sn)
					delete del;		//刪除該項 
				}				 
			}else{	//相加後此項不會抵銷，依題意合併需用刪除 
				Node *temp2=new Node(temp->coef+co,ex);	//新增 係數相加 次方相同之節點 
				fn->next=temp2; 
				temp2->next=sn;			//在 fn 和 sn 中間插入temp2節點 
				delete del;			//刪除原本該次方項節點 
			}
		}else if(temp==first){		//插入項 的次方還沒出現過，且要插入成為首項 
			Node *temp2=new Node(co,ex);	//插入項temp2 
			temp2->next=first;		//temp2的next設為目前之首項 
			first=temp2;	//首項更新 
		}else{
			Node *temp2=new Node(co,ex);	//插入項 的次方還沒出現過，插入為中間項
			fn->next=temp2;	
			temp2->next=sn;			//一樣概念插入temp2，使用fn和temp2之next節點完成設置 
		}
		return;
	}
	Poly operator+(const Poly &p) const{
		Poly res(*this);		//res紀錄相加之結果，先賦值為加號左邊之多項式 
		Node *temp=p.first;
		while(temp!=NULL){		//依序加上 加號右邊之多項式 的各個次方項
			res.add_node(temp->coef,temp->expo);
			temp=temp->next;
		}
		return res;		//回傳結果 
	}
	Poly operator*(const Poly &p) const{
		Poly cpy(*this),res;		//cpy複製 *號左邊之多項式，res紀錄相加之結果
		Node *temp=p.first;	
		while(temp!=NULL){			//遍歷 *號右邊之多項式
			Node *tempcpy=cpy.first;
			while(tempcpy!=NULL){	//右邊之多項式的每個次方項 都要乘以 左邊之多項式的每一個次方項(遍歷 *號左邊次方項)，並且所有結果相加，如同乘法之概念 
				res.add_node(temp->coef*tempcpy->coef,temp->expo+tempcpy->expo);
				tempcpy=tempcpy->next;
			}
			temp=temp->next; 
		}
		return res;		//回傳結果 
	}
	void show(){
		Node* temp=first;
		if(first==NULL){	//如多項式為空 
			cout<<"0 0"<<endl;
		}
		while(temp!=NULL){	//否則輸出多項式 
			cout<<temp->coef<<" "<<temp->expo<<endl;
			temp=temp->next;
		}
		return;
	}
};
int main(){
//依題意處理輸入和輸出 
	int p,q,t=1;
	while(cin>>p){
		
		Poly A, B, C, D; //宣告多項式
		for(int i=0;i<p;i++){
			int a,b;
			cin>>a>>b;
			A.add_node(a,b);
		}
		
		cin>>q;		if(!p&&!q)	break;
		for(int i=0;i<q;i++){
			int a,b;
			cin>>a>>b;
			B.add_node(a,b);
		}
		
		C = A+B; //把 多項式A和多項式B相加結果放入C
		D = A*B; //把 多項式A和多項式B相乘結果放入D
		
		cout<<"Case"<<t++<<":"<<endl<<"ADD"<<endl;
		C.show();
		cout<<"MULTIPLY"<<endl;
		D.show();
	}

	return 0;
}

