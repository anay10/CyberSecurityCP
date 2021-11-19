#pragma once

#include"wx\wx.h"
#include<fstream>

class Caesar : public wxFrame
{
public:
	Caesar(wxWindow* w, wxButton* b, std::string s);
	~Caesar();

private:
	wxButton* b_StartBut = nullptr;
	std::string f_Path = "";

public:
	wxPanel* c_RadioPanel = nullptr;
	wxBoxSizer* c_RadioSizer = nullptr;
	wxRadioBox* c_RadioBox = nullptr;
	wxBoxSizer* c_topSizer = nullptr;
	wxTextCtrl* c_Key = nullptr;
	wxPanel* c_KeyPanel = nullptr;
	wxBoxSizer* KP_Sizer = nullptr;
	wxButton* c_Go = nullptr;
	wxDECLARE_EVENT_TABLE();

private:
	void OnGoClicked(wxCommandEvent& evt);
	int CeaserCipher(int key);
	int CeaserDCipher(int key);
};

