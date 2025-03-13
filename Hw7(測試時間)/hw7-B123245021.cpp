// ���§� B123245021 
// 11/21/2024
// �{���\�� : �ϥΤ��P�ƧǺt��k�i��ƧǡA�ñN�Ƨǫᵲ�G��X���ɮסC�P�ɰO�����P��ƶq�j�p�ɦU�t��k���B��ɶ��A�s�����C 

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <chrono> // �Ω���q�ɶ�
#include <iomanip> // �Ψӳ]�m��ܺ��
#include <thread>  // �����ޤJ�����Y�ɮרӨϥ� std::this_thread
using namespace std::this_thread;

using namespace std;
using namespace std::chrono;	//���q�ɶ���ƻݭn

int f[5]={0};	//�O�_�W�ɤ����� 
double average_time[5]={0};	// A �� E �����ƧǮɶ��A���ά� 

// n = 21���An = 10x + y�Ax=2�Ay=1 
void insertion_sort(vector<int>&);	//  A�� : (n mod 2)+1
template<class T>
void merge_sort(T&,int,int);	//  B�� : ((x + y) mod 2)+1 
void quick_sort(vector<int>&,int,int);	//  C�� : ((x + y * 2) mod 2)+1 
 
int comp(const void * a, const void * b){	//�Ω�qsort 
	return ( *(int*)a - *(int*)b );		//�Ѥp��j�Ƨ� 
}

//�Ѥp��j�Ƨ�
int main(){
//	auto temp=high_resolution_clock::now();
//	sleep_for(seconds(10));
//	cout<<duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9<<"secs";// �ഫ����
//	return 0;
	
	ifstream in("input_5000.txt");//Ū���Ҧ��}��
	if(!in){
		cout<<"failed to open input.txt"<<endl;	return -1;
	}
	
	// �n���}�n��X�ɮסA�]��c++��ofstream�q�{�}�@���|�M�Ť��e�����e�Φ۰ʳЫت���
	ofstream out("outputA.txt");
	if(!out){	cout<<"failed to create outputA.txt"<<endl;	return -1;	} 
	
	ofstream out2("outputB.txt");
	if(!out2){	cout<<"failed to create outputB.txt"<<endl;	return -1;	} 
	
	ofstream out3("outputC.txt");
	if(!out3){	cout<<"failed to create outputC.txt"<<endl;	return -1;	} 
	
	ofstream out4("outputD.txt");
	if(!out4){	cout<<"failed to create outputD.txt"<<endl;	return -1;	} 
	
	ofstream out5("outputE.txt");
	if(!out5){	cout<<"failed to create outputE.txt"<<endl;	return -1;	} 
	
	int N,times=0;	//10��
while(in>>N){
	times++;
//	cout<<N<<endl;
	vector<int> v(N);
	for(int i=0;i<N;i++){
		in>>v[i];
	}
	
	vector<int> aft_sort(N);
	aft_sort=v;	// vector �i�������w	
	
	//  A��
	if(f[0]==0){	//�p�٨S�W�� 
		insertion_sort(aft_sort);
		out<<"Insertion sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out<<aft_sort[i]<<endl;
		if(f[0]==0)
		cout<<"Insertion sort success"<<endl;		
	}

	//  B��
	if(f[1]==0){
		aft_sort=v;	//aft_sort���w���쥻���ƧǤ��ǦC
		auto temp=high_resolution_clock::now();
		merge_sort(aft_sort,0,aft_sort.size()-1);
		average_time[1]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;// �ഫ����
		if(average_time[1]>5*60){	f[2]=1;	break;	}
		out2<<"Merge sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out2<<aft_sort[i]<<endl;
		cout<<"Merge sort success"<<endl;
	}
	
	//  C��
	if(f[2]==0){
		aft_sort=v;	//aft_sort���w���쥻���ƧǤ��ǦC 
		auto temp=high_resolution_clock::now();		cout<<"Hi";
		quick_sort(aft_sort,0,aft_sort.size()-1);	cout<<"Hi";
		average_time[2]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;// �ഫ����
		if(average_time[2]>5*60){	f[2]=1;	break;	}
		out3<<"Quick sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out3<<aft_sort[i]<<endl;
		cout<<"Quick sort success"<<endl;
	}

	//  D��
	aft_sort=v;
	auto temp=high_resolution_clock::now();
	qsort(&aft_sort[0],aft_sort.size(),sizeof(int),comp);
	average_time[3]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;
	out4<<"C qsort()(N:"<<N<<")"<<endl;
	for(int i=0;i<aft_sort.size();i++)
		out4<<aft_sort[i]<<endl;
	cout<<"C qsort() sort success"<<endl;
	
	//  E��
	aft_sort=v;
	temp=high_resolution_clock::now();
	sort(aft_sort.begin(),aft_sort.end());	//�ϥ�c++���ب禡 
	average_time[4]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;
	out5<<"C++ sort()(N:"<<N<<")"<<endl;
	for(int i=0;i<aft_sort.size();i++)
		out5<<aft_sort[i]<<endl;
	cout<<"C++ sort() sort success"<<endl;

}
	out.close();
	out2.close();
	out3.close();	
	out4.close();
	out5.close();	
	in.close();	// c++ �� close �o�˼g

	cout << fixed << setprecision(6);
	
	cout<<"��ƶq "<<N<<" �ɡA����"<<times<<"��������"<<endl<<endl; 
	cout<<endl<<"Insertion sort: ";
	if(f[0]==1){
		cout<<"TLE"<<endl; 
	}else{
		cout<<average_time[0]/times<<"secs."<<endl;
	}

	cout<<endl<<"Merge sort: ";
	if(f[1]==1){
		cout<<"TLE"<<endl; 
	}else{
		cout<<average_time[1]/times<<"secs."<<endl;
	}
	
	cout<<endl<<"Quick sort: ";
	if(f[2]==1){
		cout<<"TLE"<<endl; 
	}else{
		cout<<average_time[2]/times<<"secs."<<endl;
	}
	
	cout<<endl<<"C qsort(): ";
	if(average_time[3]/10>5*60){
		cout<<"TLE"<<endl; 
	}else{
		cout<<average_time[3]/times<<"secs."<<endl;
	}
	
	cout<<endl<<"C++ sort(): ";
	if(average_time[4]/10>5*60){
		cout<<"TLE"<<endl; 
	}else{
		cout<<average_time[4]/times<<"secs."<<endl;
	}
	
	return 0;
}


