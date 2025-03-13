// ���§� B123245021 
// 11/13/2024
// �{���\�� : ��binary search tree��X �@�Ʀr�ꤤ �X�{���Ƭ� �_�Ʀ����Ʀr�A�åѤp��j��Xnode�M�䥪/�k�l�`�I 
#include<iostream>
#include<vector>
using namespace std;

class TreeNode{
public:
	int data;
	TreeNode *left,*right;
	TreeNode(int value):data(value),left(NULL),right(NULL){}
};

class BST{
public:
//�禡�ǤJ��root���l�`�I�A�p��main�̶ǤJ��Root�h���ڸ`�I�CBST��ƬҬO�b��e�𤤰��ާ@ 
	//�ϥλ��j���J�`�I�A�P�ɳ]�m�M����`�I�����Υk�l�`�I
	TreeNode* insert(TreeNode* root,int value){
		if(root==NULL){	//�p�`�I��NULL�A�^��new node�C�𬰪Ůɦbmain�̩w�q���ڸ`�IRoot�A�Φbif else�̩w�q�����I����/�k�l�`�I�A�ݦb���̩I�s 
			return new TreeNode(value);
		}
		if(value<root->data){	//�p�n���J�Ȥp���e�I���� 
			root->left=insert(root->left,value);//��e�I�����l�`�I�]�Ȧ��A 1.�p��ӥ��l�`�I�N�s�b�A�h�U�@�����j�ɴN�|�^�ǸӦs�b���I(�ѤU����return root;)�A����o�����I���l�`�I�]�����I���l�`�I 2.�p���l�`�I�ä��s�b�A�h�U�@�����j�ɴN�|�^�Ƿs�`�I�A����o�����I���l�`�I�O�@�ӷs�`�I 
		}else if(value>root->data){
			root->right=insert(root->right,value);	//�P�e���޿� 
		}
		return root;	//�Ĥ@�����禡�^�ǶǤJ��root�`�I�A�b�D�禡�̤S=Root�`�I�A�G�N��𪺮ڸ`�I�A�ĤG���᪺���jroot�Ψөw�q���e��if else���I����/�k�l�`�I
	}
	//�ݦb�l��̦��S�����Ȭ�value���`�I
	int search(TreeNode* root,int value){
		if(root==NULL) return 0;	//�p���j�ᥪ/�l��w�g��NULL�`�I�A�h�䤣�� 
		if(root->data==value) return 1;	//�`�I���ȵ���n�䪺�ȡA�^��1 
		if(value<root->data) return search(root->left,value);	//�Ȥp���e�`�I���ȡA�h�����l�`�I��A�]��bst���l��p��`�I�p��k�l�� 
		return search(root->right,value);	//�Ȥj���e�`�I�ȡA���k�l�`�I��
	}
	//�R���l��̪��`�I 
	TreeNode* deletenode(TreeNode* root,int value){
		if(root==NULL) return NULL;	// �`�I��NULL�A�h�^��NULL�C�N��𬰪Ť���A�R���A�æbmain�̳]Root��NULL(main�̩I�s��)�C�λ��j��̫᪺�l�`�I�ɤ]�䤣��value�A�h�^��NULL�A�����ܾ𪺵��c 
		if(value<root->data){	//�p�n�R���Ȥp���e�I����
			root->left=deletenode(root->left,value);//�h��e�I�����l�`�I�]��deletenode�禡�^�ǭȡA���j�|�����n�R���I���ɡA�ҷ|�^�ǶǤJ��root�A�G�����ܾ𪺵��c�C���n�R�����I�ɡA�Ψӳ]�m�R�����I��parent(��eroot)��left��right�n�O�R�����I��left��right(���j�ɤU����temp)�A�o�˾𵲺c�~���|���A���j�I�sdeletenode�e�n�[root->left=����]�N�u���F�o�� 
		}else if(value>root->data){	//�P�W�޿� 
			root->right=deletenode(root->right,value);
		}else{	//�p���n�R�����`�I 
			//�B�z�𪺵��c�A�R�����I�e��n�s�_�� 
			if(root->left==NULL){//�p�S�����l�`�I�C���k�l�`�I���S�����ܡA�h�ϥέ���ާ@���G���@�� 
				TreeNode* temp=root->right;
				delete root;	//�R����e���`�I 
				return temp;	//�^�ǥk�l�`�I�A�|�z�L���e�����j�]�m���e�@�Ӫ�right��left�A�𵲺c�~���|�X�� 
			}else if(root->right==NULL){//�p�L�k�l�`�I�A�����l�`�I 
				TreeNode* temp=root->left;
				delete root;	//�R����e���`�I 
				return temp;	//�^�ǥ��l�`�I�A�|�z�L���e�����j�]�m���e�@�Ӫ�right��left�A�𵲺c�~���|�X��
			}else{	//�p���k�Ҧ��l�`�I 
				TreeNode* temp=findMin(root->right);//�h���������l�𤤳̥k��̤j���ȩάO�k�l�𤤳̥��̤p���ȳ��i 
				root->data=temp->data;//��e�I���ȴ������̤p(�j)���ȡA�ڬO�Υk�l�𤤳̤p���ȴ��� 
				deletenode(root->right,temp->data);//�R���k�l�𤤳̤p����
			}
		}
		return root;
	}
	//���j�e�ǹM��bst�A�Ѥp��j 
	void inor_Trav(TreeNode* root, vector<int>& ans){
		if(root==NULL)	return;
		
		inor_Trav(root->left,ans);			//���l�`�I�� 
		ans.push_back(root->data);			//��e�`�I 
		inor_Trav(root->right,ans);			//�A�k�l�`�I 
	}											//�ɥR:�p����/��ǫh�קﻼ�j�I�s�����ǧY�i 
	
