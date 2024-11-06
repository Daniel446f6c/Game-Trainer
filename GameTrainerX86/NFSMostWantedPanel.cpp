#include "NFSMostWantedPanel.h"

/*
	All UI-Elements, Fonts and Grids are defined in the constructor.
*/

NFSMostWantedPanel::NFSMostWantedPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size)
	: wxPanel(parent, wxID_ANY, pos, size)
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	m_staticTxtGameName = new wxStaticText(this, wxID_ANY, wxT("Need for Speed: Most Wanted"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtGameName->Wrap(-1);
	m_staticTxtGameName->SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	mainSizer->Add(m_staticTxtGameName, 0, wxALL, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5); // spacer

	wxBoxSizer* sizerCash;
	sizerCash = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerCashSub1;
	sizerCashSub1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtCash = new wxStaticText(this, wxID_ANY, wxT("Cash($):"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtCash->Wrap(-1);
	m_staticTxtCash->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerCashSub1->Add(m_staticTxtCash, 0, wxALL, 5);

	m_staticTxtCashCurrentAmount = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtCashCurrentAmount->Wrap(-1);
	m_staticTxtCashCurrentAmount->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerCashSub1->Add(m_staticTxtCashCurrentAmount, 0, wxALL, 5);


	sizerCash->Add(sizerCashSub1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerCashSub2;
	sizerCashSub2 = new wxBoxSizer(wxHORIZONTAL);
	
	validator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	validator.SetCharIncludes(wxT("0123456789"));
	m_txtCtrlCash = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, std::move(validator));
	m_txtCtrlCash->SetMaxLength(9);
	m_txtCtrlCash->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerCashSub2->Add(m_txtCtrlCash, 0, wxALL, 5);

	m_btnCashAdd = new wxButton(this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	m_btnCashAdd->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerCashSub2->Add(m_btnCashAdd, 0, wxALL, 5);


	sizerCash->Add(sizerCashSub2, 1, wxEXPAND, 5);


	mainSizer->Add(sizerCash, 1, wxEXPAND, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5); // spacer

	wxBoxSizer* sizerNos;
	sizerNos = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerNosSub1;
	sizerNosSub1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtNos = new wxStaticText(this, wxID_ANY, wxT("Unlimited Nos:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtNos->Wrap(-1);
	m_staticTxtNos->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerNosSub1->Add(m_staticTxtNos, 0, wxALL, 5);

	m_staticTxtNosStatus = new wxStaticText(this, wxID_ANY, wxT("Deactivated"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtNosStatus->Wrap(-1);
	m_staticTxtNosStatus->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerNosSub1->Add(m_staticTxtNosStatus, 0, wxALL, 5);


	sizerNosSub1->Add(0, 0, 1, wxEXPAND, 5); // spacer

	m_staticTxtNosGauge = new wxStaticText(this, wxID_ANY, wxT("Nos:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtNosGauge->Wrap(-1);
	m_staticTxtNosGauge->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerNosSub1->Add(m_staticTxtNosGauge, 0, wxALL, 5);

	m_gaugeNosCurrentAmount = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gaugeNosCurrentAmount->SetValue(0);
	sizerNosSub1->Add(m_gaugeNosCurrentAmount, 0, wxALL, 5);


	sizerNos->Add(sizerNosSub1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerNosSub2;
	sizerNosSub2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnNosFillUp = new wxButton(this, wxID_ANY, "Fill up", wxDefaultPosition, wxDefaultSize, 0);
	sizerNosSub2->Add(m_btnNosFillUp, 0, wxALL, 5);

	m_btnNosActivate = new wxButton(this, wxID_ANY, "Activate", wxDefaultPosition, wxDefaultSize, 0);
	sizerNosSub2->Add(m_btnNosActivate, 0, wxALL, 5);


	sizerNos->Add(sizerNosSub2, 1, wxEXPAND, 5);


	mainSizer->Add(sizerNos, 1, wxEXPAND, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5); // spacer


	this->SetSizer(mainSizer);
	this->Layout();

	// Begin: Connect Events
	m_btnCashAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnCashAddPressed), this);
	m_btnNosFillUp->Bind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnNosFillUpPressed), this);
	m_btnNosActivate->Bind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnNosActivatePressed), this);
	// End: Connect Events

	if (!InitHack())
	{
		wxMessageBox("Initializing Hack Functionality Failed!\nPlease consider contacting the developer.", "Error", wxICON_ERROR);
		parent->Close();
	}
}

NFSMostWantedPanel::~NFSMostWantedPanel()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThreadUpdateCash = true;

	// wait for thread "m_tUpdateCash" to finish execution
	m_barrierFutureUpdateCash->wait();

	// wait for thread "m_tUpdateCash" to finish execution
	if (m_bNosActivated)
	{
		m_bTerminateThreadNosFillUp = true;
		m_barrierFutureNosFillUp->wait();
	}

	// Begin: Disconnect Events
	m_btnCashAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnCashAddPressed), this);
	m_btnNosFillUp->Unbind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnNosFillUpPressed), this);
	m_btnNosActivate->Unbind(wxEVT_BUTTON, wxCommandEventHandler(NFSMostWantedPanel::OnBtnNosActivatePressed), this);
	// End: Disconnect Events
}

