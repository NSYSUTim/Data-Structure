#include <gtkmm.h>
#include <iostream>
#include <string>
#include "huffmanLib.hpp"
using namespace std;

// Usage:
// cmd line: g++ -std=c++17 -o hw8-B123245021 hw8-B123245021.cpp huffmanLib.cpp $(pkg-config --cflags gtkmm-3.0) $(pkg-config --libs gtkmm-3.0)
// ����G ./hw8-B123245021
// �����|���X���Y/�����Y�\�����

class HuffmanWindow : public Gtk::Window
{
public:
	HuffmanWindow()
	{
		set_title("Huffman Compression/Decompression"); // �]�w�������D
		set_default_size(300, 200); // �]�w�����w�]�j�p

		// �]�w���s����
		m_button_compress.set_label("Compress"); // ���Y���s
		m_button_decompress.set_label("Decompress"); // �����Y���s
		m_button_quit.set_label("Quit"); // ���}���s

		// �N���s�K�[�ܫ����G���e����
		m_box.pack_start(m_button_compress); // �K�[���Y���s
		m_box.pack_start(m_button_decompress); // �K�[�����Y���s
		m_box.pack_start(m_button_quit); // �K�[���}���s

		// �N�G���e���K�[�ܵ���
		add(m_box);

		// �s�����s�I���H���P�������禡
		m_button_compress.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_compress_clicked)); // �I�����Y���s��Ĳ�o
		m_button_decompress.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_decompress_clicked)); // �I�������Y���s��Ĳ�o
		m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &HuffmanWindow::on_quit_clicked)); // �I�����}���s��Ĳ�o

		// ��ܩҦ��l����
		show_all_children();
	}

	virtual ~HuffmanWindow() {} // �R�c�禡�A����귽

protected:
	void on_compress_clicked()
	{
		string fileName = get_file_name(); // �I�s�ɮ׿�ܾ��A���o�ɮצW��
		if (!fileName.empty()) // �T�{�ɮצW�٫D��
		{
			bool result = compress(fileName); // �������Y
			cout << (result ? "Compression succeeded!" : "Compression failed!") << endl; // ��X���Y���G
		}
	}

	void on_decompress_clicked()
	{
		string fileName = get_file_name(); // �I�s�ɮ׿�ܾ��A���o�ɮצW��
		if (!fileName.empty()) // �T�{�ɮצW�٫D��
		{
			bool result = decompress(fileName); // ��������Y
			cout << (result ? "Decompression succeeded!" : "Decompression failed!") << endl; // ��X�����Y���G
		}
	}

	void on_quit_clicked()
	{
		hide(); // ���õ����õ������ε{��
	}

private:
	string get_file_name()
	{
		// �إ��ɮ׿�ܹ�ܮءA���\�Τ����ɮ�
		Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL); // �K�[�������s
		dialog.add_button("_Open", Gtk::RESPONSE_OK); // �K�[�}�ҫ��s

		int result = dialog.run(); // �����ܮءA���o�Τ�^��
		if (result == Gtk::RESPONSE_OK) // �p�G�Τ���U�}�ҫ��s
		{
			return dialog.get_filename(); // �^�ǿ�ܪ��ɮצW��
		}

		return ""; // �p�G�Τ������ܡA�^�ǪŦr��
	}

	Gtk::Box m_box{Gtk::ORIENTATION_VERTICAL, 10}; // �����ƦC���G���e���A�l���󤧶��� 10px ���Z
	Gtk::Button m_button_compress, m_button_decompress, m_button_quit; // �T�ӫ��s�G���Y�B�����Y�B���}
};

int main(int argc, char *argv[])
{
	// ��l�� GTK
	Gtk::Main kit(argc, argv);

	// �إߥD�����ð������ε{��
	HuffmanWindow window;
	Gtk::Main::run(window);

	return 0; // �����{��
}

