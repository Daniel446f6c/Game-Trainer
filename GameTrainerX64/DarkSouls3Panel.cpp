#include "DarkSouls3Panel.h"


DarkSouls3Panel::DarkSouls3Panel(wxFrame* parent, const wxPoint& pos, const wxSize& size)
	: wxPanel(parent, wxID_ANY, pos, size)
{
	InitUI();
	BindEvents();
	if (!InitHack())
	{
		wxMessageBox(wxT("Initializing Hack Functionality Failed!\nPlease consider contacting the developer."), wxT("Error"), wxICON_ERROR);
		parent->Close();
	}
}

DarkSouls3Panel::~DarkSouls3Panel()
{
	UnbindEvents();
	delete colorGreen, colorRed, colorLightBlue;
}

void DarkSouls3Panel::InitUI()
{
	colorGreen = new wxColour(0, 255, 0);
	colorRed = new wxColour(255, 0, 0);
	colorLightBlue = new wxColour(173, 216, 230);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	m_staticTxtGameName = new wxStaticText(this, wxID_ANY, wxT("Dark Souls 3"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtGameName->Wrap(-1);
	m_staticTxtGameName->SetFont(wxFont(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	mainSizer->Add(m_staticTxtGameName, 0, wxALIGN_CENTER | wxALL, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* sizerAttributes;
	sizerAttributes = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerAttributesSub1;
	sizerAttributesSub1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerVigor1;
	sizerVigor1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtVigor = new wxStaticText(this, wxID_ANY, wxT("Vigor:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtVigor->Wrap(-1);
	m_staticTxtVigor->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerVigor1->Add(m_staticTxtVigor, 0, wxALL, 5);

	m_staticTxtVigorCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtVigorCurrentVal->Wrap(-1);
	m_staticTxtVigorCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerVigor1->Add(m_staticTxtVigorCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerVigor1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerAttunement1;
	sizerAttunement1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtAttunement = new wxStaticText(this, wxID_ANY, wxT("Attunement:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtAttunement->Wrap(-1);
	m_staticTxtAttunement->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerAttunement1->Add(m_staticTxtAttunement, 0, wxALL, 5);

	m_staticTxtAttunementCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtAttunementCurrentVal->Wrap(-1);
	m_staticTxtAttunementCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerAttunement1->Add(m_staticTxtAttunementCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerAttunement1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerEndurance1;
	sizerEndurance1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtEndurance = new wxStaticText(this, wxID_ANY, wxT("Endurance:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtEndurance->Wrap(-1);
	m_staticTxtEndurance->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerEndurance1->Add(m_staticTxtEndurance, 0, wxALL, 5);

	m_staticTxtEnduranceCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtEnduranceCurrentVal->Wrap(-1);
	m_staticTxtEnduranceCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerEndurance1->Add(m_staticTxtEnduranceCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerEndurance1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerVitality1;
	sizerVitality1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtVitality = new wxStaticText(this, wxID_ANY, wxT("Vitality:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtVitality->Wrap(-1);
	m_staticTxtVitality->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerVitality1->Add(m_staticTxtVitality, 0, wxALL, 5);

	m_staticTxtVitalityCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtVitalityCurrentVal->Wrap(-1);
	m_staticTxtVitalityCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerVitality1->Add(m_staticTxtVitalityCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerVitality1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerStrength1;
	sizerStrength1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtStrength = new wxStaticText(this, wxID_ANY, wxT("Strength:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtStrength->Wrap(-1);
	m_staticTxtStrength->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerStrength1->Add(m_staticTxtStrength, 0, wxALL, 5);

	m_staticTxtStrengthCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtStrengthCurrentVal->Wrap(-1);
	m_staticTxtStrengthCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerStrength1->Add(m_staticTxtStrengthCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerStrength1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerDexterity1;
	sizerDexterity1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtDexterity = new wxStaticText(this, wxID_ANY, wxT("Dexterity:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtDexterity->Wrap(-1);
	m_staticTxtDexterity->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerDexterity1->Add(m_staticTxtDexterity, 0, wxALL, 5);

	m_staticTxtDexterityCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtDexterityCurrentVal->Wrap(-1);
	m_staticTxtDexterityCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerDexterity1->Add(m_staticTxtDexterityCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerDexterity1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerIntelligence1;
	sizerIntelligence1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtIntelligence = new wxStaticText(this, wxID_ANY, wxT("Intelligence:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtIntelligence->Wrap(-1);
	m_staticTxtIntelligence->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerIntelligence1->Add(m_staticTxtIntelligence, 0, wxALL, 5);

	m_staticTxtIntelligenceCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtIntelligenceCurrentVal->Wrap(-1);
	m_staticTxtIntelligenceCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerIntelligence1->Add(m_staticTxtIntelligenceCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerIntelligence1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerFaith1;
	sizerFaith1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtFaith = new wxStaticText(this, wxID_ANY, wxT("Faith:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtFaith->Wrap(-1);
	m_staticTxtFaith->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerFaith1->Add(m_staticTxtFaith, 0, wxALL, 5);

	m_staticTxtFaithCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtFaithCurrentVal->Wrap(-1);
	m_staticTxtFaithCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerFaith1->Add(m_staticTxtFaithCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerFaith1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerLuck1;
	sizerLuck1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtLuck = new wxStaticText(this, wxID_ANY, wxT("Luck:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtLuck->Wrap(-1);
	m_staticTxtLuck->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerLuck1->Add(m_staticTxtLuck, 0, wxALL, 5);

	m_staticTxtLuckCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtLuckCurrentVal->Wrap(-1);
	m_staticTxtLuckCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerLuck1->Add(m_staticTxtLuckCurrentVal, 0, wxALL, 5);


	sizerAttributesSub1->Add(sizerLuck1, 1, wxEXPAND, 5);


	sizerAttributes->Add(sizerAttributesSub1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerAttributesSub2;
	sizerAttributesSub2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerVigor2;
	sizerVigor2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnVigorAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVigorAdd->SetBackgroundColour(*colorGreen);
	sizerVigor2->Add(m_btnVigorAdd, 0, wxALL, 5);

	m_btnVigorSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVigorSub->SetBackgroundColour(*colorRed);
	sizerVigor2->Add(m_btnVigorSub, 0, wxALL, 5);

	m_btnVigorMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVigorMax->SetBackgroundColour(*colorLightBlue);
	sizerVigor2->Add(m_btnVigorMax, 0, wxALL, 5);

	m_btnVigorReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVigorReset->SetBackgroundColour(*colorLightBlue);
	sizerVigor2->Add(m_btnVigorReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerVigor2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerAttunement2;
	sizerAttunement2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnAttunementAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnAttunementAdd->SetBackgroundColour(*colorGreen);
	sizerAttunement2->Add(m_btnAttunementAdd, 0, wxALL, 5);

	m_btnAttunementSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnAttunementSub->SetBackgroundColour(*colorRed);
	sizerAttunement2->Add(m_btnAttunementSub, 0, wxALL, 5);

	m_btnAttunementMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnAttunementMax->SetBackgroundColour(*colorLightBlue);
	sizerAttunement2->Add(m_btnAttunementMax, 0, wxALL, 5);

	m_btnAttunementReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnAttunementReset->SetBackgroundColour(*colorLightBlue);
	sizerAttunement2->Add(m_btnAttunementReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerAttunement2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerEndurance2;
	sizerEndurance2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnEnduranceAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnEnduranceAdd->SetBackgroundColour(*colorGreen);
	sizerEndurance2->Add(m_btnEnduranceAdd, 0, wxALL, 5);

	m_btnEnduranceSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnEnduranceSub->SetBackgroundColour(*colorRed);
	sizerEndurance2->Add(m_btnEnduranceSub, 0, wxALL, 5);

	m_btnEnduranceMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnEnduranceMax->SetBackgroundColour(*colorLightBlue);
	sizerEndurance2->Add(m_btnEnduranceMax, 0, wxALL, 5);

	m_btnEnduranceReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnEnduranceReset->SetBackgroundColour(*colorLightBlue);
	sizerEndurance2->Add(m_btnEnduranceReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerEndurance2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerVitality2;
	sizerVitality2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnVitalityAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVitalityAdd->SetBackgroundColour(*colorGreen);
	sizerVitality2->Add(m_btnVitalityAdd, 0, wxALL, 5);

	m_btnVitalitySub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVitalitySub->SetBackgroundColour(*colorRed);
	sizerVitality2->Add(m_btnVitalitySub, 0, wxALL, 5);

	m_btnVitalityMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVitalityMax->SetBackgroundColour(*colorLightBlue);
	sizerVitality2->Add(m_btnVitalityMax, 0, wxALL, 5);

	m_btnVitalityReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnVitalityReset->SetBackgroundColour(*colorLightBlue);
	sizerVitality2->Add(m_btnVitalityReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerVitality2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerStrength2;
	sizerStrength2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnStrengthAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnStrengthAdd->SetBackgroundColour(*colorGreen);
	sizerStrength2->Add(m_btnStrengthAdd, 0, wxALL, 5);

	m_btnStrengthSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnStrengthSub->SetBackgroundColour(*colorRed);
	sizerStrength2->Add(m_btnStrengthSub, 0, wxALL, 5);

	m_btnStrengthMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnStrengthMax->SetBackgroundColour(*colorLightBlue);
	sizerStrength2->Add(m_btnStrengthMax, 0, wxALL, 5);

	m_btnStrengthReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnStrengthReset->SetBackgroundColour(*colorLightBlue);
	sizerStrength2->Add(m_btnStrengthReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerStrength2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerDexterity2;
	sizerDexterity2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnDexterityAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnDexterityAdd->SetBackgroundColour(*colorGreen);
	sizerDexterity2->Add(m_btnDexterityAdd, 0, wxALL, 5);

	m_btnDexteritySub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnDexteritySub->SetBackgroundColour(*colorRed);
	sizerDexterity2->Add(m_btnDexteritySub, 0, wxALL, 5);

	m_btnDexterityMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnDexterityMax->SetBackgroundColour(*colorLightBlue);
	sizerDexterity2->Add(m_btnDexterityMax, 0, wxALL, 5);

	m_btnDexterityReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnDexterityReset->SetBackgroundColour(*colorLightBlue);
	sizerDexterity2->Add(m_btnDexterityReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerDexterity2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerIntelligence2;
	sizerIntelligence2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnIntelligenceAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIntelligenceAdd->SetBackgroundColour(*colorGreen);
	sizerIntelligence2->Add(m_btnIntelligenceAdd, 0, wxALL, 5);

	m_btnIntelligenceSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIntelligenceSub->SetBackgroundColour(*colorRed);
	sizerIntelligence2->Add(m_btnIntelligenceSub, 0, wxALL, 5);

	m_btnIntelligenceMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIntelligenceMax->SetBackgroundColour(*colorLightBlue);
	sizerIntelligence2->Add(m_btnIntelligenceMax, 0, wxALL, 5);

	m_btnIntelligenceReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnIntelligenceReset->SetBackgroundColour(*colorLightBlue);
	sizerIntelligence2->Add(m_btnIntelligenceReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerIntelligence2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerFaith2;
	sizerFaith2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnFaithAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnFaithAdd->SetBackgroundColour(*colorGreen);
	sizerFaith2->Add(m_btnFaithAdd, 0, wxALL, 5);

	m_btnFaithSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnFaithSub->SetBackgroundColour(*colorRed);
	sizerFaith2->Add(m_btnFaithSub, 0, wxALL, 5);

	m_btnFaithMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnFaithMax->SetBackgroundColour(*colorLightBlue);
	sizerFaith2->Add(m_btnFaithMax, 0, wxALL, 5);

	m_btnFaithReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnFaithReset->SetBackgroundColour(*colorLightBlue);
	sizerFaith2->Add(m_btnFaithReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerFaith2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerLuck2;
	sizerLuck2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnLuckAdd = new wxButton(this, wxID_ANY, wxT("+5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLuckAdd->SetBackgroundColour(*colorGreen);
	sizerLuck2->Add(m_btnLuckAdd, 0, wxALL, 5);

	m_btnLuckSub = new wxButton(this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLuckSub->SetBackgroundColour(*colorRed);
	sizerLuck2->Add(m_btnLuckSub, 0, wxALL, 5);

	m_btnLuckMax = new wxButton(this, wxID_ANY, wxT("MAX"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLuckMax->SetBackgroundColour(*colorLightBlue);
	sizerLuck2->Add(m_btnLuckMax, 0, wxALL, 5);

	m_btnLuckReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLuckReset->SetBackgroundColour(*colorLightBlue);
	sizerLuck2->Add(m_btnLuckReset, 0, wxALL, 5);


	sizerAttributesSub2->Add(sizerLuck2, 1, wxEXPAND, 5);


	sizerAttributes->Add(sizerAttributesSub2, 1, wxEXPAND, 5);


	mainSizer->Add(sizerAttributes, 1, wxEXPAND, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* sizerSoulsLevels;
	sizerSoulsLevels = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerSoulsLevelsSub1;
	sizerSoulsLevelsSub1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerSouls1;
	sizerSouls1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtSouls = new wxStaticText(this, wxID_ANY, wxT("Souls:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtSouls->Wrap(-1);
	m_staticTxtSouls->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerSouls1->Add(m_staticTxtSouls, 0, wxALL, 5);

	m_staticTxtSoulsCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtSoulsCurrentVal->Wrap(-1);
	m_staticTxtSoulsCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerSouls1->Add(m_staticTxtSoulsCurrentVal, 0, wxALL, 5);


	sizerSoulsLevelsSub1->Add(sizerSouls1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerLevels1;
	sizerLevels1 = new wxBoxSizer(wxHORIZONTAL);

	m_staticTxtLevel = new wxStaticText(this, wxID_ANY, wxT("Level:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtLevel->Wrap(-1);
	m_staticTxtLevel->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerLevels1->Add(m_staticTxtLevel, 0, wxALL, 5);

	m_staticTxtLevelCurrentVal = new wxStaticText(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTxtLevelCurrentVal->Wrap(-1);
	m_staticTxtLevelCurrentVal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	sizerLevels1->Add(m_staticTxtLevelCurrentVal, 0, wxALL, 5);


	sizerSoulsLevelsSub1->Add(sizerLevels1, 1, wxEXPAND, 5);


	sizerSoulsLevels->Add(sizerSoulsLevelsSub1, 1, wxEXPAND, 5);

	wxBoxSizer* sizerSoulsLevelsSub2;
	sizerSoulsLevelsSub2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerSouls2;
	sizerSouls2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnSoulsAdd = new wxButton(this, wxID_ANY, wxT("+500"), wxDefaultPosition, wxSize(45, 25));
	m_btnSoulsAdd->SetBackgroundColour(*colorGreen);
	sizerSouls2->Add(m_btnSoulsAdd, 0, wxALL, 5);

	m_btnSoulsSub = new wxButton(this, wxID_ANY, wxT("-500"), wxDefaultPosition, wxSize(45, 25));
	m_btnSoulsSub->SetBackgroundColour(*colorRed);
	sizerSouls2->Add(m_btnSoulsSub, 0, wxALL, 5);

	m_btnSoulsReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25));
	m_btnSoulsReset->SetBackgroundColour(*colorLightBlue);
	sizerSouls2->Add(m_btnSoulsReset, 0, wxALL, 5);


	sizerSoulsLevelsSub2->Add(sizerSouls2, 1, wxEXPAND, 5);

	wxBoxSizer* sizerLevels2;
	sizerLevels2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnLevelAdd = new wxButton(this, wxID_ANY, wxT("+1"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLevelAdd->SetBackgroundColour(*colorGreen);
	sizerLevels2->Add(m_btnLevelAdd, 0, wxALL, 5);

	m_btnLevelSub = new wxButton(this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLevelSub->SetBackgroundColour(*colorRed);
	sizerLevels2->Add(m_btnLevelSub, 0, wxALL, 5);

	m_btnLevelReset = new wxButton(this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxSize(45, 25), 0);
	m_btnLevelReset->SetBackgroundColour(*colorLightBlue);
	sizerLevels2->Add(m_btnLevelReset, 0, wxALL, 5);


	sizerSoulsLevelsSub2->Add(sizerLevels2, 1, wxEXPAND, 5);


	sizerSoulsLevels->Add(sizerSoulsLevelsSub2, 1, wxEXPAND, 5);


	mainSizer->Add(sizerSoulsLevels, 1, wxEXPAND, 5);


	mainSizer->Add(0, 0, 1, wxEXPAND, 5);


	this->SetSizer(mainSizer);
	this->Layout();
}

bool DarkSouls3Panel::InitHack()
{
	procInfo.name = L"DarkSoulsIII.exe";
	procInfo.moduleName = L"DarkSoulsIII.exe";

	// Begin: Offsets
	std::vector<uint64_t> vigorOffsets = { 0x10, 0x44 };
	std::vector<uint64_t> attunementOffsets = { 0x10, 0x48 };
	std::vector<uint64_t> enduranceOffsets = { 0x10, 0x4c };
	std::vector<uint64_t> vitalityOffsets = { 0x10, 0x6c };
	std::vector<uint64_t> strengthOffsets = { 0x10, 0x50 };
	std::vector<uint64_t> dexterityOffsets = { 0x10, 0x54 };
	std::vector<uint64_t> intelligenceOffsets = { 0x10, 0x58 };
	std::vector<uint64_t> faithOffsets = { 0x10, 0x5c };
	std::vector<uint64_t> luckOffsets = { 0x10, 0x60 };
	std::vector<uint64_t> soulsOffsets = { 0x10, 0x74 };
	std::vector<uint64_t> levelOffsets = { 0x10, 0x70 };
	// End: Offsets

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

	procInfo.moduleBaseAddress = GetModuleBaseAddress(procInfo.id, procInfo.moduleName);

	// Begin: get dynamic memory addresses
	uint64_t bpAttributes = procInfo.moduleBaseAddress + 0x4740178;
	procInfo.Addresses.emplace("vigor", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, vigorOffsets));
	procInfo.Addresses.emplace("attunement", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, attunementOffsets));
	procInfo.Addresses.emplace("endurance", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, enduranceOffsets));
	procInfo.Addresses.emplace("vitality", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, vitalityOffsets));
	procInfo.Addresses.emplace("strength", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, strengthOffsets));
	procInfo.Addresses.emplace("dexterity", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, dexterityOffsets));
	procInfo.Addresses.emplace("intelligence", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, intelligenceOffsets));
	procInfo.Addresses.emplace("faith", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, faithOffsets));
	procInfo.Addresses.emplace("luck", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, luckOffsets));
	procInfo.Addresses.emplace("souls", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, soulsOffsets));
	procInfo.Addresses.emplace("level", GetDynamicMemoryAddress(procInfo.handle, bpAttributes, levelOffsets));
	// End: get dynamic memory addresses

	return true;
}

void DarkSouls3Panel::BindEvents()
{
	m_btnVigorAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorAddPressed), this);
	m_btnVigorSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorSubPressed), this);
	m_btnVigorMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorMaxPressed), this);
	m_btnVigorReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorResetPressed), this);

	m_btnAttunementAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementAddPressed), this);
	m_btnAttunementSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementSubPressed), this);
	m_btnAttunementMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementMaxPressed), this);
	m_btnAttunementReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementResetPressed), this);

	m_btnEnduranceAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceAddPressed), this);
	m_btnEnduranceSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceSubPressed), this);
	m_btnEnduranceMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceMaxPressed), this);
	m_btnEnduranceReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceResetPressed), this);

	m_btnVitalityAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityAddPressed), this);
	m_btnVitalitySub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalitySubPressed), this);
	m_btnVitalityMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityMaxPressed), this);
	m_btnVitalityReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityResetPressed), this);

	m_btnStrengthAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthAddPressed), this);
	m_btnStrengthSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthSubPressed), this);
	m_btnStrengthMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthMaxPressed), this);
	m_btnStrengthReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthResetPressed), this);

	m_btnDexterityAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityAddPressed), this);
	m_btnDexteritySub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexteritySubPressed), this);
	m_btnDexterityMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityMaxPressed), this);
	m_btnDexterityReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityResetPressed), this);

	m_btnIntelligenceAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceAddPressed), this);
	m_btnIntelligenceSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceSubPressed), this);
	m_btnIntelligenceMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceMaxPressed), this);
	m_btnIntelligenceReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceResetPressed), this);

	m_btnFaithAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithAddPressed), this);
	m_btnFaithSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithSubPressed), this);
	m_btnFaithMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithMaxPressed), this);
	m_btnFaithReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithResetPressed), this);

	m_btnLuckAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckAddPressed), this);
	m_btnLuckSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckSubPressed), this);
	m_btnLuckMax->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckMaxPressed), this);
	m_btnLuckReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckResetPressed), this);

	m_btnSoulsAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsAddPressed), this);
	m_btnSoulsSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsSubPressed), this);
	m_btnSoulsReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsResetPressed), this);

	m_btnLevelAdd->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelAddPressed), this);
	m_btnLevelSub->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelSubPressed), this);
	m_btnLevelReset->Bind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelResetPressed), this);
}

