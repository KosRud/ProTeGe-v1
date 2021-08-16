/***************************************************************
 * Name:      ProTeGeMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hase ()
 * Created:   2015-03-02
 * Copyright: Hase ()
 * License:
 **************************************************************/

#include "ProTeGeMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/image.h>

#include "ProTeGe.h"

using namespace PTG;

//(*InternalHeaders(ProTeGeFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ProTeGeFrame)
const long ProTeGeFrame::ID_BUTTON1 = wxNewId();
const long ProTeGeFrame::ID_STATICBITMAP1 = wxNewId();
const long ProTeGeFrame::ID_CHOICE1 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE1 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT1 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL1 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT2 = wxNewId();
const long ProTeGeFrame::ID_CHOICE2 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT3 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL2 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT4 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL3 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE2 = wxNewId();
const long ProTeGeFrame::ID_CHECKBOX1 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT5 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE3 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT6 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL4 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT7 = wxNewId();
const long ProTeGeFrame::ID_CHOICE3 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE4 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT8 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL5 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT9 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT10 = wxNewId();
const long ProTeGeFrame::ID_CHOICE4 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT11 = wxNewId();
const long ProTeGeFrame::ID_CHOICE5 = wxNewId();
const long ProTeGeFrame::ID_CHOICE6 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT12 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL6 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE5 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL7 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT13 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT14 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT15 = wxNewId();
const long ProTeGeFrame::ID_CHECKBOX2 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT16 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL8 = wxNewId();
const long ProTeGeFrame::ID_BUTTON2 = wxNewId();
const long ProTeGeFrame::ID_STATICLINE6 = wxNewId();
const long ProTeGeFrame::ID_BUTTON3 = wxNewId();
const long ProTeGeFrame::ID_CHOICE7 = wxNewId();
const long ProTeGeFrame::ID_STATICTEXT17 = wxNewId();
const long ProTeGeFrame::ID_TEXTCTRL9 = wxNewId();
const long ProTeGeFrame::ID_CHOICE8 = wxNewId();
const long ProTeGeFrame::ID_CHOICE9 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ProTeGeFrame,wxFrame)
    //(*EventTable(ProTeGeFrame)
    //*)
END_EVENT_TABLE()

