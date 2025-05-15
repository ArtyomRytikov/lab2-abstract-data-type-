#include <wx/wx.h>
#include <wx/numdlg.h>
#include <wx/intl.h>
#include "Sequence.h"

class MyApp : public wxApp 
{
public:
    virtual bool OnInit() override;
};

class MainFrame : public wxFrame 
{
public:
    MainFrame(const wxString& title);
    
private:
    Sequence<int>* currentSequence = nullptr;
    bool isArraySequence = true;
    
    void OnCreateSequence(wxCommandEvent& event);
    void OnSequenceOperation(wxCommandEvent& event);
    void ShowSequenceInfo();
    void ClearSequence();
    void ShowError(const wxString& message);
    void ShowInfo(const wxString& message);
    int GetIntegerInput(const wxString& prompt, int min, int max);
};

enum 
{
    ID_CreateArray = 1,
    ID_CreateList,
    ID_FirstElement,
    ID_LastElement,
    ID_GetAtIndex,
    ID_Append,
    ID_Prepend,
    ID_InsertAt,
    ID_Concat,
    ID_Subsequence,
    ID_Length,
    ID_PrintAll,
    ID_Exit
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
    wxLocale* locale = new wxLocale(wxLANGUAGE_RUSSIAN);
    if (locale) 
    {
        locale->AddCatalogLookupPathPrefix(".");
        locale->AddCatalog("sequence_app");
    }
    MainFrame* frame = new MainFrame(wxT("Повелитель последовательностей 52"));
    if (frame) 
    {
        frame->Show(true);
        return true;
    } 
    else 
    {
        return false;
    }
}

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(700, 500)) 
    {
    
    this->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial Unicode MS")));
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);  
    wxStaticBox* mainBox = new wxStaticBox(panel, wxID_ANY, wxT("Главное меню"));
    wxStaticBoxSizer* mainSizer = new wxStaticBoxSizer(mainBox, wxVERTICAL);
    wxButton* btnArray = new wxButton(panel, ID_CreateArray, wxT("Создать ArraySequence"));
    wxButton* btnList = new wxButton(panel, ID_CreateList, wxT("Создать ListSequence"));
    wxButton* btnExit = new wxButton(panel, ID_Exit, wxT("Выход"));
    mainSizer->Add(btnArray, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(btnList, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(btnExit, 0, wxALL | wxEXPAND, 5);
    wxStaticBox* opsBox = new wxStaticBox(panel, wxID_ANY, wxT("Операции с последовательностью"));
    wxStaticBoxSizer* opsSizer = new wxStaticBoxSizer(opsBox, wxVERTICAL);
    wxButton* buttons[] = 
    {
        new wxButton(panel, ID_FirstElement, wxT("1. Получить первый элемент")),
        new wxButton(panel, ID_LastElement, wxT("2. Получить последний элемент")),
        new wxButton(panel, ID_GetAtIndex, wxT("3. Получить элемент по индексу")),
        new wxButton(panel, ID_Append, wxT("4. Добавить в конец")),
        new wxButton(panel, ID_Prepend, wxT("5. Добавить в начало")),
        new wxButton(panel, ID_InsertAt, wxT("6. Вставить по индексу")),
        new wxButton(panel, ID_Concat, wxT("7. Объединить с другой последовательностью")),
        new wxButton(panel, ID_Subsequence, wxT("8. Получить подпоследовательность")),
        new wxButton(panel, ID_Length, wxT("9. Получить длину")),
        new wxButton(panel, ID_PrintAll, wxT("10. Вывести все элементы"))
    };
    for (auto* btn : buttons) 
    {
        opsSizer->Add(btn, 0, wxALL | wxEXPAND, 5);
        btn->Enable(false);
    }
    vbox->Add(mainSizer, 0, wxALL | wxEXPAND, 10);
    vbox->Add(opsSizer, 0, wxALL | wxEXPAND, 10);
    panel->SetSizer(vbox);
    CreateStatusBar();
    SetStatusText(wxT("Последовательность не создана"));
    Bind(wxEVT_BUTTON, &MainFrame::OnCreateSequence, this, ID_CreateArray, ID_CreateList);
    Bind(wxEVT_BUTTON, &MainFrame::OnSequenceOperation, this, ID_FirstElement, ID_PrintAll);
    Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { Close(); }, ID_Exit);
}

void MainFrame::OnCreateSequence(wxCommandEvent& event) 
{
    ClearSequence();
    if (event.GetId() == ID_CreateArray) 
    {
        isArraySequence = true;
    } 
    else 
    {
        isArraySequence = false;
    }
    int size = GetIntegerInput(wxT("Введите размер последовательности:"), 1, 100);
    if (size == -1) return;
    try 
    {
        int* items = new int[size];
        for (int i = 0; i < size; i++) 
        {
            items[i] = GetIntegerInput(wxString::Format(wxT("Элемент %d:"), i+1), INT_MIN, INT_MAX);
            if (items[i] == -1) 
            {
                delete[] items;
                return;
            }
        }
        if (isArraySequence) 
        {
            currentSequence = new MutableArraySequence<int>(items, size);
        } 
        else 
        {
            currentSequence = new MutableListSequence<int>(items, size);
        }
        delete[] items;
        for (int i = ID_FirstElement; i <= ID_PrintAll; i++) 
        {
            FindWindowById(i)->Enable(true);
        }
        ShowSequenceInfo();
        ShowInfo(wxT("Последовательность успешно создана"));
    } 
    catch (const std::exception& e) 
    {
        ShowError(wxString::Format(wxT("Ошибка: %s"), e.what()));
    }
}

