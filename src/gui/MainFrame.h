#pragma once

#include <includes.h>


class MainFrame : public wxFrame {
private:
    wxPanel* panel;
    wxStaticText* headlineText;
    wxTextCtrl* inputField;
    wxButton* addButton;
    wxCheckListBox* checkListBox;
    wxButton* clearButton;

public:
    explicit MainFrame(const wxString & title);

private:
    void createControls();
    void bindEventHandlers();
    void loadTasks();

    void onAddButtonClicked(wxCommandEvent& event);
    void onInputEnter(wxCommandEvent& event);
    void onListKeyDown(wxKeyEvent& event);
    void onClearButtonClicked(wxCommandEvent& event);
    void onWindowClosed(wxCloseEvent& event);

    void addTaskFromInput();
    void deleteSelectedTask();
    void moveSelectedTask(int offset);
};