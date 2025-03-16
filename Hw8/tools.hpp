#ifndef TOOLS
#define TOOLS
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "huffmanLib.hpp"

namespace tools
{
	using namespace std;

	// 開啟檔案並讀取內容至 vector<uChar>，回傳檔案是否成功開啟
	bool openToVector(string fileName, vector<uChar> &rawData)
	{
		ifstream inFile(fileName, ios::in | ios::binary); // 開啟檔案為二進位讀取模式
		if (inFile.fail())
			throw "Read File Error"; // 檔案開啟失敗時拋出異常
		if (inFile.good())
			rawData = vector<uChar>(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>()); // 將檔案內容讀取到 vector
		//像是rawData = {'A', 'B', 'C', '\n', 'D', 'E', 'F'}; 
		inFile.close(); // 關閉檔案
		return inFile.good(); // 回傳檔案是否開啟成功
		
	}

	// 比較 Huffman 節點，根據頻率及位元碼排序
	struct cmpNodes {
		bool operator()(const HuffmanNode *lhs, const HuffmanNode *rhs)
		{
			if (lhs->frequency != rhs->frequency)
				return lhs->frequency > rhs->frequency; // 頻率較高者排序後，如同 priority_queue 的寫法
			return lhs->byteCode > rhs->byteCode; // 頻率相同則依位元碼排序
		}
	};	//priority_queue默認是最大在前，所以要自定義 

	// 將字節陣列附加到目標 vector 中
	inline void appendByteArray(const uChar *arr, int arrSize, vector<uChar> &_dest)
	{
		for (int i = 0; i < arrSize; i++)
			_dest.push_back(arr[i]); // 將陣列的每個元素加入目標 vector
	}

	// 計算填充位元長度
	inline int getPaddingLength(int _value)
	{
		return ((int(_value / 8) + 1) * 8 - _value) % 8; // 計算補齊至 8 位元所需的填充數量
	}

	// 將資料向前移動指定步數
	inline void stepForward(vector<uChar> &_data, int steps)
	{
		_data.erase(_data.begin(), _data.begin() + steps); // 刪除指定數量的起始元素
	}

	// 列印編碼表 (用 HuffmanNode 指標的 vector)，是用這個 
	inline void printCodingTable(vector<HuffmanNode *> &records)
	{
		for (auto i : records)
			cout << (char) i->byteCode << " " << i->decompressCode << endl; // 列印每個節點的位元碼和解碼字串
	}

	// 列印解碼表 (用 map 儲存解碼字串及對應字節)
	inline void printCodingTable(map<string, uChar> &decodeTable)
	{
		for (auto i : decodeTable)
			cout << i.second << " " << i.first << endl; // 列印字節及對應的解碼字串
	}

	// 以整數形式檢視字節陣列，每行顯示指定數量元素
	void viewByteAsINT(vector<uChar> &bytesArray, int elementsPerLine = 20)
	{
		unsigned int counter = 0;
		for (auto i : bytesArray) {
			cout << int(i) << "|\t"; // 輸出每個字節的整數值
			if ((++counter) % elementsPerLine == 0)
				cout << "\n"; // 每行到達限制時換行
		}
		cout << endl;
	}

	// 將整數轉換為字節陣列
	pair<uChar *, int> toByteArray(size_t _value)
	{
		uChar *arr = new uChar[sizeof(_value)](); // 分配字節陣列
		memcpy(arr, &_value, sizeof(_value)); // 複製數值到字節陣列
		return make_pair(arr, sizeof(_value));
	}

	// 將浮點數轉換為字節陣列
	pair<uChar *, int> toByteArray(float _value)
	{
		uChar *arr = new uChar[sizeof(_value)](); // 分配字節陣列
		memcpy(arr, &_value, sizeof(_value)); // 複製數值到字節陣列
		return make_pair(arr, sizeof(float));
	}

	// 將可迭代資料轉換為字節陣列
	template <typename Iterable>
	pair<uChar *, int> toByteArray(const Iterable &data)
	{
		int arrSize = data.size() / 8; // 計算字節陣列大小
		uChar *arr = new uChar[arrSize]();
		unsigned int counter = 0, bitBuffer = 0;
		for (auto i : data) {
			bitBuffer <<= 1;
			bitBuffer += (i + '0') % 2;

			if ((counter % 8 == 7) && counter) {
				arr[(counter) / 8] = char(bitBuffer); // 儲存完整的字節
				bitBuffer = 0;
			}
			counter++;
		}
		return make_pair(arr, arrSize);
	}