bool NFSMostWantedPanel::InitHack()
{
	procInfo.name = nfsMW::processName;
	procInfo.moduleName = nfsMW::processName;

	// Begin: Get the Process Identifier
	procInfo.id = GetProcId(procInfo.name);
	if (!procInfo.id) // Error Checking
		return false;
	// End: Get the Process Identifier

	// Begin: Open a Handle to the Process
	procInfo.handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procInfo.id); // OpenProcess returns 0 if it fails
	if (!OpenProcess(PROCESS_ALL_ACCESS, NULL, procInfo.id)) // Error Checking
		return false;
	// End: Open a Handle to the Process

	// Begin: Get Module Base Address
	procInfo.moduleBaseAddress = GetModuleBaseAddress(procInfo.id, procInfo.moduleName);
	// End: Get Module Base Address
	
	// Begin: Get Dynamic Memory Address
	InitCash();
	InitNos();
	// End: Get Dynamic Memory Address

	// Begin: m_tUpdateCash setup
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_barrierFutureUpdateCash = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThreadUpdateCash = false;
	// start updating current cash amount in asynchronous thread
	m_tUpdateCash = std::make_unique<std::thread>(&NFSMostWantedPanel::UpdateCashNosCurrentAmount, this, std::move(barrier));
	m_tUpdateCash->detach();
	// End: m_tUpdateCash setup

	m_bNosActivated = false;

	return true;
}

void NFSMostWantedPanel::InitCash()
{
	std::vector<uint64_t> offsets;
	offsets.reserve(nfsMW::offsetsCash.size());
	for (auto offset : nfsMW::offsetsCash) {
		offsets.push_back(offset);
	}

	uint64_t basePointer = procInfo.moduleBaseAddress + nfsMW::moduleBaseOffsetCash;

	procInfo.Addresses.emplace(nfsMW::cash, GetDynamicMemoryAddress(procInfo.handle, basePointer, offsets));
}

void NFSMostWantedPanel::InitNos()
{
	std::vector<uint64_t> offsets;
	offsets.reserve(nfsMW::offsetsNos.size());
	for (auto offset : nfsMW::offsetsNos) {
		offsets.push_back(offset);
	}
	
	uint64_t basePointer = procInfo.moduleBaseAddress + nfsMW::moduleBaseOffsetNos;

	for (auto iter = procInfo.Addresses.cbegin(); iter != procInfo.Addresses.cend(); iter++)
	{
		if (std::get<0>(*iter) == nfsMW::nos)
		{
			procInfo.Addresses.erase(iter);
			break;
		}
	}

	procInfo.Addresses.emplace(nfsMW::nos, GetDynamicMemoryAddress(procInfo.handle, basePointer, offsets));
}

void NFSMostWantedPanel::UpdateCashNosCurrentAmount(std::promise<void> barrier)
{
	int iTemp = 0;
	float fTemp = 0.f;
	while (!m_bTerminateThreadUpdateCash)
	{
		// Cash
		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at(nfsMW::cash)), &iTemp, sizeof(iTemp), nullptr);
		m_staticTxtCashCurrentAmount->SetLabelText(std::to_string(iTemp));
		
		// Nos
		InitNos();
		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at(nfsMW::nos)), &fTemp, sizeof(fTemp), nullptr);
		m_gaugeNosCurrentAmount->SetValue(static_cast<float>(fTemp * 100));
		
		// Sleep 0.03s to save resources
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	barrier.set_value();
}

void NFSMostWantedPanel::NosFillUp(std::promise<void> barrier)
{
	float fTemp = 1.f;
	while (!m_bTerminateThreadNosFillUp)
	{
		if (WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at(nfsMW::nos)), &fTemp, sizeof(fTemp), nullptr) == 0)
		{
			m_bTerminateThreadNosFillUp = !m_bTerminateThreadNosFillUp;
			m_bNosActivated = !m_bNosActivated;
			m_staticTxtNosStatus->SetLabelText("Deactivated");
			m_btnNosActivate->SetLabelText("Activate");
		}
		// Sleep 1.25s to save resources
		std::this_thread::sleep_for(std::chrono::milliseconds(1250));
	}
	barrier.set_value();
}

void NFSMostWantedPanel::OnBtnCashAddPressed(wxCommandEvent& ev)
{
	if (m_txtCtrlCash->GetLineLength(0) != 0)
	{
		int iTemp = std::stoi(static_cast<std::string>(m_txtCtrlCash->GetLineText(0)));
		if (iTemp != -1)
		{
			iTemp += std::stoi(static_cast<std::string>(m_staticTxtCashCurrentAmount->GetLabelText()));
			WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at(nfsMW::cash)), &iTemp, sizeof(iTemp), nullptr);
		}
	}
	ev.Skip();
}

void NFSMostWantedPanel::OnBtnNosFillUpPressed(wxCommandEvent& ev)
{
	float fTemp = 1.f;
	WriteProcessMemory(procInfo.handle, LPVOID(procInfo.Addresses.at(nfsMW::nos)), &fTemp, sizeof(fTemp), nullptr);
	ev.Skip();
}

void NFSMostWantedPanel::OnBtnNosActivatePressed(wxCommandEvent& ev)
{
	if (m_bNosActivated)
	{
		m_bTerminateThreadNosFillUp = m_bNosActivated;
		m_barrierFutureNosFillUp->wait();
		m_bNosActivated = !m_bNosActivated;
		m_staticTxtNosStatus->SetLabelText("Deactivated");
		m_btnNosActivate->SetLabelText("Activate");
	}
	else
	{
		InitNos();
		m_bTerminateThreadNosFillUp = m_bNosActivated;
		m_bNosActivated = !m_bNosActivated;
		std::promise<void> barrier;
		m_barrierFutureNosFillUp = std::make_unique<std::future<void>>(barrier.get_future());
		m_tNosFillUp = std::make_unique<std::thread>(&NFSMostWantedPanel::NosFillUp, this, std::move(barrier));
		m_tNosFillUp->detach();
		m_staticTxtNosStatus->SetLabelText("Activated");
		m_btnNosActivate->SetLabelText("Deactivate");
	}
	ev.Skip();
}
