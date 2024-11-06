#pragma once
#include "wx/wx.h"
#include "Proc.h"

class DarkSouls3Panel
	: public wxPanel
{
public:
	DarkSouls3Panel(wxFrame *parent, const wxPoint& pos, const wxSize& size);
	~DarkSouls3Panel();

private:
	// controls
	wxStaticText* m_staticTxtGameName;
	wxStaticText* m_staticTxtVigor;
	wxStaticText* m_staticTxtVigorCurrentVal;
	wxStaticText* m_staticTxtAttunement;
	wxStaticText* m_staticTxtAttunementCurrentVal;
	wxStaticText* m_staticTxtEndurance;
	wxStaticText* m_staticTxtEnduranceCurrentVal;
	wxStaticText* m_staticTxtVitality;
	wxStaticText* m_staticTxtVitalityCurrentVal;
	wxStaticText* m_staticTxtStrength;
	wxStaticText* m_staticTxtStrengthCurrentVal;
	wxStaticText* m_staticTxtDexterity;
	wxStaticText* m_staticTxtDexterityCurrentVal;
	wxStaticText* m_staticTxtIntelligence;
	wxStaticText* m_staticTxtIntelligenceCurrentVal;
	wxStaticText* m_staticTxtFaith;
	wxStaticText* m_staticTxtFaithCurrentVal;
	wxStaticText* m_staticTxtLuck;
	wxStaticText* m_staticTxtLuckCurrentVal;
	wxButton* m_btnVigorAdd;
	wxButton* m_btnVigorSub;
	wxButton* m_btnVigorMax;
	wxButton* m_btnVigorReset;
	wxButton* m_btnAttunementAdd;
	wxButton* m_btnAttunementSub;
	wxButton* m_btnAttunementMax;
	wxButton* m_btnAttunementReset;
	wxButton* m_btnEnduranceAdd;
	wxButton* m_btnEnduranceSub;
	wxButton* m_btnEnduranceMax;
	wxButton* m_btnEnduranceReset;
	wxButton* m_btnVitalityAdd;
	wxButton* m_btnVitalitySub;
	wxButton* m_btnVitalityMax;
	wxButton* m_btnVitalityReset;
	wxButton* m_btnStrengthAdd;
	wxButton* m_btnStrengthSub;
	wxButton* m_btnStrengthMax;
	wxButton* m_btnStrengthReset;
	wxButton* m_btnDexterityAdd;
	wxButton* m_btnDexteritySub;
	wxButton* m_btnDexterityMax;
	wxButton* m_btnDexterityReset;
	wxButton* m_btnIntelligenceAdd;
	wxButton* m_btnIntelligenceSub;
	wxButton* m_btnIntelligenceMax;
	wxButton* m_btnIntelligenceReset;
	wxButton* m_btnFaithAdd;
	wxButton* m_btnFaithSub;
	wxButton* m_btnFaithMax;
	wxButton* m_btnFaithReset;
	wxButton* m_btnLuckAdd;
	wxButton* m_btnLuckSub;
	wxButton* m_btnLuckMax;
	wxButton* m_btnLuckReset;
	wxStaticText* m_staticTxtSouls;
	wxStaticText* m_staticTxtSoulsCurrentVal;
	wxStaticText* m_staticTxtLevel;
	wxStaticText* m_staticTxtLevelCurrentVal;
	wxButton* m_btnSoulsAdd;
	wxButton* m_btnSoulsSub;
	wxButton* m_btnSoulsReset;
	wxButton* m_btnLevelAdd;
	wxButton* m_btnLevelSub;
	wxButton* m_btnLevelReset;
	wxColour* colorGreen;
	wxColour* colorRed;
	wxColour* colorLightBlue;

	ProcInfo procInfo;

	void InitUI();
	bool InitHack();
	void BindEvents();
	void UnbindEvents();


	// event handler
	void OnBtnVigorAddPressed(wxCommandEvent &ev);
	void OnBtnVigorSubPressed(wxCommandEvent &ev);
	void OnBtnVigorMaxPressed(wxCommandEvent &ev);
	void OnBtnVigorResetPressed(wxCommandEvent &ev);

	void OnBtnAttunementAddPressed(wxCommandEvent& ev);
	void OnBtnAttunementSubPressed(wxCommandEvent& ev);
	void OnBtnAttunementMaxPressed(wxCommandEvent& ev);
	void OnBtnAttunementResetPressed(wxCommandEvent& ev);

	void OnBtnEnduranceAddPressed(wxCommandEvent& ev);
	void OnBtnEnduranceSubPressed(wxCommandEvent& ev);
	void OnBtnEnduranceMaxPressed(wxCommandEvent& ev);
	void OnBtnEnduranceResetPressed(wxCommandEvent& ev);

	void OnBtnVitalityAddPressed(wxCommandEvent& ev);
	void OnBtnVitalitySubPressed(wxCommandEvent& ev);
	void OnBtnVitalityMaxPressed(wxCommandEvent& ev);
	void OnBtnVitalityResetPressed(wxCommandEvent& ev);

	void OnBtnStrengthAddPressed(wxCommandEvent& ev);
	void OnBtnStrengthSubPressed(wxCommandEvent& ev);
	void OnBtnStrengthMaxPressed(wxCommandEvent& ev);
	void OnBtnStrengthResetPressed(wxCommandEvent& ev);

	void OnBtnDexterityAddPressed(wxCommandEvent& ev);
	void OnBtnDexteritySubPressed(wxCommandEvent& ev);
	void OnBtnDexterityMaxPressed(wxCommandEvent& ev);
	void OnBtnDexterityResetPressed(wxCommandEvent& ev);

	void OnBtnIntelligenceAddPressed(wxCommandEvent& ev);
	void OnBtnIntelligenceSubPressed(wxCommandEvent& ev);
	void OnBtnIntelligenceMaxPressed(wxCommandEvent& ev);
	void OnBtnIntelligenceResetPressed(wxCommandEvent& ev);

	void OnBtnFaithAddPressed(wxCommandEvent& ev);
	void OnBtnFaithSubPressed(wxCommandEvent& ev);
	void OnBtnFaithMaxPressed(wxCommandEvent& ev);
	void OnBtnFaithResetPressed(wxCommandEvent& ev);

	void OnBtnLuckAddPressed(wxCommandEvent& ev);
	void OnBtnLuckSubPressed(wxCommandEvent& ev);
	void OnBtnLuckMaxPressed(wxCommandEvent& ev);
	void OnBtnLuckResetPressed(wxCommandEvent& ev);

	void OnBtnSoulsAddPressed(wxCommandEvent& ev);
	void OnBtnSoulsSubPressed(wxCommandEvent& ev);
	void OnBtnSoulsResetPressed(wxCommandEvent& ev);

	void OnBtnLevelAddPressed(wxCommandEvent& ev);
	void OnBtnLevelSubPressed(wxCommandEvent& ev);
	void OnBtnLevelResetPressed(wxCommandEvent& ev);
};
