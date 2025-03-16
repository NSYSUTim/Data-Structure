#include <algorithm>
#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "tools.hpp"
#define uChar unsigned char
using namespace std;

// HuffmanNode 的構造函式，用於單一字節節點
HuffmanNode::HuffmanNode(uChar _singleByte, int _frequency)
	: frequency(_frequency), byteCode(_singleByte)
{
	parent = left = right = nullptr; // 初始化父節點與左右子節點為空指標
}

// 合併節點
HuffmanNode::HuffmanNode(HuffmanNode *leftNode, HuffmanNode *rightNode)
{
	frequency = leftNode->frequency + rightNode->frequency; // 合併兩節點的頻率
	leftNode->parent = rightNode->parent = this; // 設定左右子節點的父節點
	left = (leftNode->byteCode <= rightNode->byteCode) ? leftNode : rightNode; // 按照字節碼排序，較小的在左
	right = (leftNode->byteCode > rightNode->byteCode) ? leftNode : rightNode; // 較大的在右
	parent = nullptr; // 合併節點的父節點設為空
	byteCode = ((int(left->byteCode) + int(right->byteCode)) / 2) % (1 << 8); // 計算合併節點的字節碼
}

// 讀取檔案內容到向量，成功返回 true
static bool getFile(string fileName, vector<uChar> &rawData)
{
	bool isGood = false; // 是否成功打開檔案的標誌
	try {
		isGood = tools::openToVector(fileName, rawData); // 使用工具函式讀取檔案
	} catch (const exception &e) {
		cerr << e.what() << '\n'; // 捕捉例外並輸出錯誤訊息
	}
	return isGood;
}

// 合併生成 Huffman 樹，返回根節點
static HuffmanNode *mergeHuffmanTree(map<uChar, int> &nodeTable)
{
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, tools::cmpNodes> pq; // 優先佇列，用於合併節點
	for (auto i : nodeTable) {
		auto newNode = new HuffmanNode(i.first, i.second); // 建立新節點
		pq.push(newNode); // 添加到優先佇列中
	}
	while (pq.size() > 1) { // 當佇列中至少有兩個節點時
		auto a = pq.top(); pq.pop(); // 取出頻率最小的兩個節點
		auto b = pq.top(); pq.pop();

		auto mergedNode = new HuffmanNode(a, b); // 合併這兩個節點
		pq.push(mergedNode); // 將合併後的節點重新放回佇列
	}

	return pq.top(); // 返回 Huffman 樹的根節點
}

// 為每個葉節點分配壓縮碼
static void assignCompressCode(HuffmanNode *current, string code)
{
	if (current->left) // 如果有左子節點，遞迴分配壓縮碼
		assignCompressCode(current->left, code + "0");
	if (current->left == nullptr && current->right == nullptr) // 如果是葉節點
		current->decompressCode = code; // 設定解壓碼
	if (current->right) // 如果有右子節點，遞迴分配壓縮碼
		assignCompressCode(current->right, code + "1");
}

// 收集所有葉節點到向量中
static void recordingLeafs(HuffmanNode *current, vector<HuffmanNode *> &leafs)
{
	if (current->left) // 如果有左子節點，遞迴搜尋
		recordingLeafs(current->left, leafs);
	if (current->left == nullptr && current->right == nullptr) // 如果是葉節點
		leafs.push_back(current); // 添加到葉節點向量
	if (current->right) // 如果有右子節點，遞迴搜尋
		recordingLeafs(current->right, leafs);
}

// 將原始數據編碼為二進位格式
static void encoding(vector<HuffmanNode *> &leafs,
					 vector<uChar> &rawData,
					 vector<bool> &encodedData)
{
	map<uChar, string> encodingTable; // 建立字節到壓縮碼的映射表
	for (auto i : leafs)
		encodingTable.insert(
			pair<uChar, string>(i->byteCode, i->decompressCode));

	for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {
		auto getCode = encodingTable.at(*iter); // 查詢每個字節的壓縮碼
		for (auto i : getCode)
			encodedData.push_back(i - '0'); // 將壓縮碼存入編碼數據
	}
}

// 解碼二進位格式為原始字串
static string decoding(map<string, uChar> &_table, string &bitStringData)
{
	string tmp, result; // 暫存字串與解碼結果
	for (auto iter = bitStringData.begin(); iter != bitStringData.end(); iter++) {
		tmp.push_back(*iter); // 將每一位加入暫存
		auto isFound = _table.find(tmp); // 查詢是否存在解碼對應
		if (isFound != _table.end()) {//如果有找到
			tmp = ""; // 清空暫存
			result.push_back(char(isFound->second)); // 將解碼結果加入字串
		}//沒找到就保留tmp，繼續加入下一位查找 
	}
	return result;
}

