#include "CodeVeinPanel.h"

CodeVeinPanel::CodeVeinPanel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
	: wxPanel(parent, wxID_ANY, pos, size)
{
	InitUI(*parent);
	BindEvents();
	if (!InitHack()) {
		wxMessageBox(wxT("Initializing Hack Functionality Failed!\nPlease consider contacting the developer."), wxT("Error"), wxICON_ERROR);
		parent->Close();
	}
	CreateValueUpdateThread();
	
	m_tUnlimitedHealth = nullptr;
	m_tUnlimitedIchor = nullptr;
}

CodeVeinPanel::~CodeVeinPanel()
{
	if (m_tUpdateValues)
	{
		WaitValueUpdateThreadFinishExecution();
	}
	if (m_tUnlimitedHealth)
	{
		WaitUnlimitedHealthThreadFinishExecution();
	}
	if (m_tUnlimitedIchor)
	{
		WaitUnlimitedIchorThreadFinishExecution();
	}
	UnbindEvents();
	delete colorGreen, colorRed;
	delete m_bitmapHeader;
}

void CodeVeinPanel::InitUI(const wxFrame& parent)
{
	colorGreen = new wxColour(0, 255, 0);
	colorRed = new wxColour(255, 0, 0);
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->Add(0, 0, 1, wxEXPAND, 5);

	// old way, loaded png from file
	/*wxBitmap headerImage;
	headerImage.LoadFile(wxT("CodeVeinHeaderImage.png"), wxBITMAP_TYPE_PNG);
	if (headerImage.IsOk())
	{
		m_bitmapHeader = new wxStaticBitmap(this, wxID_ANY, headerImage, wxDefaultPosition, wxSize(460, 259), 0);
		sizerHeader->Add(m_bitmapHeader, 0, wxALIGN_CENTER | wxALL, 5);
	}
	else
	{
		wxMessageBox(wxT("Failed to load the Header-Image."), wxString(parent.GetTitle() + wxT(" Error")), wxICON_ERROR);
	}*/
	
	// new way, load png direct from resources now it must not be shipped alongside the executable
	m_bitmapHeader = new wxStaticBitmap(this, wxID_ANY, wxBITMAP_PNG(IDB_PNG1), wxDefaultPosition, wxSize(600, 337), 0);

	mainSizer->Add(m_bitmapHeader, 0, wxALIGN_CENTER | wxALL, 5);


	wxBoxSizer* sizerAttributes;
	sizerAttributes = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerAttributesSub1;
	sizerAttributesSub1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerHaze1;
	sizerHaze1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtHaze = new wxStaticText(this, wxID_ANY, wxT("Haze:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtHaze->Wrap(-1);
	m_staticTxtHaze->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerHaze1->Add(m_staticTxtHaze, 0, wxALL, 5);

	m_staticTxtHazeCurrentVal = new wxStaticText(this, wxID_ANY, wxT("99"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtHazeCurrentVal->Wrap(-1);
	m_staticTxtHazeCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerHaze1->Add(m_staticTxtHazeCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerHaze1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerMaxHealth1;
	sizerMaxHealth1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtMaxHealth = new wxStaticText(this, wxID_ANY, wxT("Max. Health:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtMaxHealth->Wrap(-1);
	m_staticTxtMaxHealth->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerMaxHealth1->Add(m_staticTxtMaxHealth, 0, wxALL, 5);

	m_staticTxtMaxHealthCurrentVal = new wxStaticText(this, wxID_ANY, wxT("99"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtMaxHealthCurrentVal->Wrap(-1);
	m_staticTxtMaxHealthCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerMaxHealth1->Add(m_staticTxtMaxHealthCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerMaxHealth1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerHealth1;
	sizerHealth1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtHealth = new wxStaticText(this, wxID_ANY, wxT("Health:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtHealth->Wrap(-1);
	m_staticTxtHealth->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerHealth1->Add(m_staticTxtHealth, 0, wxALL, 5);

	m_staticTxtHealthCurrentVal = new wxStaticText(this, wxID_ANY, wxT("99"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtHealthCurrentVal->Wrap(-1);
	m_staticTxtHealthCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerHealth1->Add(m_staticTxtHealthCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerHealth1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerStamina1;
	sizerStamina1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtStamina = new wxStaticText(this, wxID_ANY, wxT("Stamina:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtStamina->Wrap(-1);
	m_staticTxtStamina->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerStamina1->Add(m_staticTxtStamina, 0, wxALL, 5);

	m_staticTxtStaminaCurrentVal = new wxStaticText(this, wxID_ANY, wxT("99"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtStaminaCurrentVal->Wrap(-1);
	m_staticTxtStaminaCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerStamina1->Add(m_staticTxtStaminaCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerStamina1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerIchor1;
	sizerIchor1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtIchor = new wxStaticText(this, wxID_ANY, wxT("Ichor:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtIchor->Wrap(-1);
	m_staticTxtIchor->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerIchor1->Add(m_staticTxtIchor, 0, wxALL, 5);

	m_staticTxtIchorCurrentVal = new wxStaticText(this, wxID_ANY, wxT("99"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtIchorCurrentVal->Wrap(-1);
	m_staticTxtIchorCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerIchor1->Add(m_staticTxtIchorCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerIchor1, 1, wxEXPAND, 5);


	sizerAttributes->Add(sizerAttributesSub1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerAttributesSub2;
	sizerAttributesSub2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerHaze2;
	sizerHaze2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnHazeAdd = new wxButton(this, wxID_ANY, wxT("+5000"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnHazeAdd->SetBackgroundColour(*colorGreen);
	sizerHaze2->Add(m_btnHazeAdd, 0, wxALL, 5);

	m_btnHazeSub = new wxButton(this, wxID_ANY, wxT("-5000"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnHazeSub->SetBackgroundColour(*colorRed);
	sizerHaze2->Add(m_btnHazeSub, 0, wxALL, 5);

	m_btnHazeMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerHaze2->Add(m_btnHazeMax, 0, wxALL, 5);

	m_btnHazeReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerHaze2->Add(m_btnHazeReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerHaze2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerMaxHealth2;
	sizerMaxHealth2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnMaxHealthAdd = new wxButton(this, wxID_ANY, wxT("+100"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnMaxHealthAdd->SetBackgroundColour(*colorGreen);
	sizerMaxHealth2->Add(m_btnMaxHealthAdd, 0, wxALL, 5);

	m_btnMaxHealthSub = new wxButton(this, wxID_ANY, wxT("-100"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnMaxHealthSub->SetBackgroundColour(*colorRed);
	sizerMaxHealth2->Add(m_btnMaxHealthSub, 0, wxALL, 5);

	m_btnMaxHealthMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerMaxHealth2->Add(m_btnMaxHealthMax, 0, wxALL, 5);

	m_btnMaxHealthReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerMaxHealth2->Add(m_btnMaxHealthReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerMaxHealth2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerHealth2;
	sizerHealth2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnHealthAdd = new wxButton(this, wxID_ANY, wxT("+100"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnHealthAdd->SetBackgroundColour(*colorGreen);
	sizerHealth2->Add(m_btnHealthAdd, 0, wxALL, 5);

	m_btnHealthSub = new wxButton(this, wxID_ANY, wxT("-100"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnHealthSub->SetBackgroundColour(*colorRed);
	sizerHealth2->Add(m_btnHealthSub, 0, wxALL, 5);

	m_btnHealthMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerHealth2->Add(m_btnHealthMax, 0, wxALL, 5);

	m_btnHealthReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerHealth2->Add(m_btnHealthReset, 0, wxALL, 5);

	m_btnHealthUnlimited = new wxButton(this, wxID_ANY, wxT("UNLTD"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnHealthUnlimited->SetBackgroundColour(*colorRed);
	sizerHealth2->Add(m_btnHealthUnlimited, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerHealth2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerStamina2;
	sizerStamina2 = new wxBoxSizer(wxHORIZONTAL);


	sizerStamina2->Add(0, 0, 1, wxEXPAND, 5);

	m_btnStaminaUnlimited = new wxButton(this, wxID_ANY, wxT("UNLTD"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnStaminaUnlimited->SetBackgroundColour(*colorRed);
	sizerStamina2->Add(m_btnStaminaUnlimited, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerStamina2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerIchor2;
	sizerIchor2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnIchorAdd = new wxButton(this, wxID_ANY, wxT("+2"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIchorAdd->SetBackgroundColour(*colorGreen);
	sizerIchor2->Add(m_btnIchorAdd, 0, wxALL, 5);

	m_btnIchorSub = new wxButton(this, wxID_ANY, wxT("-2"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIchorSub->SetBackgroundColour(*colorRed);
	sizerIchor2->Add(m_btnIchorSub, 0, wxALL, 5);

	m_btnIchorMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerIchor2->Add(m_btnIchorMax, 0, wxALL, 5);

	m_btnIchorReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	sizerIchor2->Add(m_btnIchorReset, 0, wxALL, 5);

	m_btnIchorUnlimited = new wxButton(this, wxID_ANY, wxT("UNLTD"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIchorUnlimited->SetBackgroundColour(*colorRed);
	sizerIchor2->Add(m_btnIchorUnlimited, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerIchor2, 1, wxEXPAND, 5);


	sizerAttributes->Add(sizerAttributesSub2, 1, wxEXPAND, 5);


	mainSizer->Add(sizerAttributes, 1, wxALIGN_CENTER, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5);


	this->SetSizer(mainSizer);
	this->Layout();
}

bool CodeVeinPanel::InitHack()
{
	procInfo.name = L"CodeVein-Win64-Shipping.exe";
	procInfo.moduleName = L"CodeVein-Win64-Shipping.exe";

	// Begin: Offsets
	std::vector<uint64_t> hazeOffsets		= { 0x60, 0xF8, 0x8, 0x538, 0x358, 0xA8, 0x548 };
	std::vector<uint64_t> maxHealthOffsets	= { 0x60, 0xF8, 0x8, 0x538, 0x358, 0xA8, 0x208 };
	std::vector<uint64_t> healthOffsets		= { 0x60, 0xF8, 0x8, 0x538, 0x358, 0xA8, 0x1FC };
	std::vector<uint64_t> staminaOffsets	= { 0x0, 0x0 };
	std::vector<uint64_t> ichorOffsets		= { 0x60, 0xF8, 0x8, 0x538, 0x358, 0xA8, 0x500 };
	std::vector<uint64_t> maxIchorOffsets	= { 0x60, 0xF8, 0x8, 0x538, 0x358, 0xA8, 0x508 };
	// End: Offsets

	// Begin: Get the Process Identifier
	procInfo.id = GetProcId(procInfo.name);
	if (!procInfo.id) // Error Checking
		return false;
	// End: Get the Process Identifier

	// Begin: Open a Handle to the Process
	procInfo.handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procInfo.id); // OpenProcess returns 0 if it fails
	if (!procInfo.handle) // Error Checking
		return false;
	// End: Open a Handle to the Process

	procInfo.moduleBaseAddress = GetModuleBaseAddress(procInfo.id, procInfo.moduleName);

	// Begin: get dynamic memory addresses
	uint64_t bpAttributes = procInfo.moduleBaseAddress + 0x429CEB8;
	procInfo.Addresses.emplace("haze", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, hazeOffsets));
	procInfo.Addresses.emplace("maxHealth", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, maxHealthOffsets));
	procInfo.Addresses.emplace("health", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, healthOffsets));
	procInfo.Addresses.emplace("stamina", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, staminaOffsets));
	procInfo.Addresses.emplace("ichor", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, ichorOffsets));
	procInfo.Addresses.emplace("maxIchor", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, maxIchorOffsets));
	// End: get dynamic memory addresses

	return true;
}

void CodeVeinPanel::BindEvents()
{
	// Begin: Connect Events
	m_btnHazeAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeAddPressed), this);
	m_btnHazeSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeSubPressed), this);
	m_btnHazeMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeMaxPressed), this);
	m_btnHazeReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeResetPressed), this);

	m_btnMaxHealthAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthAddPressed), this);
	m_btnMaxHealthSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthSubPressed), this);
	m_btnMaxHealthMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthMaxPressed), this);
	m_btnMaxHealthReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthResetPressed), this);

	m_btnHealthAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthAddPressed), this);
	m_btnHealthSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthSubPressed), this);
	m_btnHealthMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthMaxPressed), this);
	m_btnHealthReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthResetPressed), this);
	m_btnHealthUnlimited->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthUnlimitedPressed), this);

	m_btnStaminaUnlimited->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnStaminaUnlimitedPressed), this);

	m_btnIchorAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorAddPressed), this);
	m_btnIchorSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorSubPressed), this);
	m_btnIchorMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorMaxPressed), this);
	m_btnIchorReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorResetPressed), this);
	m_btnIchorUnlimited->Bind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorUnlimitedPressed), this);
	// End: Connect Events
}

void CodeVeinPanel::UnbindEvents()
{
	// Begin: Disconnect Events
	m_btnHazeAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeAddPressed), this);
	m_btnHazeSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeSubPressed), this);
	m_btnHazeMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeMaxPressed), this);
	m_btnHazeReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHazeResetPressed), this);

	m_btnMaxHealthAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthAddPressed), this);
	m_btnMaxHealthSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthSubPressed), this);
	m_btnMaxHealthMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthMaxPressed), this);
	m_btnMaxHealthReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnMaxHealthResetPressed), this);

	m_btnHealthAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthAddPressed), this);
	m_btnHealthSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthSubPressed), this);
	m_btnHealthMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthMaxPressed), this);
	m_btnHealthReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthResetPressed), this);
	m_btnHealthUnlimited->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnHealthUnlimitedPressed), this);

	m_btnStaminaUnlimited->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnStaminaUnlimitedPressed), this);

	m_btnIchorAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorAddPressed), this);
	m_btnIchorSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorSubPressed), this);
	m_btnIchorMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorMaxPressed), this);
	m_btnIchorReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorResetPressed), this);
	m_btnIchorUnlimited->Unbind(wxEVT_BUTTON, wxCommandEventHandler(CodeVeinPanel::OnBtnIchorUnlimitedPressed), this);
	// End: Disconnect Events
}