	// 將字節陣列轉換為位元字串
	string toBitString(uChar *arr, int arrSize, int paddingLength)
	{
		string tmp;
		string result;
		for (int i = 0; i < arrSize; i++) {
			uChar oneByteBuffer = 0;
			memcpy(&oneByteBuffer, &arr[i], sizeof(uChar)); // 讀取每個字節
			for (int j = 0; j < 8; j++) {
				tmp.push_back(char(abs((oneByteBuffer % 2)) + '0')); // 取得每個位元
				oneByteBuffer /= 2;
			}
			reverse(tmp.begin(), tmp.end()); // 倒序後加入結果
			result.append(tmp);
			tmp = "";
		}
		result.erase(result.end() - paddingLength, result.end()); // 刪除填充位元
		return result;
	}

	// 將 vector 的字節陣列轉換為位元字串
	string toBitString(vector<uChar> &rawData, int paddingLength)
	{
		return toBitString(&rawData[0], rawData.size(), paddingLength); // 調用函式處理
	}

	// 寫入檔案頭資訊
	void writeHeader(ofstream &outFile,
					size_t originSize,
					size_t compressSize,
					vector<HuffmanNode *> leafs)
	{
		float compressRate = compressSize * 1.0 / originSize; // 計算壓縮率
		vector<uChar> headerBytes;

		auto [origin, originArraySize] = toByteArray(originSize);
		appendByteArray(origin, originArraySize, headerBytes);
		delete[] origin;
		auto [compressed, compressedArraySize] = toByteArray(compressSize);
		appendByteArray(compressed, compressedArraySize, headerBytes);
		delete[] compressed;
		auto [rate, rateArraySize] = toByteArray(compressRate);
		appendByteArray(rate, rateArraySize, headerBytes);
		delete[] rate;

		// 壓縮表大小及填充長度
		headerBytes.push_back(char(leafs.size() % 256)); // 寫入壓縮表大小
		int paddingLength = getPaddingLength(compressSize);
		headerBytes.push_back(char(paddingLength)); // 填充長度

		// 編碼表內容
		for (auto i : leafs) {
			headerBytes.push_back(i->byteCode); // 壓縮的字節
			headerBytes.push_back(char(i->decompressCode.length() % 256)); // 編碼長度
			paddingLength = getPaddingLength(i->decompressCode.length());
			auto code = i->decompressCode;
			for (int j = 0; j < paddingLength; j++)
				code.append("0"); // 補齊填充

			auto [encodeArray, encodeArraySize] = toByteArray(code);
			appendByteArray(encodeArray, encodeArraySize, headerBytes);
			delete[] encodeArray;
		}

		// 寫入檔案
		for (auto i : headerBytes)
			outFile << i;
	}

	// 讀取檔案頭資訊
	auto readHeader(vector<uChar> &rawData)
	{
		size_t originSize = 0, compressBitsLength = 0;
		int codingTableSize = 0, dataPaddingLength = 0;

		originSize = *((size_t *) (&(rawData[0]))); // 讀取原始大小
		stepForward(rawData, sizeof(size_t)); //跳過原始大小 
		compressBitsLength = *((size_t *) (&(rawData[0]))); // 讀取壓縮後大小(位元長度) 
		stepForward(rawData, sizeof(size_t)); //跳過壓縮後大小 
		stepForward(rawData, sizeof(float)); // 跳過壓縮率 rate

//int a=v.at(0); 返回 v 向量第0個的元素，超出範圍會報錯 
		codingTableSize = int(rawData.at(0)); // 讀取解碼表大小(前面的壓縮表) 
		stepForward(rawData, sizeof(char));
		dataPaddingLength = int(rawData.at(0)); // 讀取填充位元
		stepForward(rawData, sizeof(char));

		return make_tuple(originSize, compressBitsLength, codingTableSize, dataPaddingLength);
	}

	// 讀取解碼表
	void readDecodeTable(vector<uChar> &rawData, map<string, uChar> &decodeTable, int decodingTableSize)
	{
		if (decodingTableSize == 0)
			decodingTableSize = 256; // 預設大小為 256
		for (int i = 0; i < decodingTableSize; i++) {
			uChar element = rawData.at(0); // 字節內容
			int codingLength = int(rawData.at(1)); // 編碼長度
			int paddingLength = getPaddingLength(codingLength);
			int totalBytes = (codingLength + paddingLength) / 8;

			uChar *codingBuffer = new uChar[totalBytes]();
			for (int j = 0; j < totalBytes; j++)
				codingBuffer[j] = rawData.at(j + 2); // 讀取編碼內容
			string code = toBitString(codingBuffer, totalBytes, paddingLength);
			decodeTable.insert(make_pair(code, element)); // 新增至解碼表

			delete[] codingBuffer;
			stepForward(rawData, totalBytes + 2); // 向前移動至下一組
		}
	}

} // namespace tools
#endif