void insertion_sort(vector<int> &v){
	if(f[0]==1)	return;
	
	 // �}�l�p��
    auto start = high_resolution_clock::now();  // �����}�l�ɶ�
	
	for(int i=1;i<v.size();i++){
		int key=v[i];
		int j=i-1;
		while(j>=0&&key<v[j]){
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=key;
		auto temp = high_resolution_clock::now();
	}
	// ���������ɶ�
	auto end = high_resolution_clock::now();
	// �p��ɶ��t���ഫ����
    auto duration = duration_cast<nanoseconds>(end - start);
	average_time[0]+=duration.count()/1e9;	// �֭p����ɶ��]���G��^
	if(duration.count()/1e9>5*60){
		f[0]=1;
	}
}



template<class T>
void twoway(T* a, T* b, int na, int nb){
   // a[ ]: left sorted array, and resulting sorted array
   // b[ ]: right sorted array
   // na: size of a[ ]
   // nb: size of b[ ]   
	T c[na+nb];        // temp resulting array
	int iLeft = 0;     // index for left sorted array
	int iRight = 0;    // index for right sorted array
	int iMerge = 0;    // index for temp array
	while( iLeft < na && iRight < nb){
		if(a[iLeft] <= b[iRight]){
			c[iMerge] = a[iLeft];
			++iLeft;
			++iMerge;
		}else{
			c[iMerge] = b[iRight];
			++iRight;
			++iMerge;
		}
	}
	// if there are remaining in left array
	while(iLeft < na){
		c[iMerge] = a[iLeft];
		++iLeft;
		++iMerge;
	}
	// if there are remaining in right array
	while(iRight < nb){
		c[iMerge] = b[iRight];
		++iRight;
		++iMerge;
	}
	// copy temp resulting array into a[ ]
	for(int i=0 ; i < na+nb ; ++i){
		a[i] = c[i];
	}
}
// recursive merge sort
template<class T>
void merge_sort(T& a, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(a, left, mid); // ���j�Ƨǥ��b����
        merge_sort(a, mid + 1, right); // ���j�Ƨǥk�b����
        twoway(&a[left], &a[mid + 1], mid - left + 1, right - mid); // �X�}��Ӥw�ƧǪ��ǦC 
    }
}

//void merge_sort(vector<int> &v){
//	
//}

// ��� Hoare partition scheme ���ֳt�ƧǡA���T���N��F 
//void quick_sort(vector<int> &v, int left, int right) {
//    if (left < right) {
//        int pivot = v[(left + right) / 2];  // ��ܤ��Ϥ���
//        int i = left-1;
//        int j = right+1;
//        
//        while (1) {
//            // ���j��϶b������
//            i++;
//            while (v[i] < pivot)	i++;
//            // ���p��϶b������
//            j--;
//			while (v[j] > pivot)	j--;
//            // �p�G i �M j ����A�h��^
//            if (i >= j) {
//                break;
//            }
//            // �洫��Ӥ���
//            swap(v[i], v[j]);
//        }
//
//        // ���j�Ƨǥ��b��M�k�b��
//        quick_sort(v, left, j);
//        quick_sort(v, j + 1, right);
//    }
//}




//void quick_sort(vector<int> &v,int left,int right){
//	if(left<right){
//		int pivot=v[left];
//		int i=left+1;
//		int j=right;
//		
//		while(i<j){		//�@���j��O�洫�@����ӼƦr
//		
//			while(i<=j&&v[i]<pivot)	i++;	//�ni<j�A���M�|�q���T�����Y�洫���������Y�A�����չL 
//			while(i<=j&&v[j]>pivot)	j--;	
//			
//			if(i<j){		//cout<<v[i]<<" "<<v[j]<<endl;
//				swap(v[i],v[j]);	//cout<<v[i]<<" "<<v[j]<<endl;	system("pause");
//				i++;
//				j--;
//			}
//		}
//		
//		if(v[left]>v[j])
//		swap(v[left],v[j]);
////		for (int x : v)	cout << x << " ";
////		cout << endl;
////		system("pause");
//		
//		quick_sort(v,left,j-1);
//		quick_sort(v,j+1,right);
//	}
//}

//�ҥ��S�� 
void quick_sort(vector<int> &v,int left, int right){ 
  if (left < right) { 
   int i = left, j = right + 1, pivot = v[left]; 
   do{ 
    do i++; while (v[i] < pivot); 
    do j--; while (v[j] > pivot); 
     if (i<j) swap(v[i], v[j]); 
   } while (i < j); 
   swap(v[left], v[j]);
   
	 quick_sort(v,left, j-1); 
   quick_sort(v,j+1, right); 
  } 
}


//C++�ɾާ@(�ɥR)
//1.�����ϥάy��H�i���ɪ��ާ@�A�w�]�覡�p�U�G
//ofstream out("...", ios::out);
//ifstream in("...", ios::in);
//fstream foi("...", ios::in|ios::out);
