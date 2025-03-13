#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

// 生成測試檔案的函式
void generate_test_file(int data_size, int groups_per_size, const string& filename) {
    ofstream out(filename); // 打開或創建輸出檔案
    if (!out) {
        cerr << "Failed to create " << filename << endl;
        return;
    }

    random_device rd;  // 用於隨機數生成
    mt19937 gen(rd()); // 使用 Mersenne Twister 隨機數引擎
    uniform_int_distribution<> dis(1, data_size); // 隨機數範圍 [1, 500000]

    for (int group = 0; group < groups_per_size; ++group) {
        out << data_size << endl; // 每組的第一行是 N
        for (int i = 0; i < data_size; ++i) {
            out << dis(gen) << endl; // 寫入隨機數
        }
    }

    out.close(); // 關閉文件
    cout << "Test data for size " << data_size << " successfully written to " << filename << endl;
}

int main() {
    // 定義不同資料量
    vector<int> data_sizes = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000};

    // 每個資料量的測試組數
    int groups_per_size = 10;

    // 依據不同資料量生成檔案
    for (int size : data_sizes) {
        string filename = "input_" + to_string(size) + ".txt"; // 動態命名檔案
        generate_test_file(size, groups_per_size, filename);   // 為每個資料量生成檔案
    }
    
    //worst_case_reverse
//    string filename = "input_r500000.txt";
//    ofstream out(filename);
//    if (!out) {
//        cerr << "Failed to create " << filename << endl;
//        return 0;
//    }
//    int n=500000;
//   	out<<n<<endl;
//   	for (int i = 0; i < n ; ++i) {
//        out << n-i << endl; // 寫入反向排序的序列
//    }
    
//    string
//	filename = "input_r100.txt";
//    ofstream out2(filename);
//    if (!out2) {
//        cerr << "Failed to create " << filename << endl;
//        return 0;
//    }
////    int
//	n=100;
//   	out2<<n<<endl;
//   	for (int i = 0; i < n ; ++i) {
//        out2 << n-i << endl; // 寫入反向排序的序列
//    }

   
    return 0;
}

