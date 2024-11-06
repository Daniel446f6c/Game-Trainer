#pragma once
#include "wx/wx.h"
#include "Proc.h"
#include <thread>
#include <future>

class CodeVeinPanel
	: public wxPanel
{
public:
	CodeVeinPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size);
	~CodeVeinPanel();

private:
	//controls
	wxStaticBitmap* m_bitmapHeader;
	wxStaticText* m_staticTxtHaze;
	wxStaticText* m_staticTxtHazeCurrentVal;
	wxStaticText* m_staticTxtMaxHealth;
	wxStaticText* m_staticTxtMaxHealthCurrentVal;
	wxStaticText* m_staticTxtHealth;
	wxStaticText* m_staticTxtHealthCurrentVal;
	wxStaticText* m_staticTxtStamina;
	wxStaticText* m_staticTxtStaminaCurrentVal;
	wxStaticText* m_staticTxtIchor;
	wxStaticText* m_staticTxtIchorCurrentVal;
	wxButton* m_btnHazeAdd;
	wxButton* m_btnHazeSub;
	wxButton* m_btnHazeMax;
	wxButton* m_btnHazeReset;
	wxButton* m_btnMaxHealthAdd;
	wxButton* m_btnMaxHealthSub;
	wxButton* m_btnMaxHealthMax;
	wxButton* m_btnMaxHealthReset;
	wxButton* m_btnHealthAdd;
	wxButton* m_btnHealthSub;
	wxButton* m_btnHealthMax;
	wxButton* m_btnHealthReset;
	wxButton* m_btnHealthUnlimited;
	wxButton* m_btnStaminaUnlimited;
	wxButton* m_btnIchorAdd;
	wxButton* m_btnIchorSub;
	wxButton* m_btnIchorMax;
	wxButton* m_btnIchorReset;
	wxButton* m_btnIchorUnlimited;
	wxColour* colorGreen;
	wxColour* colorRed;

	ProcInfo procInfo;


	void InitUI(const wxFrame& parent);
	bool InitHack();
	void BindEvents();
	void UnbindEvents();
	void CreateValueUpdateThread();
	void WaitValueUpdateThreadFinishExecution();
	void CreateUnlimitedHealthThread();
	void WaitUnlimitedHealthThreadFinishExecution();
	void CreateUnlimitedIchorThread();
	void WaitUnlimitedIchorThreadFinishExecution();

	// supposed to run in a detached thread until ~CodeVeinPanel
	void UpdateValues(std::promise<void> barrier);
	std::unique_ptr<std::thread> m_tUpdateValues;
	bool m_bTerminateThreadUpdateValues;
	std::unique_ptr<std::future<void>> m_futureUpdateValues;

	// Unlimited Health Thread
	void UnlimitedHealth(std::promise<void> barrier);
	std::unique_ptr<std::thread> m_tUnlimitedHealth;
	bool m_bTerminateThreadUnlimitedHealth;
	std::unique_ptr<std::future<void>> m_futureUnlimitedHealth;

	// Unlimited Ichor Thread
	void UnlimitedIchor(std::promise<void> barrier);
	std::unique_ptr<std::thread> m_tUnlimitedIchor;
	bool m_bTerminateThreadUnlimitedIchor;
	std::unique_ptr<std::future<void>> m_futureUnlimitedIchor;

	// event handler
	void OnBtnHazeAddPressed(wxCommandEvent& ev);
	void OnBtnHazeSubPressed(wxCommandEvent& ev);
	void OnBtnHazeMaxPressed(wxCommandEvent& ev);
	void OnBtnHazeResetPressed(wxCommandEvent& ev);

	void OnBtnMaxHealthAddPressed(wxCommandEvent& ev);
	void OnBtnMaxHealthSubPressed(wxCommandEvent& ev);
	void OnBtnMaxHealthMaxPressed(wxCommandEvent& ev);
	void OnBtnMaxHealthResetPressed(wxCommandEvent& ev);

	void OnBtnHealthAddPressed(wxCommandEvent& ev);
	void OnBtnHealthSubPressed(wxCommandEvent& ev);
	void OnBtnHealthMaxPressed(wxCommandEvent& ev);
	void OnBtnHealthResetPressed(wxCommandEvent& ev);
	void OnBtnHealthUnlimitedPressed(wxCommandEvent& ev);

	void OnBtnStaminaUnlimitedPressed(wxCommandEvent& ev);

	void OnBtnIchorAddPressed(wxCommandEvent& ev);
	void OnBtnIchorSubPressed(wxCommandEvent& ev);
	void OnBtnIchorMaxPressed(wxCommandEvent& ev);
	void OnBtnIchorResetPressed(wxCommandEvent& ev);
	void OnBtnIchorUnlimitedPressed(wxCommandEvent& ev);
};