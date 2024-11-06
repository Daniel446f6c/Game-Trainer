#include "cMain.h"

/*
	All UI-Elements, Fonts and Grids are defined in the constructor.
*/

cMain::cMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	InitUI();
	BindEvents();
	CreateCheckProcListThread();
	wxInitAllImageHandlers();
	PanelDS3 = nullptr;
	PanelCV = nullptr;
	m_ds3Name = L"DarkSoulsIII.exe";
	m_cvName = L"CodeVein-Win64-Shipping.exe";
}

cMain::~cMain()
{
	WaitCheckProcListThreadFinishExecution();
	UnbindEvents();

	if (PanelDS3)
	{
		delete PanelDS3;
	}
	if (PanelCV)
	{
		delete PanelCV;
	}
}

void cMain::InitUI()
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

	m_menuItemDS3 = new wxMenuItem(m_menuGames, 10101, wxString(wxT("Dark Souls 3")), wxEmptyString, wxITEM_NORMAL);
	m_menuGames->Append(m_menuItemDS3);

	m_menuItemCV = new wxMenuItem(m_menuGames, 10102, wxString(wxT("Code Vein")), wxEmptyString, wxITEM_NORMAL);
	m_menuGames->Append(m_menuItemCV);

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
}

void cMain::BindEvents()
{
	// Begin: Connect Events
	m_menuGameTrainer->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemExitPressed), this, m_menuItemExit->GetId());
	m_menuGames->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemDS3Pressed), this, m_menuItemDS3->GetId());
	m_menuGames->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemCVPressed), this, m_menuItemCV->GetId());
	m_menuHelp->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemInfoPressed), this, m_menuItemInfo->GetId());
	m_menuHelp->Bind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemAboutPressed), this, m_menuItemAbout->GetId());
	Bind(wxEVT_SIZE, wxSizeEventHandler(cMain::OnWindowResized), this);
	// End: Connect Events
}

void cMain::UnbindEvents()
{
	// Begin: Disconnect Events
	m_menuGameTrainer->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemExitPressed), this, m_menuItemExit->GetId());
	m_menuGames->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemDS3Pressed), this, m_menuItemDS3->GetId());
	m_menuGames->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemCVPressed), this, m_menuItemCV->GetId());
	m_menuHelp->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemInfoPressed), this, m_menuItemInfo->GetId());
	m_menuHelp->Unbind(wxEVT_MENU, wxCommandEventHandler(cMain::OnMenuItemAboutPressed), this, m_menuItemAbout->GetId());
	Unbind(wxEVT_SIZE, wxSizeEventHandler(cMain::OnWindowResized), this, GetId());
	// End: Disconnect Events
}

void cMain::CreateCheckProcListThread()
{
	// Begin: m_tCheckProcList setup
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_futureCheckProcList = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThreadCheckProcList = false;
	// start checking for running game processes in asynchronous thread
	m_tCheckProcList = std::make_unique<std::thread>(&cMain::CheckProcessList, this, std::move(barrier));
	m_tCheckProcList->detach();
	// End: m_tCheckProcList setup
}

void cMain::WaitCheckProcListThreadFinishExecution()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThreadCheckProcList = true;
	// wait for thread "m_tCheckProcList" to finish execution
	m_futureCheckProcList->wait();
}

void cMain::CheckProcessList(std::promise<void> barrier)
{
	while (!m_bTerminateThreadCheckProcList)
	{
		// Dark Souls 3
		if (!GetProcId(m_ds3Name)) // process not found
		{
			m_menuItemDS3->Enable(false);
			// Close the panel if open, reset his pointer to nullptr
			if (PanelDS3 != nullptr)
			{
				PanelDS3->Hide(); // Fixes the bug that after closing it it is still shown
				PanelDS3->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
				//PanelDS3->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
				// Refresh() doesn't make the closed Panel disapper therefor we hide it before closing it
				PanelDS3 = nullptr;
			}
		}
		else // process found
		{
			m_menuItemDS3->Enable(true);
		}

		// Code Vein
		if (!GetProcId(m_cvName)) // process not found
		{
			m_menuItemCV->Enable(false);
			// Close the panel if open, reset his pointer to nullptr
			if (PanelCV != nullptr)
			{
				PanelCV->Hide(); // Fixes the bug that after closing it it is still shown
				PanelCV->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
				//PanelCV->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
				//Refresh(); // doesn't make the closed Panel disapper therefor we hide it before closing it
				PanelCV = nullptr;
			}
		}
		else // process found
		{
			m_menuItemCV->Enable(true);
		}

		// Sleep 2.4s to save resources
		std::this_thread::sleep_for(std::chrono::milliseconds(2400));
	}
	// set the promise that the thread has ended execution
	barrier.set_value();
}

void cMain::OnMenuItemExitPressed(wxCommandEvent& ev)
{
	Close(true);
	ev.Skip();
}

void cMain::OnMenuItemDS3Pressed(wxCommandEvent &ev)
{
	// Close any other panels that might be open, reset their pointer to nullptr
	if (PanelCV != nullptr)
	{
		PanelCV->Hide();
		PanelCV->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
		//PanelCV->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
		PanelCV = nullptr;
	}
	
	// Create Dark Souls 3 Panel
	if (PanelDS3 == nullptr)
	{
		PanelDS3 = new DarkSouls3Panel(this, wxDefaultPosition, GetClientSize());
	}
	else
	{
		PanelDS3->Hide();
		PanelDS3->Destroy();
		PanelDS3 = new DarkSouls3Panel(this, wxDefaultPosition, GetClientSize());
	}
	
	ev.Skip();
}

void cMain::OnMenuItemCVPressed(wxCommandEvent& ev)
{
	// Close any other panels that might be open, reset their pointer to nullptr
	if (PanelDS3 != nullptr)
	{
		PanelDS3->Hide();
		PanelDS3->Destroy(); // necessary in this case, normally prefer Close() over Destroy()
		//PanelDS3->Close(true); // calling Close() on a wxPanel doesn't destroy the instance, hence I'm using Destroy()
		PanelDS3 = nullptr;
	}
	
	// Create Code Vein Panel
	if (PanelCV == nullptr)
	{
		PanelCV = new CodeVeinPanel(this, wxDefaultPosition, GetClientSize());
	}
	else
	{
		PanelCV->Hide();
		PanelCV->Destroy();
		PanelCV = new CodeVeinPanel(this, wxDefaultPosition, GetClientSize());
	}
	
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
	if (PanelDS3 != nullptr)
	{
		PanelDS3->SetSize(GetClientSize());
	}
	if (PanelCV != nullptr)
	{
		PanelCV->SetSize(GetClientSize());
	}
	ev.Skip();
}