#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <map>
#include <string>
#include <vector>
#define uChar unsigned char

using namespace std;

// 定義 HuffmanNode 類別，用於建立 Huffman 樹的節點
class HuffmanNode
{
public:
	HuffmanNode(uChar, int);	// 構造函式，用於初始化單一字節的 Huffman 節點
	HuffmanNode(HuffmanNode *, HuffmanNode *);	// 構造函式，用於合併兩個節點生成新的 Huffman 節點
	int frequency;	// 該節點的頻率
	uChar byteCode;	// 該節點對應的字節碼
	std::string decompressCode;	// 該節點的解壓碼，編碼
	HuffmanNode *parent, *left, *right;	// 父節點、左子節點、右子節點
};

// 合併 Huffman 樹，將各個字節節點按頻率合併為一顆樹
static HuffmanNode *mergeHuffmanTree(map<uChar, int> &nodeTable);

// 分配壓縮碼，同時收集葉節點
static void assignCompressCode(HuffmanNode *current, string code);

// 遞迴方法，收集 Huffman 樹中的葉節點
static void recordingLeafs(HuffmanNode *current, vector<HuffmanNode *> &leafs);

// 將 Huffman 樹葉節點轉換為編碼數據
static void encoding(vector<HuffmanNode *> &leafs,
					 vector<uChar> &rawData,
					 vector<bool> &encodedData);

// 解碼函式，將二進位字串轉換為原始的字節
static string decoding(map<string, uChar> &_table, string &bitStringData);

// 將壓縮結果寫入檔案
static void writeCompressResult(string inputFileName,
								int originSize,
								HuffmanNode *root,
								vector<uChar> &rawData);

// 壓縮函式，接收檔案名稱並執行壓縮操作
bool compress(string fileName);

// 解壓函式，接收檔案名稱並執行解壓操作
bool decompress(string fileName);

#endif

