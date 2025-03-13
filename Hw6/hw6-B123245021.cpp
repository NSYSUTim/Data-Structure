// 江威廷 B123245021 
// 11/13/2024
// 程式功能 : 用binary search tree找出 一數字串中 出現次數為 奇數次之數字，並由小到大輸出node和其左/右子節點 
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
//函式傳入之root為子節點，如為main裡傳入之Root則為根節點。BST函數皆是在當前樹中做操作 
	//使用遞迴插入節點，同時設置遍歷到節點的左或右子節點
	TreeNode* insert(TreeNode* root,int value){
		if(root==NULL){	//如節點為NULL，回傳new node。樹為空時在main裡定義給根節點Root，或在if else裡定義給該點之左/右子節點，看在哪裡呼叫 
			return new TreeNode(value);
		}
		if(value<root->data){	//如要插入值小於當前點之值 
			root->left=insert(root->left,value);//當前點之左子節點設值成， 1.如原來左子節點就存在，則下一次遞迴時就會回傳該存在的點(由下面的return root;)，等於這次該點左子節點設成該點左子節點 2.如左子節點並不存在，則下一次遞迴時就會回傳新節點，等於這次該點左子節點是一個新節點 
		}else if(value>root->data){
			root->right=insert(root->right,value);	//同前之邏輯 
		}
		return root;	//第一次的函式回傳傳入的root節點，在主函式裡又=Root節點，故代表樹的根節點，第二次後的遞迴root用來定義給前面if else該點之左/右子節點
	}
	//看在子樹裡有沒有找到值為value的節點
	int search(TreeNode* root,int value){
		if(root==NULL) return 0;	//如遞迴後左/子樹已經到NULL節點，則找不到 
		if(root->data==value) return 1;	//節點之值等於要找的值，回傳1 
		if(value<root->data) return search(root->left,value);	//值小於當前節點之值，則往左子節點找，因為bst左子樹小於節點小於右子樹 
		return search(root->right,value);	//值大於當前節點值，往右子節點找
	}
	//刪除子樹裡的節點 
	TreeNode* deletenode(TreeNode* root,int value){
		if(root==NULL) return NULL;	// 節點為NULL，則回傳NULL。代表樹為空不能再刪除，並在main裡設Root為NULL(main裡呼叫時)。或遞迴到最後的子節點時也找不到value，則回傳NULL，不改變樹的結構 
		if(value<root->data){	//如要刪除值小於當前點之值
			root->left=deletenode(root->left,value);//則當前點之左子節點設成deletenode函式回傳值，遞迴尚未找到要刪除點之時，皆會回傳傳入的root，故不改變樹的結構。找到要刪除的點時，用來設置刪除的點的parent(當前root)的left或right要是刪除的點的left或right(遞迴時下面的temp)，這樣樹結構才不會錯，遞迴呼叫deletenode前要加root->left=的原因就只為了這個 
		}else if(value>root->data){	//同上邏輯 
			root->right=deletenode(root->right,value);
		}else{	//如找到要刪除之節點 
			//處理樹的結構，刪掉的點前後要連起來 
			if(root->left==NULL){//如沒有左子節點。左右子節點都沒有的話，則使用哪邊操作結果都一樣 
				TreeNode* temp=root->right;
				delete root;	//刪除當前找到節點 
				return temp;	//回傳右子節點，會透過先前的遞迴設置成前一個的right或left，樹結構才不會出錯 
			}else if(root->right==NULL){//如無右子節點，有左子節點 
				TreeNode* temp=root->left;
				delete root;	//刪除當前找到節點 
				return temp;	//回傳左子節點，會透過先前的遞迴設置成前一個的right或left，樹結構才不會出錯
			}else{	//如左右皆有子節點 
				TreeNode* temp=findMin(root->right);//則替換成左子樹中最右邊最大的值或是右子樹中最左最小的值都可 
				root->data=temp->data;//當前點之值替換成最小(大)之值，我是用右子樹中最小之值替換 
				deletenode(root->right,temp->data);//刪除右子樹中最小之值
			}
		}
		return root;
	}
	//遞迴前序遍歷bst，由小到大 
	void inor_Trav(TreeNode* root, vector<int>& ans){
		if(root==NULL)	return;
		
		inor_Trav(root->left,ans);			//左子節點先 
		ans.push_back(root->data);			//當前節點 
		inor_Trav(root->right,ans);			//再右子節點 
	}											//補充:如為中/後序則修改遞迴呼叫之順序即可 
	
	// 找到子樹中最小(最左邊)的值
	TreeNode* findMin(TreeNode* root){
		while(root->left != NULL)	root=root->left;
		return root;
	}
	
	// 輸出 bst
	void show(TreeNode* root){
		vector<int> ans;	// 放前序遍歷 bst之結果
		inor_Trav(root,ans);	//前序遍歷 
		
		cout << "node:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<ans[i];
		cout<<endl<<"left:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<getlv(root,ans[i]);
		cout<<endl<<"right:";
		for(int i=0;i<ans.size();i++)	cout<<" "<<getrv(root,ans[i]);
	}
private:
	//當前點之左子節點之值 
	int getlv(TreeNode* root,int value){
		TreeNode* temp=findNode(root,value);	//temp=當前點在bst中的位置的節點 
		if(temp->left!=NULL)	return temp->left->data;	//回傳當前點之左子節點之值 
		return 0;	//回傳0，如左子節點為NULL 
	}
	//當前點之右子節點之值 
	int getrv(TreeNode* root,int value){
		TreeNode* temp=findNode(root,value);	//temp=當前點在bst中的位置的節點 
		if(temp->right!=NULL)	return temp->right->data;	//回傳當前點之右子節點之值 
		return 0;	//回傳0，如右子節點為NULL 
	}
	//尋找當前點root在bst中之位置之節點 
	TreeNode* findNode(TreeNode* root,int value){
		if(root==NULL||root->data==value)	return root;//如找不到或找到回傳root(NULL或該值) 
		if(value<root->data)	return findNode(root->left,value);//value小於當前點之值，往左子樹中尋找 
		return findNode(root->right,value);	//反之，往右子樹中尋找 
	}
};

int main(){
	BST bst;	//宣告bst樹 
	int f=1;	//f=1時為第一組側資，輸出時前面不換行和加空行
	int n;	//輸入值 
	while(cin>>n){
		TreeNode* Root=NULL;	//樹的根結點 Root 
		Root=bst.insert(Root,n);	//插入n值節點並依insert函數邏輯設置Root，即將Root設為n值新節點 
		while(cin>>n&&n!=-1){
			if(bst.search(Root,n)){	//如n值出現在bst裡 
				Root=bst.deletenode(Root,n);//刪除值為n之節點，並依deletenode函數邏輯設置Root節點 
			}else{
//				if(Root!=NULL)	bst.insert(Root,n);
//				else
				Root=bst.insert(Root,n);//插入n值節點並依insert函數邏輯設置Root
			}	//因為deletenode函數呼叫時有可能刪除Root並設置Root為NULL，故這裡的insert也還是要加Root=設置Root以應對樹為空時需指定Root的情況，前一行的程式碼可證明此事 
		}
		if(!f)	cout<<endl<<endl;
		f=0;
		bst.show(Root);
	}
	return 0;
}

