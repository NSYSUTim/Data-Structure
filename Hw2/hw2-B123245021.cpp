// 江威廷 B123245021 
// 09/18/2024
// 程式功能 : 製作有「聯集」、「交集」、「差集」、「包含」、「屬於」五種功能的set class 
#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
class TSet{
public:
	int as[256]={0};//紀錄字元是否已經出現過，出現標記為 1 ，無則 0 
	string s,name;// s 存放集合之元素，name為集合之名稱 
	TSet(){}
	TSet(string n):name(n){	}
	
	//const TSet &a 可是左值或右值，不可修改 
	//unsigned char 之範圍為 0~255，與題目敘述之字元最多256種相符，故使用其作為索引 
	const TSet operator+(const TSet &b)const {//重載 +運算子 
		TSet t(name+"+"+b.name);// t 紀錄運算完成之結果 
		t.s=s;
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==0){//如 b.s中出現 *this.s沒出現過的內容，
				t.s+=b.s[i];							//則將其加進結果字串 
			}
		}sort(t.s.begin(),t.s.end());//排序 
		return t;
	}
	const TSet operator*(const TSet &b)const {//重載 *運算子 
		TSet t(name+"*"+b.name);//同上 
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==1){//如兩集合都出現該字元 
				t.s+=b.s[i];//則加進結果字串 
			}
		}sort(t.s.begin(),t.s.end());//排序 
		return t;
	}
	const TSet operator-(const TSet &b)const {//重載 -運算子 
		TSet t(name+"-"+b.name);//同上 
		for(int i=0;i<s.size();i++){
			if(b.as[static_cast<unsigned char>(s[i])]==0){//如兩集合皆未出現過 
				t.s+=s[i];//則將該字元加進結果字串
			}											//等同於消去兩集合都出現過的 
		}sort(t.s.begin(),t.s.end());//排序 
		return t;
	}
	const TSet operator>=(const TSet &b) const{//重載 >=運算子 
		int f=1;
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==0){//如集合b出現不屬於集合a的字元 
				f=0;	break;//f標記為0 
			}
		}
		
		if(f==0)	return TSet(name+" does not contain "+b.name);//輸出b不屬於a 
		else	return TSet(name+" contain "+b.name);
	}const TSet operator<=(const TSet &b) const{//重載 <=運算子，與前一個邏輯相同 
		int f=1;
		for(int i=0;i<s.size();i++){
			if(b.as[static_cast<unsigned char>(s[i])]==0){
				f=0;	break;
			}
		}
		if(f==0)	return TSet(b.name+" does not contain "+name);
		else	return TSet(b.name+" contain "+name);
	}
	TSet in(char c)const {//看在集合中有沒有出現過字元 c 
		string ss;	ss+=c;
		if(as[static_cast<unsigned char>(c)]==0)	return TSet("'"+ss+"' is not in "+name);
		else	return TSet("'"+ss+"' is in "+name);
	} 
	
};
istream& operator>>(istream &is,TSet &a){	//把is當成cin 
	getline(is,a.s);	// 讀取整行輸入含空格!!!!!
	string ans="";
	for(int i=0;i<a.s.size();i++){
		if(a.as[static_cast<unsigned char>(a.s[i])]==0){//遍歷輸入之a.s字串，如未出現過該字元 
			a.as[static_cast<unsigned char>(a.s[i])]=1;//則將該字元標記為 1 
			ans+=a.s[i];//加進結果字串 
		}
	}
	sort(ans.begin(),ans.end());//排序 
	a.s=ans;//更新a.s 
	return is;
}
ostream& operator<<(ostream &os,const TSet &a){	 
	if(a.name[1]==' ')	return os<<a.name;
	if(a.name[2]=='\'')	return os<<a.name;
	return os<<a.name<<": {"<<a.s<<"}";
}

int main(){//main function裡和題目範例的一樣

	int t;
	cin>>t;
	for(int k=1;k<=t;k++){
		cin.ignore();
		TSet A("A"),B("B"); //宣告集合 
		cin>>A>>B;
		char c;
		cin>>c;
		
		TSet C, D;
		C = A+B; //把 A和B聯集的結果放入C 
		D = A*B; //把 A和B交集的結果放入D

		cout<<"Test Case "<<k<<":"<<endl;
		cout<<A<<endl;
		cout<<B<<endl;
		cout<<C<<endl;	//(A+B)
		cout<<D<<endl;	//(A*B)
		cout<<(A-B)<<endl;
		cout<<(B-A)<<endl;
		cout<<(A>=B)<<endl;
		cout<<(B>=A)<<endl;
		cout<<A.in(c)<<endl;
		cout<<B.in(c)<<endl<<endl;
	}


	return 0;
}

//2
//abcdef
//chfeechi
//h
//3abf4ec
//43
//g