	// ���l�𤤳̤p(�̥���)����
	TreeNode* findMin(TreeNode* root){
		while(root->left != NULL)	root=root->left;
		return root;
	}
	
	// ��X bst
	void show(TreeNode* root){
		vector<int> ans;	// ��e�ǹM�� bst�����G
		inor_Trav(root,ans);	//�e�ǹM�� 
		
		cout << "node:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<ans[i];
		cout<<endl<<"left:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<getlv(root,ans[i]);
		cout<<endl<<"right:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<getrv(root,ans[i]);
	}
private:
	//��e�I�����l�`�I���� 
	int getlv(TreeNode* root,int value){
		TreeNode* temp=findNode(root,value);	//temp=��e�I�bbst������m���`�I 
		if(temp->left!=NULL)	return temp->left->data;	//�^�Ƿ�e�I�����l�`�I���� 
		return 0;	//�^��0�A�p���l�`�I��NULL 
	}
	//��e�I���k�l�`�I���� 
	int getrv(TreeNode* root,int value){
		TreeNode* temp=findNode(root,value);	//temp=��e�I�bbst������m���`�I 
		if(temp->right!=NULL)	return temp->right->data;	//�^�Ƿ�e�I���k�l�`�I���� 
		return 0;	//�^��0�A�p�k�l�`�I��NULL 
	}
	//�M���e�Iroot�bbst������m���`�I 
	TreeNode* findNode(TreeNode* root,int value){
		if(root==NULL||root->data==value)	return root;//�p�䤣��Χ��^��root(NULL�θӭ�) 
		if(value<root->data)	return findNode(root->left,value);//value�p���e�I���ȡA�����l�𤤴M�� 
		return findNode(root->right,value);	//�Ϥ��A���k�l�𤤴M�� 
	}
};

int main(){
	BST bst;	//�ŧibst�� 
	int f=1;	//f=1�ɬ��Ĥ@�հ���A��X�ɫe��������M�[�Ŧ�
	int n;	//��J�� 
	while(cin>>n){
		TreeNode* Root=NULL;	//�𪺮ڵ��I Root 
		Root=bst.insert(Root,n);	//���Jn�ȸ`�I�è�insert����޿�]�mRoot�A�Y�NRoot�]��n�ȷs�`�I 
		while(cin>>n&&n!=-1){
			if(bst.search(Root,n)){	//�pn�ȥX�{�bbst�� 
				Root=bst.deletenode(Root,n);//�R���Ȭ�n���`�I�A�è�deletenode����޿�]�mRoot�`�I 
			}else{
//				if(Root!=NULL)	bst.insert(Root,n);
//				else
				Root=bst.insert(Root,n);//���Jn�ȸ`�I�è�insert����޿�]�mRoot
			}	//�]��deletenode��ƩI�s�ɦ��i��R��Root�ó]�mRoot��NULL�A�G�o�̪�insert�]�٬O�n�[Root=�]�mRoot�H����𬰪Ůɻݫ��wRoot�����p�A�e�@�檺�{���X�i�ҩ����� 
		}
		if(!f)	cout<<endl<<endl;
		f=0;
		bst.show(Root);
	}
	return 0;
}

