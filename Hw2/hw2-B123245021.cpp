// ���§� B123245021 
// 09/18/2024
// �{���\�� : �s�@���u�p���v�B�u�涰�v�B�u�t���v�B�u�]�t�v�B�u�ݩ�v���إ\�઺set class 
#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
class TSet{
public:
	int as[256]={0};//�����r���O�_�w�g�X�{�L�A�X�{�аO�� 1 �A�L�h 0 
	string s,name;// s �s�񶰦X�������Aname�����X���W�� 
	TSet(){}
	TSet(string n):name(n){	}
	
	//const TSet &a �i�O���ȩΥk�ȡA���i�ק� 
	//unsigned char ���d�� 0~255�A�P�D�رԭz���r���̦h256�ج۲šA�G�ϥΨ�@������ 
	const TSet operator+(const TSet &b)const {//���� +�B��l 
		TSet t(name+"+"+b.name);// t �����B�⧹�������G 
		t.s=s;
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==0){//�p b.s���X�{ *this.s�S�X�{�L�����e�A
				t.s+=b.s[i];							//�h�N��[�i���G�r�� 
			}
		}sort(t.s.begin(),t.s.end());//�Ƨ� 
		return t;
	}
	const TSet operator*(const TSet &b)const {//���� *�B��l 
		TSet t(name+"*"+b.name);//�P�W 
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==1){//�p�ⶰ�X���X�{�Ӧr�� 
				t.s+=b.s[i];//�h�[�i���G�r�� 
			}
		}sort(t.s.begin(),t.s.end());//�Ƨ� 
		return t;
	}
	const TSet operator-(const TSet &b)const {//���� -�B��l 
		TSet t(name+"-"+b.name);//�P�W 
		for(int i=0;i<s.size();i++){
			if(b.as[static_cast<unsigned char>(s[i])]==0){//�p�ⶰ�X�ҥ��X�{�L 
				t.s+=s[i];//�h�N�Ӧr���[�i���G�r��
			}											//���P����h�ⶰ�X���X�{�L�� 
		}sort(t.s.begin(),t.s.end());//�Ƨ� 
		return t;
	}
	const TSet operator>=(const TSet &b) const{//���� >=�B��l 
		int f=1;
		for(int i=0;i<b.s.size();i++){
			if(as[static_cast<unsigned char>(b.s[i])]==0){//�p���Xb�X�{���ݩ󶰦Xa���r�� 
				f=0;	break;//f�аO��0 
			}
		}
		
		if(f==0)	return TSet(name+" does not contain "+b.name);//��Xb���ݩ�a 
		else	return TSet(name+" contain "+b.name);
	}const TSet operator<=(const TSet &b) const{//���� <=�B��l�A�P�e�@���޿�ۦP 
		int f=1;
		for(int i=0;i<s.size();i++){
			if(b.as[static_cast<unsigned char>(s[i])]==0){
				f=0;	break;
			}
		}
		if(f==0)	return TSet(b.name+" does not contain "+name);
		else	return TSet(b.name+" contain "+name);
	}
	TSet in(char c)const {//�ݦb���X�����S���X�{�L�r�� c 
		string ss;	ss+=c;
		if(as[static_cast<unsigned char>(c)]==0)	return TSet("'"+ss+"' is not in "+name);
		else	return TSet("'"+ss+"' is in "+name);
	} 
	
};
istream& operator>>(istream &is,TSet &a){	//��is��cin 
	getline(is,a.s);	// Ū������J�t�Ů�!!!!!
	string ans="";
	for(int i=0;i<a.s.size();i++){
		if(a.as[static_cast<unsigned char>(a.s[i])]==0){//�M����J��a.s�r��A�p���X�{�L�Ӧr�� 
			a.as[static_cast<unsigned char>(a.s[i])]=1;//�h�N�Ӧr���аO�� 1 
			ans+=a.s[i];//�[�i���G�r�� 
		}
	}
	sort(ans.begin(),ans.end());//�Ƨ� 
	a.s=ans;//��sa.s 
	return is;
}
ostream& operator<<(ostream &os,const TSet &a){	 
	if(a.name[1]==' ')	return os<<a.name;
	if(a.name[2]=='\'')	return os<<a.name;
	return os<<a.name<<": {"<<a.s<<"}";
}

int main(){//main function�̩M�D�ؽd�Ҫ��@��

	int t;
	cin>>t;
	for(int k=1;k<=t;k++){
		cin.ignore();
		TSet A("A"),B("B"); //�ŧi���X 
		cin>>A>>B;
		char c;
		cin>>c;
		
		TSet C, D;
		C = A+B; //�� A�MB�p�������G��JC 
		D = A*B; //�� A�MB�涰�����G��JD

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

