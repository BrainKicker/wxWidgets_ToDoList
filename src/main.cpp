#include <gui/ToDoListApp.h>


wxIMPLEMENT_APP(ToDoListApp);


//int main() {
//
//    std::vector<Task> tasks {
//            Task{ "1", true },
//            Task{ "two", false },
//            Task{ "three four five", false},
//            Task{ "\nбегает\nперевод строки \n бла-бла-бла", true },
//            Task{ "нВ№Ш!8ё61цт8Ёз9увцйIWO U`1ygy\\\\ewq\\ d12", true },
//    };
//
//    Task::saveTasksToFile(tasks, "tasks.txt");
//
//    std::vector<Task> read_tasks = Task::loadTasksFromFile("tasks.txt");
//
//    std::cout << tasks.size() << ' ' << read_tasks.size() << std::endl;
//
//    for (int i = 0; i < tasks.size(); ++i) {
//        std::cout << '\'' << tasks[i].description << "' " << tasks[i].done << "; '" << read_tasks[i].description << "' " << read_tasks[i].done << '\n';
//    }
//}