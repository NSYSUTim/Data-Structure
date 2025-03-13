#include <windows.h> 
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

// �w�q Huffman �`�I���c
struct HuffmanNode {
    char ch;  
    int freq; 
    HuffmanNode* left;  
    HuffmanNode* right; 

    HuffmanNode(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// ������c�A�Ω�̤p��
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq; 
    }
};

// �Ψӥͦ� Huffman �s�X
void generateHuffmanCodes(HuffmanNode* root, std::string str, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root) return;  
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str; 
    }
    generateHuffmanCodes(root->left, str + "0", huffmanCodes);  
    generateHuffmanCodes(root->right, str + "1", huffmanCodes); 
}

// �ΨӺc�� Huffman ��
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();  
        HuffmanNode* right = minHeap.top(); minHeap.pop(); 
        HuffmanNode* internalNode = new HuffmanNode('\0', left->freq + right->freq); 
        internalNode->left = left;
        internalNode->right = right;
        minHeap.push(internalNode);  
    }

    return minHeap.top();  
}

// ���Y�ɮ�
void compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);
    
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    // �p��C�Ӧr�����W�v
    std::unordered_map<char, int> freqMap;
    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
    }

    // �ͦ� Huffman ��ño��s�X
    HuffmanNode* root = buildHuffmanTree(freqMap);
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // �x�s�ɮ��Y����T�G�s�X��P��l�ɮפj�p
    outFile << "Encoding Table:\n";
    for (const auto& pair : huffmanCodes) {
        outFile << pair.first << "=" << pair.second << "\n";
    }

    // �x�s���Y���
    std::vector<bool> bitstream;
    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    while (inFile.get(ch)) {
        std::string code = huffmanCodes[ch];
        for (char bit : code) {
            bitstream.push_back(bit == '1');
        }
    }

    int byteCount = 0;
    unsigned char byte = 0;
    for (bool bit : bitstream) {
        byte = (byte << 1) | bit;
        byteCount++;
        if (byteCount == 8) {
            outFile.put(byte);
            byteCount = 0;
            byte = 0;
        }
    }

    // Write remaining bits if any
    if (byteCount > 0) {
        byte = byte << (8 - byteCount);
        outFile.put(byte);
    }

    inFile.close();
    outFile.close();
}

// �����Y�ɮ�
void decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    // Ū���s�X��
    std::unordered_map<std::string, char> reverseHuffmanCodes;
    std::string line;

    while (std::getline(inFile, line) && !line.empty()) {
        size_t pos = line.find("=");
        if (pos != std::string::npos) {
            char ch = line[0];
            std::string code = line.substr(pos + 1);
            reverseHuffmanCodes[code] = ch;
        }
    }

    // Ū�����Y���
    std::vector<bool> bitstream;
    char byte;
    while (inFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            bitstream.push_back((byte >> i) & 1);
        }
    }

    // �ѽX���٭��l�ɮ�
    std::string currentCode = "";
    for (bool bit : bitstream) {
        currentCode += bit ? "1" : "0";
        if (reverseHuffmanCodes.find(currentCode) != reverseHuffmanCodes.end()) {
            outFile.put(reverseHuffmanCodes[currentCode]);
            currentCode.clear();
        }
    }

    inFile.close();
    outFile.close();
}

// �������ε{���B�z
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // Create "Compress" and "Decompress" buttons
        CreateWindow("BUTTON", "Compress", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     150, 50, 200, 40, hwnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow("BUTTON", "Decompress", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     150, 120, 200, 40, hwnd, (HMENU)2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // Handle Compress button click
            OPENFILENAME ofn;
            char szFile[260];

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "Text files\0*.TXT\0All files\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE) {
                // Perform compression
                std::string inputFile = ofn.lpstrFile;
                std::string outputFile = inputFile + ".huff";
                compressFile(inputFile, outputFile);
                MessageBox(hwnd, "File compressed successfully!", "Info", MB_OK);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Handle Decompress button click
            OPENFILENAME ofn;
            char szFile[260];

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "Huffman files\0*.huff\0All files\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE) {
                // Perform decompression
                std::string inputFile = ofn.lpstrFile;
                std::string outputFile = inputFile + ".decompressed";
                decompressFile(inputFile, outputFile);
                MessageBox(hwnd, "File decompressed successfully!", "Info", MB_OK);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    // Define and register window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProcedure, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "HuffmanWindow", NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow(wc.lpszClassName, "Huffman Compression Tool", WS_OVERLAPPEDWINDOW, 100, 100, 600, 400, NULL, NULL, wc.hInstance, NULL);
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Start the message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

