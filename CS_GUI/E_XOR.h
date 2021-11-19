#pragma once

#include"wx/wx.h"
#include<fstream>

class E_XOR : public wxFrame
{
public:
	E_XOR(wxWindow*, wxButton*, std::string);
	~E_XOR();

private:
	wxPanel* x_RadioPanel = nullptr;
	wxBoxSizer* x_RadioSizer = nullptr;
	wxRadioBox* x_RadioBox = nullptr;
	wxBoxSizer* x_topSizer = nullptr;
	std::string f_Path = "";
	wxButton* b_Start = nullptr;
	wxTextCtrl* x_Key = nullptr;
	wxButton* x_Go = nullptr;
	wxPanel* x_KeyPanel = nullptr;
	wxBoxSizer* x_KPSizer = nullptr;
	wxDECLARE_EVENT_TABLE();

public:
	void OnXGOClicked(wxCommandEvent& evt);
	int XOR_Cipher(std::string key);
	int XOR_DCipher(std::string key);
};

