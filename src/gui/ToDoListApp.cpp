#include <gui/ToDoListApp.h>

#include <gui/MainFrame.h>


bool ToDoListApp::OnInit() {
    MainFrame* mainFrame = new MainFrame(APP_NAME);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}