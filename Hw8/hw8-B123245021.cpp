#include <gtkmm.h>
#include <iostream>
#include <string>
#include "huffmanLib.hpp"
using namespace std;

// Usage:
// cmd line: g++ -std=c++17 -o hw8-B123245021 hw8-B123245021.cpp huffmanLib.cpp $(pkg-config --cflags gtkmm-3.0) $(pkg-config --libs gtkmm-3.0)
// 執行： ./hw8-B123245021
// 執行後會跳出壓縮/解壓縮功能視窗

class HuffmanWindow : public Gtk::Window
{
public:
	HuffmanWindow()
	{
		set_title("Huffman Compression/Decompression"); // 設定視窗標題
		set_default_size(300, 200); // 設定視窗預設大小

		// 設定按鈕標籤
		m_button_compress.set_label("Compress"); // 壓縮按鈕
		m_button_decompress.set_label("Decompress"); // 解壓縮按鈕
		m_button_quit.set_label("Quit"); // 離開按鈕

		// 將按鈕添加至垂直佈局容器中
		m_box.pack_start(m_button_compress); // 添加壓縮按鈕
		m_box.pack_start(m_button_decompress); // 添加解壓縮按鈕
		m_box.pack_start(m_button_quit); // 添加離開按鈕

		// 將佈局容器添加至視窗
		add(m_box);

		// 連接按鈕點擊信號與對應的函式
		m_button_compress.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_compress_clicked)); // 點擊壓縮按鈕時觸發
		m_button_decompress.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_decompress_clicked)); // 點擊解壓縮按鈕時觸發
		m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_quit_clicked)); // 點擊離開按鈕時觸發

		// 顯示所有子元件
		show_all_children();
	}

	virtual ~HuffmanWindow() {} // 析構函式，釋放資源

protected:
	void on_compress_clicked()
	{
		string fileName = get_file_name(); // 呼叫檔案選擇器，取得檔案名稱
		if (!fileName.empty()) // 確認檔案名稱非空
		{
			bool result = compress(fileName); // 執行壓縮
			cout << (result ? "Compression succeeded!" : "Compression failed!") << endl; // 輸出壓縮結果
		}
	}

	void on_decompress_clicked()
	{
		string fileName = get_file_name(); // 呼叫檔案選擇器，取得檔案名稱
		if (!fileName.empty()) // 確認檔案名稱非空
		{
			bool result = decompress(fileName); // 執行解壓縮
			cout << (result ? "Decompression succeeded!" : "Decompression failed!") << endl; // 輸出解壓縮結果
		}
	}

	void on_quit_clicked()
	{
		hide(); // 隱藏視窗並結束應用程式
	}

private:
	string get_file_name()
	{
		// 建立檔案選擇對話框，允許用戶選擇檔案
		Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL); // 添加取消按鈕
		dialog.add_button("_Open", Gtk::RESPONSE_OK); // 添加開啟按鈕

		int result = dialog.run(); // 執行對話框，取得用戶回應
		if (result == Gtk::RESPONSE_OK) // 如果用戶按下開啟按鈕
		{
			return dialog.get_filename(); // 回傳選擇的檔案名稱
		}

		return ""; // 如果用戶取消選擇，回傳空字串
	}

	Gtk::Box m_box{Gtk::ORIENTATION_VERTICAL, 10}; // 垂直排列的佈局容器，子元件之間有 10px 間距
	Gtk::Button m_button_compress, m_button_decompress, m_button_quit; // 三個按鈕：壓縮、解壓縮、離開
};

int main(int argc, char *argv[])
{
	// 初始化 GTK
	Gtk::Main kit(argc, argv);

	// 建立主視窗並執行應用程式
	HuffmanWindow window;
	Gtk::Main::run(window);

	return 0; // 結束程式
}