void DarkSouls3Panel::UnbindEvents()
{
	m_btnVigorAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorAddPressed), this);
	m_btnVigorSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorSubPressed), this);
	m_btnVigorMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorMaxPressed), this);
	m_btnVigorReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVigorResetPressed), this);

	m_btnAttunementAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementAddPressed), this);
	m_btnAttunementSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementSubPressed), this);
	m_btnAttunementMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementMaxPressed), this);
	m_btnAttunementReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnAttunementResetPressed), this);

	m_btnEnduranceAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceAddPressed), this);
	m_btnEnduranceSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceSubPressed), this);
	m_btnEnduranceMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceMaxPressed), this);
	m_btnEnduranceReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnEnduranceResetPressed), this);

	m_btnVitalityAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityAddPressed), this);
	m_btnVitalitySub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalitySubPressed), this);
	m_btnVitalityMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityMaxPressed), this);
	m_btnVitalityReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnVitalityResetPressed), this);

	m_btnStrengthAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthAddPressed), this);
	m_btnStrengthSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthSubPressed), this);
	m_btnStrengthMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthMaxPressed), this);
	m_btnStrengthReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnStrengthResetPressed), this);

	m_btnDexterityAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityAddPressed), this);
	m_btnDexteritySub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexteritySubPressed), this);
	m_btnDexterityMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityMaxPressed), this);
	m_btnDexterityReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnDexterityResetPressed), this);

	m_btnIntelligenceAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceAddPressed), this);
	m_btnIntelligenceSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceSubPressed), this);
	m_btnIntelligenceMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceMaxPressed), this);
	m_btnIntelligenceReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnIntelligenceResetPressed), this);

	m_btnFaithAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithAddPressed), this);
	m_btnFaithSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithSubPressed), this);
	m_btnFaithMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithMaxPressed), this);
	m_btnFaithReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnFaithResetPressed), this);

	m_btnLuckAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckAddPressed), this);
	m_btnLuckSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckSubPressed), this);
	m_btnLuckMax->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckMaxPressed), this);
	m_btnLuckReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLuckResetPressed), this);

	m_btnSoulsAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsAddPressed), this);
	m_btnSoulsSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsSubPressed), this);
	m_btnSoulsReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnSoulsResetPressed), this);

	m_btnLevelAdd->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelAddPressed), this);
	m_btnLevelSub->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelSubPressed), this);
	m_btnLevelReset->Unbind(wxEVT_BUTTON, wxCommandEventHandler(DarkSouls3Panel::OnBtnLevelResetPressed), this);
}