void CodeVeinPanel::CreateValueUpdateThread()
{
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_futureUpdateValues = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThreadUpdateValues = false;
	
	m_tUpdateValues = std::make_unique<std::thread>(&CodeVeinPanel::UpdateValues, this, std::move(barrier));
	m_tUpdateValues->detach();
}

void CodeVeinPanel::WaitValueUpdateThreadFinishExecution()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThreadUpdateValues = true;
	// wait for thread "m_tUpdateValues" to finish execution
	m_futureUpdateValues->wait();
}

void CodeVeinPanel::CreateUnlimitedHealthThread()
{
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_futureUnlimitedHealth = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThreadUnlimitedHealth = false;

	m_tUnlimitedHealth = std::make_unique<std::thread>(&CodeVeinPanel::UnlimitedHealth, this, std::move(barrier));
	m_tUnlimitedHealth->detach();
}

void CodeVeinPanel::WaitUnlimitedHealthThreadFinishExecution()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThreadUnlimitedHealth = true;
	// wait for thread to finish execution
	m_futureUnlimitedHealth->wait();
	m_tUnlimitedHealth = nullptr;
}

void CodeVeinPanel::CreateUnlimitedIchorThread()
{
	// create barrier and instantiate the future for it
	std::promise<void> barrier;
	m_futureUnlimitedIchor = std::make_unique<std::future<void>>(barrier.get_future());

	m_bTerminateThreadUnlimitedIchor = false;

	m_tUnlimitedIchor = std::make_unique<std::thread>(&CodeVeinPanel::UnlimitedIchor, this, std::move(barrier));
	m_tUnlimitedIchor->detach();
}

