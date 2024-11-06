#include "cApp.h"

IMPLEMENT_APP(cApp);
DECLARE_APP(cApp);

cApp::cApp()
{
	m_mainFrame = nullptr;
}

cApp::~cApp()
{
	/*
		"delete cMain;" results in a runtime crash
		because wxFrame's delete themselves when they are closed
	*/
}

bool cApp::OnInit()
{
	m_frameTitle = std::make_unique<wxString>("GameTrainerX86"); // deletes itself after exiting OnInit()
	m_frameSize = std::make_unique<wxSize>(500, 480); // deletes itself after exiting OnInit()

	// create main top-level window
	m_mainFrame = new cMain(*m_frameTitle, wxDefaultPosition, *m_frameSize);
	m_mainFrame->Show();

	// Start the event loop
	return true;
}