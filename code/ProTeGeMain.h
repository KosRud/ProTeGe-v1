/***************************************************************
 * Name:      ProTeGeMain.h
 * Purpose:   Defines Application Frame
 * Author:    Hase ()
 * Created:   2015-03-02
 * Copyright: Hase ()
 * License:
 **************************************************************/

#ifndef PROTEGEMAIN_H
#define PROTEGEMAIN_H

//(*Headers(ProTeGeFrame)
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/statbmp.h>
//*)

class ProTeGeFrame: public wxFrame
{
    public:

        ProTeGeFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ProTeGeFrame();

    private:

        //(*Handlers(ProTeGeFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl6Text(wxCommandEvent& event);
        void OnChoice7Select(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(ProTeGeFrame)
        static const long ID_BUTTON1;
        static const long ID_STATICBITMAP1;
        static const long ID_CHOICE1;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICLINE2;
        static const long ID_CHECKBOX1;
        static const long ID_STATICTEXT5;
        static const long ID_STATICLINE3;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT7;
        static const long ID_CHOICE3;
        static const long ID_STATICLINE4;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL5;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_CHOICE4;
        static const long ID_STATICTEXT11;
        static const long ID_CHOICE5;
        static const long ID_CHOICE6;
        static const long ID_STATICTEXT12;
        static const long ID_TEXTCTRL6;
        static const long ID_STATICLINE5;
        static const long ID_TEXTCTRL7;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT15;
        static const long ID_CHECKBOX2;
        static const long ID_STATICTEXT16;
        static const long ID_TEXTCTRL8;
        static const long ID_BUTTON2;
        static const long ID_STATICLINE6;
        static const long ID_BUTTON3;
        static const long ID_CHOICE7;
        static const long ID_STATICTEXT17;
        static const long ID_TEXTCTRL9;
        static const long ID_CHOICE8;
        static const long ID_CHOICE9;
        //*)

        //(*Declarations(ProTeGeFrame)
        wxStaticLine* StaticLine6;
        wxTextCtrl* TextCtrl3;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticLine* StaticLine2;
        wxChoice* Choice3;
        wxTextCtrl* TextCtrl9;
        wxStaticText* StaticText17;
        wxButton* Button1;
        wxCheckBox* CheckBox1;
        wxButton* Button2;
        wxStaticLine* StaticLine5;
        wxButton* Button3;
        wxChoice* Choice2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText10;
        wxStaticText* StaticText16;
        wxTextCtrl* TextCtrl5;
        wxChoice* Choice4;
        wxStaticText* StaticText3;
        wxStaticLine* StaticLine1;
        wxChoice* Choice5;
        wxChoice* Choice1;
        wxCheckBox* CheckBox2;
        wxStaticText* StaticText8;
        wxStaticText* StaticText12;
        wxChoice* Choice7;
        wxStaticLine* StaticLine3;
        wxTextCtrl* TextCtrl6;
        wxStaticText* StaticText7;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText4;
        wxChoice* Choice9;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxStaticBitmap* StaticBitmap1;
        wxStaticText* StaticText6;
        wxStaticLine* StaticLine4;
        wxTextCtrl* TextCtrl8;
        wxTextCtrl* TextCtrl7;
        wxChoice* Choice6;
        wxChoice* Choice8;
        wxStaticText* StaticText9;
        wxTextCtrl* TextCtrl4;
        wxTextCtrl* TextCtrl2;
        wxStaticText* StaticText11;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PROTEGEMAIN_H
