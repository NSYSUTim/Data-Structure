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

// HuffmanNode ���c�y�禡�A�Ω��@�r�`�`�I
HuffmanNode::HuffmanNode(uChar _singleByte, int _frequency)
	: frequency(_frequency), byteCode(_singleByte)
{
	parent = left = right = nullptr; // ��l�Ƥ��`�I�P���k�l�`�I���ū���
}

// �X�ָ`�I
HuffmanNode::HuffmanNode(HuffmanNode *leftNode, HuffmanNode *rightNode)
{
	frequency = leftNode->frequency + rightNode->frequency; // �X�֨�`�I���W�v
	leftNode->parent = rightNode->parent = this; // �]�w���k�l�`�I�����`�I
	left = (leftNode->byteCode <= rightNode->byteCode) ? leftNode : rightNode; // ���Ӧr�`�X�ƧǡA���p���b��
	right = (leftNode->byteCode > rightNode->byteCode) ? leftNode : rightNode; // ���j���b�k
	parent = nullptr; // �X�ָ`�I�����`�I�]����
	byteCode = ((int(left->byteCode) + int(right->byteCode)) / 2) % (1 << 8); // �p��X�ָ`�I���r�`�X
}

// Ū���ɮפ��e��V�q�A���\��^ true
static bool getFile(string fileName, vector<uChar> &rawData)
{
	bool isGood = false; // �O�_���\���}�ɮת��лx
	try {
		isGood = tools::openToVector(fileName, rawData); // �ϥΤu��禡Ū���ɮ�
	} catch (const exception &e) {
		cerr << e.what() << '\n'; // �����ҥ~�ÿ�X���~�T��
	}
	return isGood;
}

// �X�֥ͦ� Huffman ��A��^�ڸ`�I
static HuffmanNode *mergeHuffmanTree(map<uChar, int> &nodeTable)
{
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, tools::cmpNodes> pq; // �u����C�A�Ω�X�ָ`�I
	for (auto i : nodeTable) {
		auto newNode = new HuffmanNode(i.first, i.second); // �إ߷s�`�I
		pq.push(newNode); // �K�[���u����C��
	}
	while (pq.size() > 1) { // ���C���ܤ֦���Ӹ`�I��
		auto a = pq.top(); pq.pop(); // ���X�W�v�̤p����Ӹ`�I
		auto b = pq.top(); pq.pop();

		auto mergedNode = new HuffmanNode(a, b); // �X�ֳo��Ӹ`�I
		pq.push(mergedNode); // �N�X�᪺֫�`�I���s��^��C
	}

	return pq.top(); // ��^ Huffman �𪺮ڸ`�I
}

// ���C�Ӹ��`�I���t���Y�X
static void assignCompressCode(HuffmanNode *current, string code)
{
	if (current->left) // �p�G�����l�`�I�A���j���t���Y�X
		assignCompressCode(current->left, code + "0");
	if (current->left == nullptr && current->right == nullptr) // �p�G�O���`�I
		current->decompressCode = code; // �]�w�����X
	if (current->right) // �p�G���k�l�`�I�A���j���t���Y�X
		assignCompressCode(current->right, code + "1");
}

// �����Ҧ����`�I��V�q��
static void recordingLeafs(HuffmanNode *current, vector<HuffmanNode *> &leafs)
{
	if (current->left) // �p�G�����l�`�I�A���j�j�M
		recordingLeafs(current->left, leafs);
	if (current->left == nullptr && current->right == nullptr) // �p�G�O���`�I
		leafs.push_back(current); // �K�[�츭�`�I�V�q
	if (current->right) // �p�G���k�l�`�I�A���j�j�M
		recordingLeafs(current->right, leafs);
}

// �N��l�ƾڽs�X���G�i��榡
static void encoding(vector<HuffmanNode *> &leafs,
					 vector<uChar> &rawData,
					 vector<bool> &encodedData)
{
	map<uChar, string> encodingTable; // �إߦr�`�����Y�X���M�g��
	for (auto i : leafs)
		encodingTable.insert(
			pair<uChar, string>(i->byteCode, i->decompressCode));

	for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {
		auto getCode = encodingTable.at(*iter); // �d�ߨC�Ӧr�`�����Y�X
		for (auto i : getCode)
			encodedData.push_back(i - '0'); // �N���Y�X�s�J�s�X�ƾ�
	}
}

// �ѽX�G�i��榡����l�r��
static string decoding(map<string, uChar> &_table, string &bitStringData)
{
	string tmp, result; // �Ȧs�r��P�ѽX���G
	for (auto iter = bitStringData.begin(); iter != bitStringData.end(); iter++) {
		tmp.push_back(*iter); // �N�C�@��[�J�Ȧs
		auto isFound = _table.find(tmp); // �d�߬O�_�s�b�ѽX����
		if (isFound != _table.end()) {//�p�G�����
			tmp = ""; // �M�żȦs
			result.push_back(char(isFound->second)); // �N�ѽX���G�[�J�r��
		}//�S���N�O�dtmp�A�~��[�J�U�@��d�� 
	}
	return result;
}

