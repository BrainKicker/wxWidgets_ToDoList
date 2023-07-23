#include <gui/MainFrame.h>

#include <logic/Task.h>


const std::string SAVE_FILE_NAME = "tasks.txt";


MainFrame::MainFrame(const wxString&  title)
        : wxFrame(nullptr, wxID_ANY, title) {
    createControls();
    bindEventHandlers();
    loadTasks();
}


void MainFrame::createControls() {

    static const std::string HEADLINE_TEXT = "To-Do List";
    static const std::string ADD_BUTTON_TEXT = "Add";
    static const std::string CLEAR_BUTTON_TEXT = "Clear";

    wxFont headlineFont(wxFontInfo{{0,36}}.Bold());
    wxFont mainFont(wxFontInfo{{0,24}});

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    headlineText = new wxStaticText(panel, wxID_ANY, HEADLINE_TEXT, {0,22}, {800,-1}, wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headlineFont);
    headlineText->SetSize({800,headlineFont.GetPixelSize().GetY()});

    inputField = new wxTextCtrl(panel, wxID_ANY, "", {100,80}, {495,35}, wxTE_PROCESS_ENTER);
    addButton = new wxButton(panel, wxID_ANY, ADD_BUTTON_TEXT, {600,80}, {100,35});
    checkListBox = new wxCheckListBox(panel, wxID_ANY, {100,120}, {600,400});
    clearButton = new wxButton(panel, wxID_ANY, CLEAR_BUTTON_TEXT, {100,525}, {100,35});
}

void MainFrame::bindEventHandlers() {
    addButton->Bind(wxEVT_BUTTON, &MainFrame::onAddButtonClicked, this);
    inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onInputEnter, this);
    checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onListKeyDown, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::onClearButtonClicked, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onWindowClosed, this);
}

void MainFrame::loadTasks() {

    std::vector<Task> tasks = Task::loadTasksFromFile(SAVE_FILE_NAME);

    for (int i = 0; i < tasks.size(); ++i) {
        checkListBox->Insert(tasks[i].description, i);
        checkListBox->Check(i, tasks[i].done);
    }
}


void MainFrame::onAddButtonClicked(wxCommandEvent& event) {
    addTaskFromInput();
}

void MainFrame::onInputEnter(wxCommandEvent& event) {
    addTaskFromInput();
}

void MainFrame::onListKeyDown(wxKeyEvent& event) {
    switch (event.GetKeyCode()) {
        case WXK_DELETE:
            deleteSelectedTask();
            break;
        case WXK_UP:
            moveSelectedTask(-1);
            break;
        case WXK_DOWN:
            moveSelectedTask(1);
            break;
        default:
            break;
    }
}

void MainFrame::onClearButtonClicked(wxCommandEvent &event) {

    if (checkListBox->IsEmpty())
        return;

    static const std::string CLEAR_BUTTON_DIALOG_MESSAGE = "Are you sure you want to clear all tasks?";
    static const std::string CLEAR_BUTTON_DIALOG_CAPTION = "Clear";

    wxMessageDialog dialog(this, CLEAR_BUTTON_DIALOG_MESSAGE, CLEAR_BUTTON_DIALOG_CAPTION, wxYES_NO | wxCANCEL);
    int result = dialog.ShowModal();

    if (result == wxID_YES)
        checkListBox->Clear();
}

void MainFrame::onWindowClosed(wxCloseEvent &event) {

    std::vector<Task> tasks;
    tasks.reserve(checkListBox->GetCount());

    for (int i = 0; i < checkListBox->GetCount(); ++i)
        tasks.emplace_back(checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i));

    Task::saveTasksToFile(tasks, SAVE_FILE_NAME);

    event.Skip();
}


void MainFrame::addTaskFromInput() {

    wxString description = inputField->GetValue();

    if (!description.IsEmpty()) {
        checkListBox->Append(description);
        inputField->Clear();
    }

    inputField->SetFocus();
}

void MainFrame::deleteSelectedTask() {
    int selectedIndex = checkListBox->GetSelection();
    if (selectedIndex == wxNOT_FOUND)
        return;
    checkListBox->Delete(selectedIndex);
}

void MainFrame::moveSelectedTask(int offset) {

    int selectedIndex = checkListBox->GetSelection();
    if (selectedIndex == wxNOT_FOUND)
        return;

    int newIndex = selectedIndex + offset;
    if (newIndex < 0)
        newIndex = 0;
    if (newIndex >= checkListBox->GetCount())
        newIndex = (int) checkListBox->GetCount() - 1;
    if (newIndex == selectedIndex)
        return;

    // tmp
    wxString selectedString = checkListBox->GetString(selectedIndex);
    bool selectedChecked = checkListBox->IsChecked(selectedIndex);

    // swapping
    checkListBox->SetString(selectedIndex, checkListBox->GetString(newIndex));
    checkListBox->Check(selectedIndex, checkListBox->IsChecked(newIndex));
    checkListBox->SetString(newIndex, selectedString);
    checkListBox->Check(newIndex, selectedChecked);

    checkListBox->SetSelection(newIndex, true);
}