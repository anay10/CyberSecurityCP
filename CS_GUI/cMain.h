#pragma once

#include "wx\wx.h"
#include <sys/stat.h>
#include"Caesar.h"
#include"E_XOR.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
private:
	wxRadioBox* RadioBox = nullptr;
	wxTextCtrl* TextCtrl = nullptr;
	wxPanel* RadioPanel = nullptr;
	wxBoxSizer* RP_Sizer = nullptr;
	wxPanel* MidPanel = nullptr;
	wxBoxSizer* MP_Sizer = nullptr;
	wxTextCtrl* t_FilePath = nullptr;
	wxButton* b_Start = nullptr;

	wxDECLARE_EVENT_TABLE();
public:
	void OnRadioChange(wxCommandEvent& evt);
	void OnStartClicked(wxCommandEvent& evt);
};