void DarkSouls3Panel::OnBtnVigorAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("vigor")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vigor")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVigorSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("vigor")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vigor")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVigorMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vigor")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVigorResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnAttunementAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("attunement")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("attunement")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnAttunementSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("attunement")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("attunement")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnAttunementMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("attunement")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnAttunementResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnEnduranceAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("endurance")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("endurance")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnEnduranceSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("endurance")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("endurance")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnEnduranceMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("endurance")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnEnduranceResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnVitalityAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("vitality")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vitality")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVitalitySubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("vitality")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vitality")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVitalityMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("vitality")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnVitalityResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnStrengthAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("strength")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("strength")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnStrengthSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("strength")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("strength")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnStrengthMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("strength")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnStrengthResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnDexterityAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("dexterity")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("dexterity")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnDexteritySubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("dexterity")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("dexterity")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnDexterityMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("dexterity")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnDexterityResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnIntelligenceAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("intelligence")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("intelligence")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnIntelligenceSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("intelligence")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("intelligence")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnIntelligenceMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("intelligence")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnIntelligenceResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnFaithAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("faith")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("faith")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnFaithSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("faith")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("faith")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnFaithMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("faith")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnFaithResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnLuckAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("luck")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("luck")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnLuckSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("luck")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 5;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("luck")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnLuckMaxPressed(wxCommandEvent& ev)
{
	int iTemp = 99;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("luck")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnLuckResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnSoulsAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("souls")), &iTemp, sizeof(iTemp), NULL);
	iTemp += 500;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("souls")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnSoulsSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("souls")), &iTemp, sizeof(iTemp), NULL);
	iTemp -= 500;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("souls")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnSoulsResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}

void DarkSouls3Panel::OnBtnLevelAddPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("level")), &iTemp, sizeof(iTemp), NULL);
	iTemp ++;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("level")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnLevelSubPressed(wxCommandEvent& ev)
{
	int iTemp = 0;
	ReadProcessMemory(procInfo.handle, reinterpret_cast<LPCVOID>(procInfo.Addresses.at("level")), &iTemp, sizeof(iTemp), NULL);
	iTemp--;
	WriteProcessMemory(procInfo.handle, reinterpret_cast<LPVOID>(procInfo.Addresses.at("level")), &iTemp, sizeof(iTemp), NULL);
	ev.Skip();
}

void DarkSouls3Panel::OnBtnLevelResetPressed(wxCommandEvent& ev)
{
	// TODO
	wxMessageBox("TODO", "DeltaWin", wxICON_INFORMATION);
}