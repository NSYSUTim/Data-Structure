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

	// �}���ɮר�Ū�����e�� vector<uChar>�A�^���ɮ׬O�_���\�}��
	bool openToVector(string fileName, vector<uChar> &rawData)
	{
		ifstream inFile(fileName, ios::in | ios::binary); // �}���ɮ׬��G�i��Ū���Ҧ�
		if (inFile.fail())
			throw "Read File Error"; // �ɮ׶}�ҥ��ѮɩߥX���`
		if (inFile.good())
			rawData = vector<uChar>(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>()); // �N�ɮפ��eŪ���� vector
		//���OrawData = {'A', 'B', 'C', '\n', 'D', 'E', 'F'}; 
		inFile.close(); // �����ɮ�
		return inFile.good(); // �^���ɮ׬O�_�}�Ҧ��\
		
	}

	// ��� Huffman �`�I�A�ھ��W�v�Φ줸�X�Ƨ�
	struct cmpNodes {
		bool operator()(const HuffmanNode *lhs, const HuffmanNode *rhs)
		{
			if (lhs->frequency != rhs->frequency)
				return lhs->frequency > rhs->frequency; // �W�v�����̱Ƨǫ�A�p�P priority_queue ���g�k
			return lhs->byteCode > rhs->byteCode; // �W�v�ۦP�h�̦줸�X�Ƨ�
		}
	};	//priority_queue�q�{�O�̤j�b�e�A�ҥH�n�۩w�q 

	// �N�r�`�}�C���[��ؼ� vector ��
	inline void appendByteArray(const uChar *arr, int arrSize, vector<uChar> &_dest)
	{
		for (int i = 0; i < arrSize; i++)
			_dest.push_back(arr[i]); // �N�}�C���C�Ӥ����[�J�ؼ� vector
	}

	// �p���R�줸����
	inline int getPaddingLength(int _value)
	{
		return ((int(_value / 8) + 1) * 8 - _value) % 8; // �p��ɻ��� 8 �줸�һݪ���R�ƶq
	}

	// �N��ƦV�e���ʫ��w�B��
	inline void stepForward(vector<uChar> &_data, int steps)
	{
		_data.erase(_data.begin(), _data.begin() + steps); // �R�����w�ƶq���_�l����
	}

	// �C�L�s�X�� (�� HuffmanNode ���Ъ� vector)�A�O�γo�� 
	inline void printCodingTable(vector<HuffmanNode *> &records)
	{
		for (auto i : records)
			cout << (char) i->byteCode << " " << i->decompressCode << endl; // �C�L�C�Ӹ`�I���줸�X�M�ѽX�r��
	}

	// �C�L�ѽX�� (�� map �x�s�ѽX�r��ι����r�`)
	inline void printCodingTable(map<string, uChar> &decodeTable)
	{
		for (auto i : decodeTable)
			cout << i.second << " " << i.first << endl; // �C�L�r�`�ι������ѽX�r��
	}

	// �H��ƧΦ��˵��r�`�}�C�A�C����ܫ��w�ƶq����
	void viewByteAsINT(vector<uChar> &bytesArray, int elementsPerLine = 20)
	{
		unsigned int counter = 0;
		for (auto i : bytesArray) {
			cout << int(i) << "|\t"; // ��X�C�Ӧr�`����ƭ�
			if ((++counter) % elementsPerLine == 0)
				cout << "\n"; // �C���F����ɴ���
		}
		cout << endl;
	}

	// �N����ഫ���r�`�}�C
	pair<uChar *, int> toByteArray(size_t _value)
	{
		uChar *arr = new uChar[sizeof(_value)](); // ���t�r�`�}�C
		memcpy(arr, &_value, sizeof(_value)); // �ƻs�ƭȨ�r�`�}�C
		return make_pair(arr, sizeof(_value));
	}

	// �N�B�I���ഫ���r�`�}�C
	pair<uChar *, int> toByteArray(float _value)
	{
		uChar *arr = new uChar[sizeof(_value)](); // ���t�r�`�}�C
		memcpy(arr, &_value, sizeof(_value)); // �ƻs�ƭȨ�r�`�}�C
		return make_pair(arr, sizeof(float));
	}

	// �N�i���N����ഫ���r�`�}�C
	template <typename Iterable>
	pair<uChar *, int> toByteArray(const Iterable &data)
	{
		int arrSize = data.size() / 8; // �p��r�`�}�C�j�p
		uChar *arr = new uChar[arrSize]();
		unsigned int counter = 0, bitBuffer = 0;
		for (auto i : data) {
			bitBuffer <<= 1;
			bitBuffer += (i + '0') % 2;

			if ((counter % 8 == 7) && counter) {
				arr[(counter) / 8] = char(bitBuffer); // �x�s���㪺�r�`
				bitBuffer = 0;
			}
			counter++;
		}
		return make_pair(arr, arrSize);
	}

	// �N�r�`�}�C�ഫ���줸�r��
	string toBitString(uChar *arr, int arrSize, int paddingLength)
	{
		string tmp;
		string result;
		for (int i = 0; i < arrSize; i++) {
			uChar oneByteBuffer = 0;
			memcpy(&oneByteBuffer, &arr[i], sizeof(uChar)); // Ū���C�Ӧr�`
			for (int j = 0; j < 8; j++) {
				tmp.push_back(char(abs((oneByteBuffer % 2)) + '0')); // ���o�C�Ӧ줸
				oneByteBuffer /= 2;
			}
			reverse(tmp.begin(), tmp.end()); // �˧ǫ�[�J���G
			result.append(tmp);
			tmp = "";
		}
		result.erase(result.end() - paddingLength, result.end()); // �R����R�줸
		return result;
	}

	// �N vector ���r�`�}�C�ഫ���줸�r��
	string toBitString(vector<uChar> &rawData, int paddingLength)
	{
		return toBitString(&rawData[0], rawData.size(), paddingLength); // �եΨ禡�B�z
	}

	// �g�J�ɮ��Y��T
	void writeHeader(ofstream &outFile,
					size_t originSize,
					size_t compressSize,
					vector<HuffmanNode *> leafs)
	{
		float compressRate = compressSize * 1.0 / originSize; // �p�����Y�v
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

		// ���Y��j�p�ζ�R����
		headerBytes.push_back(char(leafs.size() % 256)); // �g�J���Y��j�p
		int paddingLength = getPaddingLength(compressSize);
		headerBytes.push_back(char(paddingLength)); // ��R����

		// �s�X���e
		for (auto i : leafs) {
			headerBytes.push_back(i->byteCode); // ���Y���r�`
			headerBytes.push_back(char(i->decompressCode.length() % 256)); // �s�X����
			paddingLength = getPaddingLength(i->decompressCode.length());
			auto code = i->decompressCode;
			for (int j = 0; j < paddingLength; j++)
				code.append("0"); // �ɻ���R

			auto [encodeArray, encodeArraySize] = toByteArray(code);
			appendByteArray(encodeArray, encodeArraySize, headerBytes);
			delete[] encodeArray;
		}

		// �g�J�ɮ�
		for (auto i : headerBytes)
			outFile << i;
	}

	// Ū���ɮ��Y��T
	auto readHeader(vector<uChar> &rawData)
	{
		size_t originSize = 0, compressBitsLength = 0;
		int codingTableSize = 0, dataPaddingLength = 0;

		originSize = *((size_t *) (&(rawData[0]))); // Ū����l�j�p
		stepForward(rawData, sizeof(size_t)); //���L��l�j�p 
		compressBitsLength = *((size_t *) (&(rawData[0]))); // Ū�����Y��j�p(�줸����) 
		stepForward(rawData, sizeof(size_t)); //���L���Y��j�p 
		stepForward(rawData, sizeof(float)); // ���L���Y�v rate

//int a=v.at(0); ��^ v �V�q��0�Ӫ������A�W�X�d��|���� 
		codingTableSize = int(rawData.at(0)); // Ū���ѽX��j�p(�e�������Y��) 
		stepForward(rawData, sizeof(char));
		dataPaddingLength = int(rawData.at(0)); // Ū����R�줸
		stepForward(rawData, sizeof(char));

		return make_tuple(originSize, compressBitsLength, codingTableSize, dataPaddingLength);
	}

	// Ū���ѽX��
	void readDecodeTable(vector<uChar> &rawData, map<string, uChar> &decodeTable, int decodingTableSize)
	{
		if (decodingTableSize == 0)
			decodingTableSize = 256; // �w�]�j�p�� 256
		for (int i = 0; i < decodingTableSize; i++) {
			uChar element = rawData.at(0); // �r�`���e
			int codingLength = int(rawData.at(1)); // �s�X����
			int paddingLength = getPaddingLength(codingLength);
			int totalBytes = (codingLength + paddingLength) / 8;

			uChar *codingBuffer = new uChar[totalBytes]();
			for (int j = 0; j < totalBytes; j++)
				codingBuffer[j] = rawData.at(j + 2); // Ū���s�X���e
			string code = toBitString(codingBuffer, totalBytes, paddingLength);
			decodeTable.insert(make_pair(code, element)); // �s�W�ܸѽX��

			delete[] codingBuffer;
			stepForward(rawData, totalBytes + 2); // �V�e���ʦܤU�@��
		}
	}

} // namespace tools
#endif