void MainFrame::OnSequenceOperation(wxCommandEvent& event) 
{
    if (!currentSequence) return;
    try 
    {
        int id = event.GetId();
        if (id == ID_FirstElement) 
        {
            ShowInfo(wxString::Format(wxT("Первый элемент: %d"), currentSequence->GetFirst()));
        } 
        else if (id == ID_LastElement) 
        {
            ShowInfo(wxString::Format(wxT("Последний элемент: %d"), currentSequence->GetLast()));
        } 
        else if (id == ID_GetAtIndex) 
        {
            int index = GetIntegerInput(wxT("Введите индекс:"), 0, currentSequence->GetLength()-1);
            if (index != -1) 
            {
                ShowInfo(wxString::Format(wxT("Элемент по индексу %d: %d"), index, currentSequence->Get(index)));
            }
        } 
        else if (id == ID_Append) 
        {
            int value = GetIntegerInput(wxT("Введите значение для добавления:"), INT_MIN, INT_MAX);
            if (value != -1) 
            {
                currentSequence = currentSequence->Append(value);
                ShowSequenceInfo();
                ShowInfo(wxT("Элемент успешно добавлен в конец"));
            }
        } 
        else if (id == ID_Prepend) 
        {
            int value = GetIntegerInput(wxT("Введите значение для добавления:"), INT_MIN, INT_MAX);
            if (value != -1) 
            {
                currentSequence = currentSequence->Prepend(value);
                ShowSequenceInfo();
                ShowInfo(wxT("Элемент успешно добавлен в начало"));
            }
        } 
        else if (id == ID_InsertAt) 
        {
            int index = GetIntegerInput(wxT("Введите индекс для вставки:"), 0, currentSequence->GetLength());
            if (index == -1) return;
            int value = GetIntegerInput(wxT("Введите значение для вставки:"), INT_MIN, INT_MAX);
            if (value != -1) 
            {
                currentSequence = currentSequence->InsertAt(value, index);
                ShowSequenceInfo();
                ShowInfo(wxString::Format(wxT("Элемент успешно вставлен по индексу %d"), index));
            }
        } 
        else if (id == ID_Concat) 
        {
            wxMessageBox(wxT("Сначала создайте последовательность для объединения"), 
                        wxT("Объединение"), wxOK | wxICON_INFORMATION, this);
            
            MainFrame* concatFrame = new MainFrame(wxT("Создание последовательности для объединения"));
            concatFrame->Show();
        } 
        else if (id == ID_Subsequence) 
        {
            int start = GetIntegerInput(wxT("Введите начальный индекс:"), 0, currentSequence->GetLength()-1);
            if (start == -1) return;
            int end = GetIntegerInput(wxT("Введите конечный индекс:"), start, currentSequence->GetLength()-1);
            if (end == -1) return;
            Sequence<int>* subseq = currentSequence->GetSubsequence(start, end);
            wxString elements;
            for (int i = 0; i < subseq->GetLength(); i++) 
            {
                elements += wxString::Format(wxT("%d "), subseq->Get(i));
            }
            delete subseq;
            ShowInfo(wxString::Format(wxT("Подпоследовательность [%d-%d]: %s"), start, end, elements));
        } 
        else if (id == ID_Length) 
        {
            ShowInfo(wxString::Format(wxT("Длина последовательности: %d"), currentSequence->GetLength()));
        } 
        else if (id == ID_PrintAll) 
        {
            wxString elements = wxT("Все элементы:\n");
            for (int i = 0; i < currentSequence->GetLength(); i++) 
            {
                elements += wxString::Format(wxT("[%d] = %d\n"), i, currentSequence->Get(i));
            }
            wxMessageDialog dialog(this, elements, wxT("Последовательность"), wxOK | wxICON_INFORMATION);
            dialog.ShowModal();
        }
    } 
    catch (const std::exception& e) 
    {
        ShowError(wxString::Format(wxT("Ошибка: %s"), e.what()));
    }
}

void MainFrame::ShowSequenceInfo() 
{
    wxString type;
    if (isArraySequence) 
    {
        type = wxT("ArraySequence");
    } 
    else 
    {
        type = wxT("ListSequence");
    }
    SetStatusText(wxString::Format(wxT("Текущая последовательность: %s, длина: %d"), type, currentSequence->GetLength()));
}

void MainFrame::ClearSequence() 
{
    if (currentSequence) 
    {
        delete currentSequence;
        currentSequence = nullptr;
    }
    for (int i = ID_FirstElement; i <= ID_PrintAll; i++) 
    {
        FindWindowById(i)->Enable(false);
    }
    SetStatusText(wxT("Последовательность не создана"));
}

void MainFrame::ShowError(const wxString& message) 
{
    wxMessageBox(message, wxT("Ошибка"), wxOK | wxICON_ERROR, this);
}

void MainFrame::ShowInfo(const wxString& message) 
{
    wxMessageBox(message, wxT("Информация"), wxOK | wxICON_INFORMATION, this);
}

int MainFrame::GetIntegerInput(const wxString& prompt, int min, int max) 
{
    long value;
    wxString message = prompt + wxString::Format(wxT("\n(Диапазон: %d - %d)"), min, max);
    value = wxGetNumberFromUser(message, wxT(""), wxT("Ввод числа"), 0, min, max, this);
    if (value == -1) 
    {
        return -1;
    } 
    else 
    {
        return static_cast<int>(value);
    }
}