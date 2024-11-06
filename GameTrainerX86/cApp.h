#pragma once
#include "wx/wx.h"
#include "cMain.h"

class cApp
	: public wxApp
{
public:
	cApp();
	~cApp();

	virtual bool OnInit();
	
private:
	std::unique_ptr<const wxString> m_frameTitle;
	std::unique_ptr<const wxSize> m_frameSize;

	cMain* m_mainFrame;
};