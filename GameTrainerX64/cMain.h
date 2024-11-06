#pragma once
#include "wx/wx.h"
#include "Proc.h"
#include "DarkSouls3Panel.h"
#include "CodeVeinPanel.h"
#include <thread>
#include <future>


class cMain
	: public wxFrame
{
public:
	cMain(const wxString& title, const wxPoint& pos, const wxSize& size);
	~cMain();

	// panel for Dark Souls 3 Hack Controls
	DarkSouls3Panel* PanelDS3;
	// panel for Code Vein Hack Controls
	CodeVeinPanel* PanelCV;

private:
	
	// Dark Souls 3 Processname
	const wchar_t* m_ds3Name;
	// Code Vein Processname
	const wchar_t* m_cvName;

	// controls
	wxMenuBar* m_menuBar;
	wxMenu* m_menuGameTrainer;
	wxMenuItem* m_menuItemExit;
	wxMenu* m_menuGames;
	wxMenuItem* m_menuItemDS3;
	wxMenuItem* m_menuItemCV;
	wxMenu* m_menuHelp;
	wxMenuItem* m_menuItemInfo;
	wxMenuItem* m_menuItemAbout;
	
	void InitUI();
	void BindEvents();
	void UnbindEvents();
	void CreateCheckProcListThread();
	void WaitCheckProcListThreadFinishExecution();

	// supposed to run in a detached thread
	// until the program terminates (~cMain)
	void CheckProcessList(std::promise<void> barrier);
	// Checks whether or not the game processes are running
	// this thread runs asynchronous until ~cApp
	std::unique_ptr<std::thread> m_tCheckProcList;
	// used in thread "m_tCheckProcList"
	// if set to true the thread terminates asap
	bool m_bTerminateThreadCheckProcList;
	// used for thread "m_tCheckProcList"
	// in ~cApp this future waits for the promise that the thread has finished
	std::unique_ptr<std::future<void>> m_futureCheckProcList;

	// event handlers
	void OnMenuItemExitPressed(wxCommandEvent& ev);
	void OnMenuItemDS3Pressed(wxCommandEvent& ev);
	void OnMenuItemCVPressed(wxCommandEvent& ev);
	void OnMenuItemInfoPressed(wxCommandEvent& ev);
	void OnMenuItemAboutPressed(wxCommandEvent& ev);
	void OnWindowResized(wxSizeEvent& ev);
};
