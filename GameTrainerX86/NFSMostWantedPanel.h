#pragma once
#include "wx/wx.h"
#include "Proc.h"
#include "constants.h"
#include <thread>
#include <future>

class NFSMostWantedPanel
	: public wxPanel
{
public:

	NFSMostWantedPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size);
	~NFSMostWantedPanel();

private:
	// controls
	wxStaticText* m_staticTxtGameName;
	wxStaticText* m_staticTxtCash;
	wxStaticText* m_staticTxtCashCurrentAmount;
	wxTextCtrl* m_txtCtrlCash;
	wxButton* m_btnCashAdd;
	wxStaticText* m_staticTxtNos;
	wxStaticText* m_staticTxtNosStatus;
	wxStaticText* m_staticTxtNosGauge;
	wxGauge* m_gaugeNosCurrentAmount;
	wxTextCtrl* m_txtCtrlNos;
	wxButton* m_btnNosFillUp;
	wxButton* m_btnNosActivate;
	wxTextValidator validator;

	ProcInfo procInfo;

	// Get Everyting but the Dynamic Memory Addresses
	bool InitHack();

	// Get Dynamic Memory Address Cash
	void InitCash();

	// Get Dynamic Memory Address Nos
	void InitNos();

	// supposed to run in a detached thread until ~NFSMostWantedPanel
	void UpdateCashNosCurrentAmount(std::promise<void> barrier);
	// Updates m_staticTxtCashCurrentAmount 
	// this thread runs asynchronous until ~cApp
	std::unique_ptr<std::thread> m_tUpdateCash;
	// used in thread "m_tUpdateCash"
	// if set to true the thread terminates asap
	bool m_bTerminateThreadUpdateCash;
	// used for thread "m_tUpdateCash"
	// in ~NFSMostWantedPanel this future waits for the promise that the thread has finished
	std::unique_ptr<std::future<void>> m_barrierFutureUpdateCash;

	// supposed to run in a detached thread until
	void NosFillUp(std::promise<void> barrier);
	std::unique_ptr<std::thread> m_tNosFillUp;
	bool m_bTerminateThreadNosFillUp;
	bool m_bNosActivated;
	std::unique_ptr<std::future<void>> m_barrierFutureNosFillUp;

	//event handlers
	void OnBtnCashAddPressed(wxCommandEvent& event);
	void OnBtnNosFillUpPressed(wxCommandEvent& event);
	void OnBtnNosActivatePressed(wxCommandEvent& event);
};
