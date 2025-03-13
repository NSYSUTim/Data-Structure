#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

// �ͦ������ɮת��禡
void generate_test_file(int data_size, int groups_per_size, const string& filename) {
    ofstream out(filename); // ���}�γЫؿ�X�ɮ�
    if (!out) {
        cerr << "Failed to create " << filename << endl;
        return;
    }

    random_device rd;  // �Ω��H���ƥͦ�
    mt19937 gen(rd()); // �ϥ� Mersenne Twister �H���Ƥ���
    uniform_int_distribution<> dis(1, data_size); // �H���ƽd�� [1, 500000]

    for (int group = 0; group < groups_per_size; ++group) {
        out << data_size << endl; // �C�ժ��Ĥ@��O N
        for (int i = 0; i < data_size; ++i) {
            out << dis(gen) << endl; // �g�J�H����
        }
    }

    out.close(); // �������
    cout << "Test data for size " << data_size << " successfully written to " << filename << endl;
}

int main() {
    // �w�q���P��ƶq
    vector<int> data_sizes = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000};

    // �C�Ӹ�ƶq�����ղռ�
    int groups_per_size = 10;

    // �̾ڤ��P��ƶq�ͦ��ɮ�
    for (int size : data_sizes) {
        string filename = "input_" + to_string(size) + ".txt"; // �ʺA�R�W�ɮ�
        generate_test_file(size, groups_per_size, filename);   // ���C�Ӹ�ƶq�ͦ��ɮ�
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
//        out << n-i << endl; // �g�J�ϦV�ƧǪ��ǦC
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
//        out2 << n-i << endl; // �g�J�ϦV�ƧǪ��ǦC
//    }

   
    return 0;
}

