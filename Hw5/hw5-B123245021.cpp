// ���§� B123245021 
// 10/09/2024
// �{���\�� : �ϥ� linked_list �B�z��h���������k�P�[�k 

#include <iostream>

using namespace std;

class Node{
public:
	int coef,expo;	//coef�Y�ơAexpo���� 
	Node *next;		//�D�ئ����w�nnext�`�I�A���Spre�`�I�A�G���� 
	Node(int co,int ex):coef(co),expo(ex),next(NULL){}	//constructor
};

class Poly{		//linked list
public:
	Node *first;	//���� first 
	Poly():first(NULL){}
	Poly(const Poly &p){	//copy constructor
		this->first=NULL;
		Node *temp=p.first;
		while(temp!=NULL){
			this->add_node(temp->coef,temp->expo);
			temp=temp->next;
		}
	}
	
	void add_node(int co,int ex){	//�s�W�Ӵ��J��(co*x^ex) 
		if(ex<0){	//����p��s 
			cout<<"ex can't be negative"<<endl;
			return;
		}
		if(first==NULL){	//�|�������� 
			first=new Node(co,ex);
			return;
		}
		int f=0,s=f;//f�ΨӰO�� ���J�� ���e�@�Ӧ�m�As�ΨӰO�� ���J�� ���᭱�@�Ӧ�m�A���@�U�|�q�Y���o��Ӹ`�I�A�]���S���ϥ�pre�`�I 
		Node *temp=first;	//temp�Ψӧ�� ���J�� �b�ثe�h�������n�[�J�����Ӧ�m���U�@�Ӫ��`�I�C���O���� 3 �b10 5 2�̧�Atemp�N�|��� 2 ���@���A�]���n���b5�M2���� 
		while(temp!=NULL){
			if(ex<temp->expo){	//�p�n���J���ت�����p��ثetemp������A�h�~��A�]�ݥѤj�ƨ�p 
				f++;
				s=f;
			}else if(ex==temp->expo){	//�p ���J������ ����temp������A�h����m�ðO�� 
				s=f+1;	break;	//�]�� ���J�� ������w�g�X�{�b�h�����̤F�A�ҥH ���J�� ���U�@�Ӹ`�I���|�Otemp�A�|�Otemp��next�`�I�Atemp�� ���J�� ���n�ק�X�֪��� 
			}else	break;	//����m�Abreak; 
			temp=temp->next;
		}
		f--;	//temp���e�@�Ӧ�m 
		Node *fn=first,*sn=first;	//���o ���J�� �e(fn) ��(sn)���`�I�Afirst�Asecond 
		for(int i=0;i<f;i++)	fn=fn->next;
		for(int i=0;i<s;i++)	sn=sn->next;
		
		if(s-f==2){//���J�� ������w�X�{�b�h����
			Node *del=fn->next;
			if(temp->coef+co==0){	//�p�ۥ[(�X��)�ᦹ���|���(�R��) 
				if(f==-1){	//�n�R�������趵������ 
					first=fn->next;	//first��s
					delete fn;	//�R���쥻��first(fn) 
				}else{	//��P�� �D ���� 
					fn->next=sn;	//��linked_list�V�L���J��	(��fn��next�]��sn)
					delete del;		//�R���Ӷ� 
				}				 
			}else{	//�ۥ[�ᦹ�����|��P�A���D�N�X�ֻݥΧR�� 
				Node *temp2=new Node(temp->coef+co,ex);	//�s�W �Y�Ƭۥ[ ����ۦP���`�I 
				fn->next=temp2; 
				temp2->next=sn;			//�b fn �M sn �������Jtemp2�`�I 
				delete del;			//�R���쥻�Ӧ��趵�`�I 
			}
		}else if(temp==first){		//���J�� �������٨S�X�{�L�A�B�n���J�������� 
			Node *temp2=new Node(co,ex);	//���J��temp2 
			temp2->next=first;		//temp2��next�]���ثe������ 
			first=temp2;	//������s 
		}else{
			Node *temp2=new Node(co,ex);	//���J�� �������٨S�X�{�L�A���J��������
			fn->next=temp2;	
			temp2->next=sn;			//�@�˷������Jtemp2�A�ϥ�fn�Mtemp2��next�`�I�����]�m 
		}
		return;
	}
	Poly operator+(const Poly &p) const{
		Poly res(*this);		//res�����ۥ[�����G�A����Ȭ��[�����䤧�h���� 
		Node *temp=p.first;
		while(temp!=NULL){		//�̧ǥ[�W �[���k�䤧�h���� ���U�Ӧ��趵
			res.add_node(temp->coef,temp->expo);
			temp=temp->next;
		}
		return res;		//�^�ǵ��G 
	}
	Poly operator*(const Poly &p) const{
		Poly cpy(*this),res;		//cpy�ƻs *�����䤧�h�����Ares�����ۥ[�����G
		Node *temp=p.first;	
		while(temp!=NULL){			//�M�� *���k�䤧�h����
			Node *tempcpy=cpy.first;
			while(tempcpy!=NULL){	//�k�䤧�h�������C�Ӧ��趵 ���n���H ���䤧�h�������C�@�Ӧ��趵(�M�� *�����䦸�趵)�A�åB�Ҧ����G�ۥ[�A�p�P���k������ 
				res.add_node(temp->coef*tempcpy->coef,temp->expo+tempcpy->expo);
				tempcpy=tempcpy->next;
			}
			temp=temp->next; 
		}
		return res;		//�^�ǵ��G 
	}
	void show(){
		Node* temp=first;
		if(first==NULL){	//�p�h�������� 
			cout<<"0 0"<<endl;
		}
		while(temp!=NULL){	//�_�h��X�h���� 
			cout<<temp->coef<<" "<<temp->expo<<endl;
			temp=temp->next;
		}
		return;
	}
};
int main(){
//���D�N�B�z��J�M��X 
	int p,q,t=1;
	while(cin>>p){
		
		Poly A, B, C, D; //�ŧi�h����
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
		
		C = A+B; //�� �h����A�M�h����B�ۥ[���G��JC
		D = A*B; //�� �h����A�M�h����B�ۭ����G��JD
		
		cout<<"Case"<<t++<<":"<<endl<<"ADD"<<endl;
		C.show();
		cout<<"MULTIPLY"<<endl;
		D.show();
	}

	return 0;
}

