#include "cMain.h"

/*
	All UI-Elements, Fonts and Grids are defined in the constructor.
*/

cMain::cMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// Begin: Icon
	// old way, loaded icon from file
	/*wxIcon icon;
	icon.LoadFile(wxT("icon.ico"), wxBITMAP_TYPE_ICO);
	if (icon.IsOk())
		SetIcon(icon);
	else
		wxMessageBox(wxT("Failed to load the Icon."), wxString(GetTitle() + wxT(" Error")), wxICON_ERROR);*/

	// new way, load icon direct from resources now it must not be shipped alongside the executable
	SetIcon(wxICON(IDI_ICON1));
	// End: Icon
	
	// Begin: Window Settings
	// center the window on screen, both horizontally and veritcally
	Centre();
	SetMinClientSize(GetClientSize());
	// End: Window Settings

	// Begin: menu bar, menus, submenus, menuitems
	m_menuBar = new wxMenuBar(0);

	// Begin: menu Delta Win
	m_menuGameTrainer = new wxMenu();

	m_menuItemExit = new wxMenuItem(m_menuGameTrainer, 10001, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	m_menuGameTrainer->Append(m_menuItemExit);

	m_menuBar->Append(m_menuGameTrainer, wxT("GameTrainer"));
	// End: menu Delta Win

	// Begin: menu Games
	m_menuGames = new wxMenu();
	
	/*m_menuItemDS3 = new wxMenuItem(m_menuGames, 10101, wxString(wxT("Dark Souls 3")), wxEmptyString, wxITEM_NORMAL);
	m_menuGames->Append(m_menuItemDS3);*/
	
	m_menuItemNFSMW = new wxMenuItem(m_menuGames, 10102, wxString(wxT("NFS Most Wanted")), wxEmptyString, wxITEM_NORMAL);
	m_menuGames->Append(m_menuItemNFSMW);
	
	m_menuItemSSTSE = new wxMenuItem(m_menuGames, 10103, wxString(wxT("Serious Sam: The 2nd Encounter")), wxEmptyString, wxITEM_NORMAL);
	m_menuGames->Append(m_menuItemSSTSE);

	m_menuBar->Append(m_menuGames, wxT("Games"));
	// End: menu Games

	// Begin: menu Help
	m_menuHelp = new wxMenu();

	m_menuItemInfo = new wxMenuItem(m_menuHelp, 10201, wxString(wxT("Info")), wxEmptyString, wxITEM_NORMAL);
	m_menuHelp->Append(m_menuItemInfo);

	m_menuItemAbout = new wxMenuItem(m_menuHelp, 10202, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menuHelp->Append(m_menuItemAbout);

	m_menuBar->Append(m_menuHelp, wxT("Help"));
	// End: menu Help

	this->SetMenuBar(m_menuBar);
	// End: menu bar, menus, submenus, menuitems

	// Begin: Panels
	/*PanelDS3 = nullptr;*/
	PanelSSTSE = nullptr;
	PanelNFSMW = nullptr;
	// End: Panels

	// Begin: Connect Events
	m_menuGameTrainer->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemExitPressed), this, m_menuItemExit->GetId());
	/*m_menuGames->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemDS3Pressed), this, m_menuItemDS3->GetId());*/
	m_menuGames->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemNFSMWPressed), this, m_menuItemNFSMW->GetId());
	m_menuGames->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemSSTSEPressed), this, m_menuItemSSTSE->GetId());
	m_menuHelp->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemInfoPressed), this, m_menuItemInfo->GetId());
	m_menuHelp->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemAboutPressed), this, m_menuItemAbout->GetId());
	Bind(wxEVT_SIZE, wxSizeEventHandler(cMain::OnWindowResized), this);
	// End: Connect Events

	// Begin: m_tCheckProcList setup
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_barrierFuture = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThread = false;
	// start checking for running game processes in asynchronous thread
	m_tCheckProcList = std::make_unique<std::thread>(&cMain::CheckProcessList, this, std::move(barrier));
	m_tCheckProcList->detach();
	// End: m_tCheckProcList setup

	/*m_ds3Name = L"DarkSoulsIII.exe";*/
	m_sstseName = L"SeriousSam.exe";
	m_nfsmwName = L"speed.exe";
}

cMain::~cMain()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThread = true;

	// wait for thread "m_tCheckProcList" to finish execution
	m_barrierFuture->wait();

	// Begin: Disconnect Events
	m_menuGameTrainer->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemExitPressed), this, m_menuItemExit->GetId());
	/*m_menuGames->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemDS3Pressed), this, m_menuItemDS3->GetId());*/
	m_menuGames->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemNFSMWPressed), this, m_menuItemNFSMW->GetId());
	m_menuGames->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemSSTSEPressed), this, m_menuItemSSTSE->GetId());
	m_menuHelp->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemInfoPressed), this, m_menuItemInfo->GetId());
	m_menuHelp->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemAboutPressed), this, m_menuItemAbout->GetId());
	Unbind(wxEVT_SIZE, wxSizeEventHandler(cMain::OnWindowResized), this, GetId());
	// End: Disconnect Events
}