// 將壓縮結果寫入檔案
static void writeCompressResult(string inputFileName,
								vector<HuffmanNode *> leafs,
								vector<uChar> &rawData)
{
	vector<bool> encodedData; // 壓縮後的二進位數據
	string outputName(inputFileName.append(".compress")); // 壓縮檔案名稱
	ofstream outFile(outputName);

	try {
		encoding(leafs, rawData, encodedData); // 執行編碼
	} catch (const std::exception &e) {
		std::cerr << e.what() << endl; // 捕捉例外並輸出錯誤訊息
	}

	tools::writeHeader(outFile, rawData.size(), encodedData.size(), leafs); // 寫入檔案頭
	int peddingDataLength = tools::getPaddingLength(encodedData.size()); // 計算填充位數
	for (int i = 0; i < peddingDataLength; i++)
		encodedData.push_back(0); // 在後面補 0 讓位數是 8 的倍數 

	vector<uChar> bodyBytes;
	auto [encodedDataByteArray, encodedDataByteArraySize] =
		tools::toByteArray(encodedData); // 將編碼數據從bool型態換成字元陣列encodedDataByteArray
	tools::appendByteArray(encodedDataByteArray, encodedDataByteArraySize,
						   bodyBytes); // encodedDataByteArray副值給 bodyBytes
	delete[] encodedDataByteArray; // 釋放動態分配的記憶體
	for (auto i : bodyBytes)
		outFile << i; // 將字節數據寫入檔案

	outFile.close(); // 關閉檔案
}

// 壓縮主函式
bool compress(string fileName) {
	vector<uChar> rawData;
	vector<HuffmanNode *> leafs;
	HuffmanNode *root;
	bool isGoodFile = true;

	// 讀取原始檔案到 rawData 向量
	isGoodFile = getFile(fileName, rawData);//這裡rawData 向量就是原本檔案裡的內容 

	// 收集字節頻率到 map 中
	map<uChar, int> nodeTable; // 存儲字節與頻率
	for (auto singleByte : rawData) {
		nodeTable[singleByte]++; // 計算每個字節的頻率
	}

	root = mergeHuffmanTree(nodeTable); // 合併生成 Huffman 樹
	assignCompressCode(root, "");       // 為每個節點分配壓縮碼
	recordingLeafs(root, leafs);        // 收集葉節點
	writeCompressResult(fileName, leafs, rawData);  // 寫入壓縮結果

	// 計算壓縮後的檔案大小
	string compressedFileName = fileName + ".compress";
	ifstream compressedFile(compressedFileName, ios::binary | ios::ate);
	auto compressedSize = compressedFile.tellg();
	compressedFile.close();

	// 在標準輸出中顯示壓縮資訊
	cout << "Original file size: " << rawData.size() << " bytes\n";
	cout << "Compressed file size: " << compressedSize << " bytes\n";
	cout << "Compression ratio: " << (100.0 * compressedSize / rawData.size()) << "%\n";
	tools::printCodingTable(leafs);

	return isGoodFile; // 返回檔案是否成功讀取
}

// 解壓主函式
bool decompress(string fileName)
{
	vector<uChar> rawData;
	bool isGoodFile = true;
	HuffmanNode *root;
	map<string, uChar> stringTable; //編碼表 

	// 讀取原始檔案到rawData向量
	isGoodFile = getFile(fileName, rawData);//這裡取得的rawdata是壓縮檔裡的內容，跟前面不一樣 

	auto [originSize, compressBitsLength, codingTableSize, dataPeddingLength] =
		tools::readHeader(rawData); // 解析檔案頭
	tools::readDecodeTable(rawData, stringTable, codingTableSize); // 讀取解碼表stringTable

	string bitStringData = tools::toBitString(rawData, dataPeddingLength); // 編碼表的編碼部份轉為01字串
	rawData.clear();
	rawData.shrink_to_fit();

	string decodedResult = decoding(stringTable, bitStringData); // 解碼數據
	// cout << decodedResult;

	ofstream outFile(fileName + string(".decompress")); // 建立解壓檔案
	outFile << decodedResult;
	outFile.close();

	// 確認解壓結果是否與壓縮前一致
	return (decodedResult.length() == originSize) && isGoodFile;
}