void CodeVeinPanel::WaitUnlimitedIchorThreadFinishExecution()
{
	// send the thread the "signal" to finish asap
	m_bTerminateThreadUnlimitedIchor = true;
	// wait for thread to finish execution
	m_futureUnlimitedIchor->wait();
	m_tUnlimitedIchor = nullptr;
}

void CodeVeinPanel::UpdateValues(std::promise<void> barrier)
{
	int iTemp = 0;
	float fTemp = 0.f;
	while (!m_bTerminateThreadUpdateValues)
	{
		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
		m_staticTxtHazeCurrentVal->SetLabelText(std::to_string(iTemp));

		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
		m_staticTxtMaxHealthCurrentVal->SetLabelText(std::to_string(fTemp));

		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
		m_staticTxtHealthCurrentVal->SetLabelText(std::to_string(fTemp));

		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("stamina")), &iTemp, sizeof(iTemp), NULL);
		m_staticTxtStaminaCurrentVal->SetLabelText(std::to_string(iTemp));

		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
		m_staticTxtIchorCurrentVal->SetLabelText(std::to_string(fTemp));

		// Sleep 0.75s to save resources
		std::this_thread::sleep_for(std::chrono::milliseconds(750));
	}
	barrier.set_value();
}

void CodeVeinPanel::UnlimitedHealth(std::promise<void> barrier)
{
	float fTemp = 9999.f;
	while (!m_bTerminateThreadUnlimitedHealth)
	{
		WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	barrier.set_value();
}

void CodeVeinPanel::UnlimitedIchor(std::promise<void> barrier)
{
	float fTemp;
	while (!m_bTerminateThreadUnlimitedIchor)
	{
		ReadProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("maxIchor")), &fTemp, sizeof(fTemp), NULL);
		WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	barrier.set_value();
}

