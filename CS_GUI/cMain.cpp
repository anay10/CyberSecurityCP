#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_RADIOBOX(10001, cMain::OnRadioChange)
EVT_BUTTON(10002, cMain::OnStartClicked)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CS Course Project", wxPoint(30, 30), wxSize(600, 200))
{
	//top level panel
	RadioPanel = new wxPanel(this, wxID_ANY);

	//Middle Panel
	MidPanel = new wxPanel(this, wxID_ANY);
	
	//Radio box
	wxArrayString choices;
	choices.Add("Caesar Cipher");
	//choices.Add("RSA");
	choices.Add("XOR encryption");
	RadioBox = new wxRadioBox(RadioPanel, 10001,
		"Select one of the options", wxDefaultPosition,
		wxDefaultSize, choices, 2, wxRA_VERTICAL);

	/*Method of retireving data from Radio Box
	(RadioBox->GetString(RadioBox->GetSelection()))*/

	//wxTextCtrl to show which option is selected
	TextCtrl = new wxTextCtrl(RadioPanel, wxID_ANY,
		RadioBox->GetString(RadioBox->GetSelection()),
		wxDefaultPosition, wxSize(140, wxDefaultCoord));

	//wxTextCtrl for file path
	t_FilePath = new wxTextCtrl(MidPanel, wxID_ANY,
		"Enter file path",
		wxDefaultPosition, wxSize(140, wxDefaultCoord));

	//Start Button
	b_Start = new wxButton(MidPanel, 10002, "Start", wxDefaultPosition, wxSize(50, wxDefaultCoord));

	//Setup Sizer for the panel
	RP_Sizer = new wxBoxSizer(wxVERTICAL);
	RP_Sizer->Add(RadioBox, 1, wxEXPAND | wxALL, 15);
	RP_Sizer->Add(TextCtrl, 0, wxCENTER);
	RP_Sizer->AddSpacer(15);
	RadioPanel->SetSizer(RP_Sizer);

	//Setup Sizer for Middle Panel
	MP_Sizer = new wxBoxSizer(wxHORIZONTAL);
	MP_Sizer->Add(t_FilePath, 1, wxALL, 10);
	MP_Sizer->Add(b_Start, 0, wxALL, 10);
	//MP_Sizer->AddSpacer(15);
	MidPanel->SetSizer(MP_Sizer);

	//Set sizer fpr Frame
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->SetMinSize(600, 200);
	topSizer->Add(RadioPanel, 0, wxEXPAND);
	topSizer->Add(MidPanel, 1, wxEXPAND | wxALL, 15);
	SetSizerAndFit(topSizer);

	this->SetMaxSize(wxSize(700, 500));

}

cMain::~cMain()
{
}

void cMain::OnRadioChange(wxCommandEvent& evt)
{
	wxString text = RadioBox->GetString(evt.GetSelection());
	TextCtrl->SetValue(text);
	evt.Skip();
}

void cMain::OnStartClicked(wxCommandEvent& evt)
{
	struct stat buffer;
	std::string path = (t_FilePath->GetLineText(0)).ToStdString();

	/*Check if the path exists*/
	/*std::ifstream f_Check;
	f_Check.open(path.c_str(), std::ios::binary);*/
	bool doesExist = (stat(path.c_str(), &buffer) == 0); //f_Check.fail();
	//f_Check.close();

	if (doesExist)
	{
		b_Start->Disable();
		if (RadioBox->GetSelection() == 0)
		{
			Caesar* c_cipher = new Caesar(this, b_Start, path);
			c_cipher->Show();
		}
		else if (RadioBox->GetSelection() == 1)
		{
			E_XOR* x_cipher = new E_XOR(this, b_Start, path);
			x_cipher->Show();
		}
	}
	else
	{
		t_FilePath->Clear();
		t_FilePath->AppendText("Enter Valid Path");
	}
	evt.Skip();
}
