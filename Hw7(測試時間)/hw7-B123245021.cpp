// 江威廷 B123245021 
// 11/21/2024
// 程式功能 : 使用不同排序演算法進行排序，並將排序後結果輸出至檔案。同時記錄不同資料量大小時各演算法之運行時間，製成表格。 

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <chrono> // 用於測量時間
#include <iomanip> // 用來設置顯示精度
#include <thread>  // 必須引入此標頭檔案來使用 std::this_thread
using namespace std::this_thread;

using namespace std;
using namespace std::chrono;	//測量時間函數需要

int f[5]={0};	//是否超時之紀錄 
double average_time[5]={0};	// A 到 E 類的排序時間，單位用秒 

// n = 21號，n = 10x + y，x=2，y=1 
void insertion_sort(vector<int>&);	//  A類 : (n mod 2)+1
template<class T>
void merge_sort(T&,int,int);	//  B類 : ((x + y) mod 2)+1 
void quick_sort(vector<int>&,int,int);	//  C類 : ((x + y * 2) mod 2)+1 
 
int comp(const void * a, const void * b){	//用於qsort 
	return ( *(int*)a - *(int*)b );		//由小到大排序 
}

//由小到大排序
int main(){
//	auto temp=high_resolution_clock::now();
//	sleep_for(seconds(10));
//	cout<<duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9<<"secs";// 轉換為秒
//	return 0;
	
	ifstream in("input_5000.txt");//讀取模式開檔
	if(!in){
		cout<<"failed to open input.txt"<<endl;	return -1;
	}
	
	// 要先開好輸出檔案，因為c++的ofstream默認開一次會清空之前的內容或自動創建空檔
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
	
	int N,times=0;	//10次
while(in>>N){
	times++;
//	cout<<N<<endl;
	vector<int> v(N);
	for(int i=0;i<N;i++){
		in>>v[i];
	}
	
	vector<int> aft_sort(N);
	aft_sort=v;	// vector 可直接指定	
	
	//  A類
	if(f[0]==0){	//如還沒超時 
		insertion_sort(aft_sort);
		out<<"Insertion sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out<<aft_sort[i]<<endl;
		if(f[0]==0)
		cout<<"Insertion sort success"<<endl;		
	}

	//  B類
	if(f[1]==0){
		aft_sort=v;	//aft_sort指定成原本未排序之序列
		auto temp=high_resolution_clock::now();
		merge_sort(aft_sort,0,aft_sort.size()-1);
		average_time[1]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;// 轉換為秒
		if(average_time[1]>5*60){	f[2]=1;	break;	}
		out2<<"Merge sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out2<<aft_sort[i]<<endl;
		cout<<"Merge sort success"<<endl;
	}
	
	//  C類
	if(f[2]==0){
		aft_sort=v;	//aft_sort指定成原本未排序之序列 
		auto temp=high_resolution_clock::now();		cout<<"Hi";
		quick_sort(aft_sort,0,aft_sort.size()-1);	cout<<"Hi";
		average_time[2]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;// 轉換為秒
		if(average_time[2]>5*60){	f[2]=1;	break;	}
		out3<<"Quick sort(N:"<<N<<")"<<endl;
		for(int i=0;i<aft_sort.size();i++)
			out3<<aft_sort[i]<<endl;
		cout<<"Quick sort success"<<endl;
	}

	//  D類
	aft_sort=v;
	auto temp=high_resolution_clock::now();
	qsort(&aft_sort[0],aft_sort.size(),sizeof(int),comp);
	average_time[3]+=duration_cast<nanoseconds>( high_resolution_clock::now()-temp ).count()/1e9;
	out4<<"C qsort()(N:"<<N<<")"<<endl;
	for(int i=0;i<aft_sort.size();i++)
		out4<<aft_sort[i]<<endl;
	cout<<"C qsort() sort success"<<endl;
	
	//  E類
	aft_sort=v;
	temp=high_resolution_clock::now();
	sort(aft_sort.begin(),aft_sort.end());	//使用c++內建函式 
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
	in.close();	// c++ 的 close 這樣寫

	cout << fixed << setprecision(6);
	
	cout<<"資料量 "<<N<<" 時，執行"<<times<<"次之平均"<<endl<<endl; 
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
	
	 // 開始計時
    auto start = high_resolution_clock::now();  // 紀錄開始時間
	
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
	// 紀錄結束時間
	auto end = high_resolution_clock::now();
	// 計算時間差並轉換為秒
    auto duration = duration_cast<nanoseconds>(end - start);
	average_time[0]+=duration.count()/1e9;	// 累計執行時間（單位：秒）
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
        merge_sort(a, left, mid); // 遞迴排序左半部分
        merge_sort(a, mid + 1, right); // 遞迴排序右半部分
        twoway(&a[left], &a[mid + 1], mid - left + 1, right - mid); // 合并兩個已排序的序列 
    }
}

//void merge_sort(vector<int> &v){
//	
//}

// 基於 Hoare partition scheme 的快速排序，正確的就對了 
//void quick_sort(vector<int> &v, int left, int right) {
//    if (left < right) {
//        int pivot = v[(left + right) / 2];  // 選擇中樞元素
//        int i = left-1;
//        int j = right+1;
//        
//        while (1) {
//            // 找到大於樞軸的元素
//            i++;
//            while (v[i] < pivot)	i++;
//            // 找到小於樞軸的元素
//            j--;
//			while (v[j] > pivot)	j--;
//            // 如果 i 和 j 交錯，則返回
//            if (i >= j) {
//                break;
//            }
//            // 交換兩個元素
//            swap(v[i], v[j]);
//        }
//
//        // 遞迴排序左半邊和右半邊
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
//		while(i<j){		//一次迴圈是交換一次兩個數字
//		
//			while(i<=j&&v[i]<pivot)	i++;	//要i<j，不然會從正確的關係交換成錯的關係，有測試過 
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

//課本沒錯 
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


//C++檔操作(補充)
//1.直接使用流對象進行檔的操作，預設方式如下：
//ofstream out("...", ios::out);
//ifstream in("...", ios::in);
//fstream foi("...", ios::in|ios::out);