void CodeVeinPanel::OnBtnHazeAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5000;
	if (iTemp > 99999999)
	{
		iTemp = 99999999;
	}
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHazeSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5000;
	if (iTemp < 0)
	{
		iTemp = 0;
	}
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHazeMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99999999;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("haze")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHazeResetPressed(wxCommandEvent& ev)
{
	// TODO
}

void CodeVeinPanel::OnBtnMaxHealthAddPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
	fTemp += 100.f;
	if (fTemp > 9999.f)
	{
		fTemp = 9999.f;
	}
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnMaxHealthSubPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
	fTemp -= 100.f;
	if (fTemp < 1.f)
	{
		fTemp = 1.f;
	}
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnMaxHealthMaxPressed(wxCommandEvent& ev)
{
	float fTemp = 9999.f;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("maxHealth")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnMaxHealthResetPressed(wxCommandEvent& ev)
{
	// TODO
}

void CodeVeinPanel::OnBtnHealthAddPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
	fTemp += 100.f;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHealthSubPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
	fTemp -= 100.f;
	if (fTemp < 1.f)
	{
		fTemp = 1.f;
	}
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHealthMaxPressed(wxCommandEvent& ev)
{
	float fTemp = 9999.f;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("health")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnHealthResetPressed(wxCommandEvent& ev)
{
	// TODO
}

void CodeVeinPanel::OnBtnHealthUnlimitedPressed(wxCommandEvent& ev)
{
	if (!m_tUnlimitedHealth)
	{
		CreateUnlimitedHealthThread();
		m_btnHealthUnlimited->SetBackgroundColour(*colorGreen);
	}
	else
	{
		WaitUnlimitedHealthThreadFinishExecution();
		m_btnHealthUnlimited->SetBackgroundColour(*colorRed);
	}
}

void CodeVeinPanel::OnBtnStaminaUnlimitedPressed(wxCommandEvent& ev)
{
	// TODO
}

void CodeVeinPanel::OnBtnIchorAddPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
	fTemp += 2.f;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnIchorSubPressed(wxCommandEvent& ev)
{
	float fTemp = 0.f;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
	fTemp -= 2.f;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnIchorMaxPressed(wxCommandEvent& ev)
{
	float fTemp;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("maxIchor")), &fTemp, sizeof(fTemp), NULL);
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("ichor")), &fTemp, sizeof(fTemp), NULL);
	ev.Skip();
}

void CodeVeinPanel::OnBtnIchorResetPressed(wxCommandEvent& ev)
{
	// TODO
}

void CodeVeinPanel::OnBtnIchorUnlimitedPressed(wxCommandEvent& ev)
{
	if (!m_tUnlimitedIchor)
	{
		CreateUnlimitedIchorThread();
		m_btnIchorUnlimited->SetBackgroundColour(*colorGreen);
	}
	else
	{
		WaitUnlimitedIchorThreadFinishExecution();
		m_btnIchorUnlimited->SetBackgroundColour(*colorRed);
	}
}