void cMain::CheckProcessList(std::promise<void> barrier)
{
	while (!m_bTerminateThread)
	{
		//// Dark Souls 3
		//if (GetProcId(m_ds3Name) == 0) // process not found
		//{
		//	m_menuItemDS3->Enable(false);
		//	// Close the panel if open, reset his pointer to nullptr
		//	if (PanelDS3 != nullptr)
		//	{
		//		PanelDS3->Hide(); // Fixes the bug that after closing it it is still shown
		//		PanelDS3->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
		//		//PanelDS3->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
		//		// Refresh() doesn't make the closed Panel disapper therefor we hide it before closing it
		//		PanelDS3 = nullptr;
		//	}
		//}
		//else // process found
		//	m_menuItemDS3->Enable(true);

		// Need for Speed: Most Wanted
		if (GetProcId(m_nfsmwName) == 0) // process not found
		{
			m_menuItemNFSMW->Enable(false);
			// Close the panel if open, reset his pointer to nullptr
			if (PanelNFSMW != nullptr)
			{
				PanelNFSMW->Hide(); // Fixes the bug that after closing it it is still shown
				PanelNFSMW->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
				//PanelNFSMW->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
				//Refresh(); // doesn't make the closed Panel disapper therefor we hide it before closing it
				PanelNFSMW = nullptr;
			}
		}
		else // process found
		{
			m_menuItemNFSMW->Enable(true);
		}

		// Serious Sam: The Second Encounter
		if (GetProcId(m_sstseName) == 0) // process not found
		{
			m_menuItemSSTSE->Enable(false);
			// Close the panel if open, reset his pointer to nullptr
			if (PanelSSTSE != nullptr)
			{
				PanelSSTSE->Hide(); // Fixes the bug that after closing it it is still shown
				PanelSSTSE->Destroy();
				//PanelSSTSE->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
				// Refresh() doesn't make the closed Panel disapper therefor we hide it before closing it
				PanelSSTSE = nullptr;
			}
		}
		else // process found
		{
			m_menuItemSSTSE->Enable(true);
		}
		

		// Sleep 1.2s to save resources
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
	}
	// set the promise that the thread has ended execution
	barrier.set_value();
}

void cMain::OnMenuItemExitPressed(wxCommandEvent& ev)
{
	Close(true);
	ev.Skip();
}

//void cMain::OnMenuItemDS3Pressed(wxCommandEvent &ev)
//{
//	// Close any other panels that might be open, reset their pointer to nullptr
//	if (PanelNFSMW != nullptr)
//	{
//		PanelNFSMW->Hide();
//		PanelNFSMW->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
//		//PanelNFSMW->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
//		PanelNFSMW = nullptr;
//	}
//	if (PanelSSTSE != nullptr)
//	{
//		PanelSSTSE->Hide();
//		PanelSSTSE->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
//		//PanelSSTSE->Close(); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
//		PanelSSTSE = nullptr;
//	}
//	// Create the desired panel
//	if (PanelDS3 == nullptr)
//		PanelDS3 = new DarkSouls3Panel(this, wxDefaultPosition, GetClientSize());
//	
//	ev.Skip();
//}

void cMain::OnMenuItemNFSMWPressed(wxCommandEvent& ev)
{
	// Close any other panels that might be open, reset their pointer to nullptr
	//if (PanelDS3 != nullptr)
	//{
	//	PanelDS3->Hide();
	//	PanelDS3->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
	//	//PanelDS3->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
	//	PanelDS3 = nullptr;
	//}
	if (PanelSSTSE != nullptr)
	{
		PanelSSTSE->Hide();
		PanelSSTSE->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
		//PanelSSTSE->Close(); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
		PanelSSTSE = nullptr;
	}
	// Create the desired panel
	if (PanelNFSMW == nullptr)
		PanelNFSMW = new NFSMostWantedPanel(this, wxDefaultPosition, GetClientSize());

	ev.Skip();
}

void cMain::OnMenuItemSSTSEPressed(wxCommandEvent& ev)
{
	// Close any other panels that might be open, reset their pointer to nullptr
	//if (PanelDS3 != nullptr)
	//{
	//	PanelDS3->Hide();
	//	PanelDS3->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
	//	//PanelDS3->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
	//	PanelDS3 = nullptr;
	//}
	if (PanelNFSMW != nullptr)
	{
		PanelNFSMW->Hide();
		PanelNFSMW->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
		//PanelNFSMW->Close(); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
		PanelNFSMW = nullptr;
	}
	// Create the desired panel
	if (PanelSSTSE == nullptr)
		PanelSSTSE = new SSTheSecondEncounterPanel(this, wxDefaultPosition, GetClientSize());
	
	ev.Skip();
}

void cMain::OnMenuItemInfoPressed(wxCommandEvent& ev)
{
	wxMessageBox("You need to have the game running to select it.", wxString(GetTitle() + " Information"), wxICON_INFORMATION);
	ev.Skip();
}

void cMain::OnMenuItemAboutPressed(wxCommandEvent& ev)
{
	wxMessageBox("TODO", wxString(GetTitle() + " About"), wxICON_INFORMATION);
	ev.Skip();
}

void cMain::OnWindowResized(wxSizeEvent& ev)
{
	/*if (PanelDS3 != nullptr)
		PanelDS3->SetSize(GetClientSize());*/
	if (PanelNFSMW != nullptr)
		PanelNFSMW->SetSize(GetClientSize());
	if (PanelSSTSE != nullptr)
		PanelSSTSE->SetSize(GetClientSize());
	ev.Skip();
}