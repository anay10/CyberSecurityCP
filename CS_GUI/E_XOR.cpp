#include "E_XOR.h"

wxBEGIN_EVENT_TABLE(E_XOR, wxFrame)
EVT_BUTTON(30001, E_XOR::OnXGOClicked)
wxEND_EVENT_TABLE()


E_XOR::E_XOR(wxWindow* p_Parent, wxButton* bButton,std::string p_Path) : wxFrame(p_Parent, wxID_ANY,
	"CS CP - XOR Encryption",wxPoint(30, 30), wxSize(600, 800))
{
	b_Start = bButton;
	f_Path = p_Path;

	//Radio panel
	x_RadioPanel = new wxPanel(this, wxID_ANY);

	//Key panel
	x_KeyPanel = new wxPanel(this, wxID_ANY);

	//Radio box
	wxArrayString x_Choices;
	x_Choices.Add("Encrytion");
	x_Choices.Add("Decrytion");
	x_RadioBox = new wxRadioBox(x_RadioPanel, wxID_ANY, "Select anyone of these options", wxDefaultPosition,
		wxDefaultSize,x_Choices, 2, wxHORIZONTAL);

	//TextCtrl for key
	x_Key = new wxTextCtrl(x_KeyPanel, wxID_ANY, "Enter key", wxDefaultPosition, wxSize(140, wxDefaultCoord));

	//Button for Starting Encryption-Decryption
	x_Go = new wxButton(x_KeyPanel, 30001, "Go", wxDefaultPosition, wxSize(50, wxDefaultCoord));

	//Radio Box Sizer
	x_RadioSizer = new wxBoxSizer(wxHORIZONTAL);
	x_RadioSizer->Add(x_RadioBox, 1, wxEXPAND | wxALL, 15);
	x_RadioPanel->SetSizer(x_RadioSizer);

	//Key TextCtrl sizer
	x_KPSizer = new wxBoxSizer(wxHORIZONTAL);
	x_KPSizer->Add(x_Key, 1, wxALL, 10);
	x_KPSizer->Add(x_Go, 0, wxALL, 10);
	x_KeyPanel->SetSizer(x_KPSizer);

	//Top sizer for entire frame
	x_topSizer = new wxBoxSizer(wxVERTICAL);
	x_topSizer->SetMinSize(600, 200);
	x_topSizer->Add(x_RadioPanel, 1, wxEXPAND);
	x_topSizer->Add(x_KeyPanel, 0, wxEXPAND);
	SetSizerAndFit(x_topSizer);
}

E_XOR::~E_XOR()
{
	b_Start->Enable(true);
}

void E_XOR::OnXGOClicked(wxCommandEvent& evt)
{
	int Choice = x_RadioBox->GetSelection();

	if (Choice == 0)//Encryption
	{
		int Cipher_Status = XOR_Cipher((x_Key->GetLineText(0)).ToStdString());

	}
	else//Decryption
	{
		int Cipher_Status = XOR_DCipher((x_Key->GetLineText(0)).ToStdString());
	}
}

int E_XOR::XOR_Cipher(std::string key)
{
	std::ifstream fin;
	std::ofstream fout;

	fin.open(f_Path, std::ios::binary);
	if (fin.fail())
	{
		wxMessageBox("File does not Exist");
		this->Close();
		return 0;
	}
	
	int p_lenth = f_Path.length();
	char p_Extension[5];
	p_Extension[3] = f_Path[p_lenth - 1];
	p_Extension[2] = f_Path[p_lenth - 2];
	p_Extension[1] = f_Path[p_lenth - 3];
	p_Extension[0] = '.';
	p_Extension[4] = '\0';
	std::string o_Path = f_Path + "Output" + p_Extension;
	char c;

	fout.open(o_Path, std::ios::binary);
	int i = 0;
	char temp;

	while (!fin.eof())
	{
		fin >> std::noskipws >> c;
		temp = c ^ key[i % key.length()];
		fout << temp;
	}

	//fout << (char)_eof;

	fin.close();
	fout.close();


	wxMessageBox("Encrytion successful");
	this->Close();
	return 1;
}

int E_XOR::XOR_DCipher(std::string key)
{
	std::ifstream fin;
	std::ofstream fout;

	fin.open(f_Path, std::ios::binary);
	if (fin.fail())
	{
		wxMessageBox("File does not Exist");
		this->Close();
		return 0;
	}

	int p_lenth = f_Path.length();
	char p_Extension[5];
	p_Extension[3] = f_Path[p_lenth - 1];
	p_Extension[2] = f_Path[p_lenth - 2];
	p_Extension[1] = f_Path[p_lenth - 3];
	p_Extension[0] = '.';
	p_Extension[4] = '\0';
	std::string o_Path = f_Path + "Decrypted" + p_Extension;
	char c;

	fout.open(o_Path, std::ios::binary);
	int i = 0;
	char temp;

	while (!fin.eof())
	{
		fin >> std::noskipws >> c;
		temp = c ^ key[i % key.length()];
		fout << temp;
		i++;
	}

	//fout << (char)_eof;

	fin.close();
	fout.close();


	wxMessageBox("Encrytion successful");
	this->Close();
	return 1;
}
