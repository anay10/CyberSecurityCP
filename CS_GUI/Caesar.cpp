#include "Caesar.h"

wxBEGIN_EVENT_TABLE(Caesar, wxFrame)
EVT_BUTTON(20002, Caesar::OnGoClicked)
wxEND_EVENT_TABLE()

Caesar::Caesar(wxWindow* p_Parent, wxButton* b_BuT, std::string f_p) : wxFrame(p_Parent, wxID_ANY,
	"CS CP - Caesar Cipher", wxPoint(30, 30), wxSize(600, 800))
{
	b_StartBut = b_BuT;
	f_Path = f_p;

	//Radio Panel
	c_RadioPanel = new wxPanel(this, wxID_ANY);

	//Key Panel
	c_KeyPanel = new wxPanel(this, wxID_ANY);

	//Radio box
	wxArrayString c_choices;
	c_choices.Add("Encrypt");
	c_choices.Add("Decrypt");
	c_RadioBox = new wxRadioBox(c_RadioPanel, 20001,
		"Select one of the options", wxDefaultPosition,
		wxDefaultSize, c_choices, 2, wxRA_HORIZONTAL);

	//TextCtrl for taking in Key
	c_Key = new wxTextCtrl(c_KeyPanel, wxID_ANY,
		"Enter Key",
		wxDefaultPosition, wxSize(140, wxDefaultCoord));

	//Button for starting encryption
	c_Go = new wxButton(c_KeyPanel, 20002, "Go", wxDefaultPosition, wxSize(50, wxDefaultCoord));

	//Set sizer for Radiobox
	c_RadioSizer = new wxBoxSizer(wxHORIZONTAL);
	c_RadioSizer->Add(c_RadioBox, 1, wxEXPAND | wxALL, 15);
	c_RadioPanel->SetSizer(c_RadioSizer);
	
	//Set sizer for key TextCtrl
	KP_Sizer = new wxBoxSizer(wxHORIZONTAL);
	KP_Sizer->Add(c_Key, 1, wxALL, 10);
	KP_Sizer->Add(c_Go, 0, wxALL, 10);
	c_KeyPanel->SetSizer(KP_Sizer);

	//Set top sizer for entire frame
	c_topSizer = new wxBoxSizer(wxVERTICAL);
	c_topSizer->SetMinSize(600, 200);
	c_topSizer->Add(c_RadioPanel, 1, wxEXPAND);
	c_topSizer->Add(c_KeyPanel, 0, wxEXPAND);
	SetSizerAndFit(c_topSizer);
}

Caesar::~Caesar()
{
	b_StartBut->Enable(true);
}

void Caesar::OnGoClicked(wxCommandEvent& evt)
{
	int Choice = c_RadioBox->GetSelection();

	if (Choice == 0)//Encryption
	{
		std::string s_Key = (c_Key->GetLineText(0)).ToStdString();
		bool isnum = true;
		
		/*Checking if key has valid datatype (int)*/
		for (char const& c : s_Key)
		{
			if (std::isdigit(c) == 0)
			{
				isnum = false;
				break;
			}
		}

		if (isnum)
		{
			int k = atoi(s_Key.c_str());
			int Cipher_Status = CeaserCipher(k);
		}
		else
		{
			c_Key->SetLabel("Enter Valid Key");
		}
	}
	else//Decryption
	{
		std::string s_Key = (c_Key->GetLineText(0)).ToStdString();
		bool isnum = true;

		/*Checking if key has valid datatype (int)*/
		for (char const& c : s_Key)
		{
			if (std::isdigit(c) == 0)
			{
				isnum = false;
				break;
			}
		}

		if (isnum)
		{
			int k = atoi(s_Key.c_str());
			int Cipher_Status = CeaserDCipher(k);
		}
		else
		{
			c_Key->SetLabel("Enter Valid Key");
		}
	}
}

int Caesar::CeaserDCipher(int key)
{
	/*Setting File Streams*/
	std::ifstream fin;
	std::ofstream fout;
	fin.open(f_Path.c_str(), std::ios::binary);

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

	fout.open(o_Path.c_str(), std::ios::binary);

	while (!fin.eof())
	{
		fin >> std::noskipws >> c;
		int temp = (c - key);
		fout << (char)temp;
	}
	fin.close();
	fout.close();


	wxMessageBox("Decrytion successful");
	this->Close();
	return 1;
}

int Caesar::CeaserCipher(int key)
{
	/*Setting File Streams*/
	std::ifstream fin;
	std::ofstream fout;
	fin.open(f_Path.c_str(), std::ios::binary);

	if (fin.fail())
	{
		c_Key->SetLabel("Invalid Path! File Does not Exist!");
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

	fout.open(o_Path.c_str(), std::ios::binary);

	while (!fin.eof())
	{
		fin >> std::noskipws >> c;
		int temp = (c + key);
		fout << (char)temp;
	}
	fin.close();
	fout.close();

	wxMessageBox("Encrytion successful");
	this->Close();
	return 1;
}
