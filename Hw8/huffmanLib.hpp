#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <map>
#include <string>
#include <vector>
#define uChar unsigned char

using namespace std;

// �w�q HuffmanNode ���O�A�Ω�إ� Huffman �𪺸`�I
class HuffmanNode
{
public:
	HuffmanNode(uChar, int);	// �c�y�禡�A�Ω��l�Ƴ�@�r�`�� Huffman �`�I
	HuffmanNode(HuffmanNode *, HuffmanNode *);	// �c�y�禡�A�Ω�X�֨�Ӹ`�I�ͦ��s�� Huffman �`�I
	int frequency;	// �Ӹ`�I���W�v
	uChar byteCode;	// �Ӹ`�I�������r�`�X
	std::string decompressCode;	// �Ӹ`�I�������X�A�s�X
	HuffmanNode *parent, *left, *right;	// ���`�I�B���l�`�I�B�k�l�`�I
};

// �X�� Huffman ��A�N�U�Ӧr�`�`�I���W�v�X�֬��@����
static HuffmanNode *mergeHuffmanTree(map<uChar, int> &nodeTable);

// ���t���Y�X�A�P�ɦ������`�I
static void assignCompressCode(HuffmanNode *current, string code);

// ���j��k�A���� Huffman �𤤪����`�I
static void recordingLeafs(HuffmanNode *current, vector<HuffmanNode *> &leafs);

// �N Huffman �𸭸`�I�ഫ���s�X�ƾ�
static void encoding(vector<HuffmanNode *> &leafs,
					 vector<uChar> &rawData,
					 vector<bool> &encodedData);

// �ѽX�禡�A�N�G�i��r���ഫ����l���r�`
static string decoding(map<string, uChar> &_table, string &bitStringData);

// �N���Y���G�g�J�ɮ�
static void writeCompressResult(string inputFileName,
								int originSize,
								HuffmanNode *root,
								vector<uChar> &rawData);

// ���Y�禡�A�����ɮצW�٨ð������Y�ާ@
bool compress(string fileName);

// �����禡�A�����ɮצW�٨ð�������ާ@
bool decompress(string fileName);

#endif