// �N���Y���G�g�J�ɮ�
static void writeCompressResult(string inputFileName,
								vector<HuffmanNode *> leafs,
								vector<uChar> &rawData)
{
	vector<bool> encodedData; // ���Y�᪺�G�i��ƾ�
	string outputName(inputFileName.append(".compress")); // ���Y�ɮצW��
	ofstream outFile(outputName);

	try {
		encoding(leafs, rawData, encodedData); // ����s�X
	} catch (const std::exception &e) {
		std::cerr << e.what() << endl; // �����ҥ~�ÿ�X���~�T��
	}

	tools::writeHeader(outFile, rawData.size(), encodedData.size(), leafs); // �g�J�ɮ��Y
	int peddingDataLength = tools::getPaddingLength(encodedData.size()); // �p���R���
	for (int i = 0; i < peddingDataLength; i++)
		encodedData.push_back(0); // �b�᭱�� 0 ����ƬO 8 ������ 

	vector<uChar> bodyBytes;
	auto [encodedDataByteArray, encodedDataByteArraySize] =
		tools::toByteArray(encodedData); // �N�s�X�ƾڱqbool���A�����r���}�CencodedDataByteArray
	tools::appendByteArray(encodedDataByteArray, encodedDataByteArraySize,
						   bodyBytes); // encodedDataByteArray�ƭȵ� bodyBytes
	delete[] encodedDataByteArray; // ����ʺA���t���O����
	for (auto i : bodyBytes)
		outFile << i; // �N�r�`�ƾڼg�J�ɮ�

	outFile.close(); // �����ɮ�
}

// ���Y�D�禡
bool compress(string fileName) {
	vector<uChar> rawData;
	vector<HuffmanNode *> leafs;
	HuffmanNode *root;
	bool isGoodFile = true;

	// Ū����l�ɮר� rawData �V�q
	isGoodFile = getFile(fileName, rawData);//�o��rawData �V�q�N�O�쥻�ɮ׸̪����e 

	// �����r�`�W�v�� map ��
	map<uChar, int> nodeTable; // �s�x�r�`�P�W�v
	for (auto singleByte : rawData) {
		nodeTable[singleByte]++; // �p��C�Ӧr�`���W�v
	}

	root = mergeHuffmanTree(nodeTable); // �X�֥ͦ� Huffman ��
	assignCompressCode(root, "");       // ���C�Ӹ`�I���t���Y�X
	recordingLeafs(root, leafs);        // �������`�I
	writeCompressResult(fileName, leafs, rawData);  // �g�J���Y���G

	// �p�����Y�᪺�ɮפj�p
	string compressedFileName = fileName + ".compress";
	ifstream compressedFile(compressedFileName, ios::binary | ios::ate);
	auto compressedSize = compressedFile.tellg();
	compressedFile.close();

	// �b�зǿ�X��������Y��T
	cout << "Original file size: " << rawData.size() << " bytes\n";
	cout << "Compressed file size: " << compressedSize << " bytes\n";
	cout << "Compression ratio: " << (100.0 * compressedSize / rawData.size()) << "%\n";
	tools::printCodingTable(leafs);

	return isGoodFile; // ��^�ɮ׬O�_���\Ū��
}

// �����D�禡
bool decompress(string fileName)
{
	vector<uChar> rawData;
	bool isGoodFile = true;
	HuffmanNode *root;
	map<string, uChar> stringTable; //�s�X�� 

	// Ū����l�ɮר�rawData�V�q
	isGoodFile = getFile(fileName, rawData);//�o�̨��o��rawdata�O���Y�ɸ̪����e�A��e�����@�� 

	auto [originSize, compressBitsLength, codingTableSize, dataPeddingLength] =
		tools::readHeader(rawData); // �ѪR�ɮ��Y
	tools::readDecodeTable(rawData, stringTable, codingTableSize); // Ū���ѽX��stringTable

	string bitStringData = tools::toBitString(rawData, dataPeddingLength); // �s�X���s�X�����ର01�r��
	rawData.clear();
	rawData.shrink_to_fit();

	string decodedResult = decoding(stringTable, bitStringData); // �ѽX�ƾ�
	// cout << decodedResult;

	ofstream outFile(fileName + string(".decompress")); // �إ߸����ɮ�
	outFile << decodedResult;
	outFile.close();

	// �T�{�������G�O�_�P���Y�e�@�P
	return (decodedResult.length() == originSize) && isGoodFile;
}