ProTeGeFrame::ProTeGeFrame(wxWindow* parent,wxWindowID id)
{
    srand(time(0));

    //(*Initialize(ProTeGeFrame)
    Create(parent, wxID_ANY, _("ProTeGe"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(964,561));
    Button1 = new wxButton(this, ID_BUTTON1, _("Generate"), wxPoint(544,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxPoint(16,8), wxSize(328,136), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(632,8), wxSize(152,32), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("Wavelet")) );
    Choice1->Append(_("Perlin"));
    Choice1->Append(_("White"));
    Choice1->Append(_("Cellular"));
    Choice1->Append(_("Convolution"));
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(552,88), wxSize(232,8), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Distribution coef:"), wxPoint(544,56), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("1"), wxPoint(664,48), wxSize(120,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Pattern:"), wxPoint(608,112), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    Choice2 = new wxChoice(this, ID_CHOICE2, wxPoint(664,104), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Choice2->SetSelection( Choice2->Append(_("None")) );
    Choice2->Append(_("Marble"));
    Choice2->Append(_("Wood"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Pattern cycles:"), wxPoint(560,144), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("10"), wxPoint(664,136), wxSize(120,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Noise coef"), wxPoint(592,176), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, _("1"), wxPoint(664,168), wxSize(120,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxPoint(552,200), wxSize(232,32), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("use gaussian (slow)"), wxPoint(632,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("For white and wavelet:"), wxPoint(552,232), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxPoint(552,320), wxSize(240,8), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("gaussian size coef:"), wxPoint(552,288), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, _("0.3"), wxPoint(680,280), wxSize(104,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Perlin mode:"), wxPoint(576,344), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    Choice3 = new wxChoice(this, ID_CHOICE3, wxPoint(664,336), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice3->SetSelection( Choice3->Append(_("normal")) );
    Choice3->Append(_("modulus"));
    Choice3->Append(_("inverted modulus"));
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxPoint(552,376), wxSize(240,8), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Cell amount:"), wxPoint(568,400), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    TextCtrl5 = new wxTextCtrl(this, ID_TEXTCTRL5, _("8"), wxPoint(664,392), wxSize(120,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Mode"), wxPoint(616,432), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Shape:"), wxPoint(608,464), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    Choice4 = new wxChoice(this, ID_CHOICE4, wxPoint(664,424), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    Choice4->Append(_("inverted bubble"));
    Choice4->SetSelection( Choice4->Append(_("bubble")) );
    Choice4->Append(_("stone"));
    Choice4->Append(_("deep stone"));
    Choice4->Append(_("inverted bubble net"));
    Choice4->Append(_("3D bubbles"));
    StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Mosaic"), wxPoint(608,496), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    Choice5 = new wxChoice(this, ID_CHOICE5, wxPoint(664,456), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    Choice5->SetSelection( Choice5->Append(_("stone")) );
    Choice5->Append(_("pyramid"));
    Choice5->Append(_("square stone"));
    Choice6 = new wxChoice(this, ID_CHOICE6, wxPoint(664,488), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
    Choice6->SetSelection( Choice6->Append(_("no mosaic")) );
    Choice6->Append(_("flat"));
    Choice6->Append(_("shiny"));
    StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Gloss:"), wxPoint(616,528), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    TextCtrl6 = new wxTextCtrl(this, ID_TEXTCTRL6, _("1"), wxPoint(664,520), wxSize(120,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxPoint(784,8), wxSize(32,544), wxLI_VERTICAL, _T("ID_STATICLINE5"));
    TextCtrl7 = new wxTextCtrl(this, ID_TEXTCTRL7, _("30"), wxPoint(872,40), wxSize(88,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Convolution:"), wxPoint(840,16), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("amount:"), wxPoint(808,48), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("shape:"), wxPoint(816,80), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("use gaussian"), wxPoint(808,144), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("contrast:"), wxPoint(808,176), wxSize(64,18), 0, _T("ID_STATICTEXT16"));
    TextCtrl8 = new wxTextCtrl(this, ID_TEXTCTRL8, _("0.8"), wxPoint(872,168), wxSize(88,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    Button2 = new wxButton(this, ID_BUTTON2, _("load from file"), wxPoint(808,200), wxSize(152,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticLine6 = new wxStaticLine(this, ID_STATICLINE6, wxPoint(808,264), wxSize(144,32), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    Button3 = new wxButton(this, ID_BUTTON3, _("save to file"), wxPoint(808,296), wxSize(152,32), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Choice7 = new wxChoice(this, ID_CHOICE7, wxPoint(872,72), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
    Choice7->SetSelection( Choice7->Append(_("star")) );
    Choice7->Append(_("square"));
    Choice7->Append(_("gaussian"));
    Choice7->Append(_("file"));
    StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("size:"), wxPoint(832,112), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    TextCtrl9 = new wxTextCtrl(this, ID_TEXTCTRL9, _("15"), wxPoint(872,104), wxSize(88,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    Choice8 = new wxChoice(this, ID_CHOICE8, wxPoint(808,240), wxSize(152,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE8"));
    Choice8->SetSelection( Choice8->Append(_("16x16")) );
    Choice8->Append(_("32x32"));
    Choice8->Append(_("64x64"));
    Choice8->Append(_("128x128"));
    Choice9 = new wxChoice(this, ID_CHOICE9, wxPoint(808,336), wxSize(152,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE9"));
    Choice9->SetSelection( Choice9->Append(_("512x512")) );
    Choice9->Append(_("1024x1024"));
    Choice9->Append(_("2048x2048"));
    Choice9->Append(_("4096x4096"));

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProTeGeFrame::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProTeGeFrame::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProTeGeFrame::OnButton3Click);
    //*)
}

ProTeGeFrame::~ProTeGeFrame()
{
    //(*Destroy(ProTeGeFrame)
    //*)
}

void ProTeGeFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ProTeGeFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

greyscale base;

void ProTeGeFrame::OnButton1Click(wxCommandEvent& event)
{
    greyscale test;

    double d_coef, n_coef, gloss, contrast;
    long p_scale, cell_amount, conv_amount, size;

    TextCtrl1->GetValue().ToDouble(&d_coef);
    TextCtrl2->GetValue().ToLong(&p_scale);
    TextCtrl3->GetValue().ToDouble(&n_coef);
    TextCtrl5->GetValue().ToLong(&cell_amount);
    TextCtrl6->GetValue().ToDouble(&gloss);
    TextCtrl7->GetValue().ToLong(&conv_amount);
    TextCtrl8->GetValue().ToDouble(&contrast);
    TextCtrl9->GetValue().ToLong(&size);

    if(d_coef <= 0 or gloss <= 0 or p_scale <= 0 or cell_amount <= 0 or
       conv_amount <= 0 or size <= 0)
    {
        wxMessageBox(wxT("Wrong input!"));
        return;
    }

    switch(Choice7->GetSelection())
    {
    case 0:
        base = Base_figures::star(size, 1.6);
        break;
    case 1:
        base = Base_figures::square(size);
        break;
    case 2:
        base = Base_figures::gaussian(size);
        break;
    case 3:
        break;
    }


    //test = Noises::wavelet(512, 1.2);

    switch(Choice1->GetSelection())
    {
    case 0:
        test = Noises::wavelet(512, d_coef);
        break;
    case 1:
        test = Noises::fractal_perlin(512, d_coef, Choice3->GetSelection());
        break;
    case 2:
        test = Noises::fractal_white(512, d_coef);
        break;
    case 3:
        test = Noises::celluar(512,cell_amount,Choice4->GetSelection(),Choice5->GetSelection(),
                               Choice6->GetSelection(),gloss);
        break;
    case 4:
        test = Noises::sparse_convolution(512, base, conv_amount, contrast, CheckBox2->GetValue());
        break;
    }

    switch(Choice2->GetSelection())
    {
    case 1:
        PTG::Patterns::marble(test, p_scale,n_coef);
        break;
    case 2:
        PTG::Patterns::wood(test, p_scale,n_coef);
        break;
    }

    test.set_image(StaticBitmap1);
}

void ProTeGeFrame::OnButton3Click(wxCommandEvent& event)
{
    int out_size = powf(2,Choice9->GetSelection() + 9);

    greyscale test;

    double d_coef, n_coef, gloss, contrast;
    long p_scale, cell_amount, conv_amount, size;

    TextCtrl1->GetValue().ToDouble(&d_coef);
    TextCtrl2->GetValue().ToLong(&p_scale);
    TextCtrl3->GetValue().ToDouble(&n_coef);
    TextCtrl5->GetValue().ToLong(&cell_amount);
    TextCtrl6->GetValue().ToDouble(&gloss);
    TextCtrl7->GetValue().ToLong(&conv_amount);
    TextCtrl8->GetValue().ToDouble(&contrast);
    TextCtrl9->GetValue().ToLong(&size);

    if(d_coef <= 0 or gloss <= 0 or p_scale <= 0 or cell_amount <= 0 or
       conv_amount <= 0 or size <= 0)
    {
        wxMessageBox(wxT("Wrong input!"));
        return;
    }

    conv_amount *= powf(4,Choice9->GetSelection());

    wxFileDialog openFileDialog(this, _("Save noise file"), "", "",
                       "PNG file|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    switch(Choice7->GetSelection())
    {
    case 0:
        base = Base_figures::star(size, 1.6);
        break;
    case 1:
        base = Base_figures::square(size);
        break;
    case 2:
        base = Base_figures::gaussian(size);
        break;
    case 3:
        break;
    }


    //test = Noises::wavelet(512, 1.2);

    switch(Choice1->GetSelection())
    {
    case 0:
        test = Noises::wavelet(out_size, d_coef);
        break;
    case 1:
        test = Noises::fractal_perlin(out_size, d_coef, Choice3->GetSelection());
        break;
    case 2:
        test = Noises::fractal_white(out_size, d_coef);
        break;
    case 3:
        test = Noises::celluar(out_size,cell_amount,Choice4->GetSelection(),Choice5->GetSelection(),
                               Choice6->GetSelection(),gloss);
        break;
    case 4:
        test = Noises::sparse_convolution(out_size, base, conv_amount, contrast, CheckBox2->GetValue());
        break;
    }

    switch(Choice2->GetSelection())
    {
    case 1:
        PTG::Patterns::marble(test, p_scale,n_coef);
        break;
    case 2:
        PTG::Patterns::wood(test, p_scale,n_coef);
        break;
    }

    wxString f = openFileDialog.GetFilename();

    test.save_to_file(f);

}

void ProTeGeFrame::OnButton2Click(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open image file"), "", "",
                       "PNG file|*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    int size = powf(2, Choice8->GetSelection() + 4);

    greyscale new_base(size);

    base = std::move(new_base);

    wxString f = openFileDialog.GetPath();

    base.load_file(f);
}
