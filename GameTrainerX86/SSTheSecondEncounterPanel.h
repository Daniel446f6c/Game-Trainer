#pragma once
#include "wx/wx.h"
#include "Proc.h"

class SSTheSecondEncounterPanel
	: public wxPanel
{
public:
	SSTheSecondEncounterPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size);
	~SSTheSecondEncounterPanel();

private:

	// initialize hack functionality
	bool InitHack();
};
