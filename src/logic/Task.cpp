#include "Task.h"


void Task::saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename) {

    std::ofstream out(filename);

    out << tasks.size();

    for (const Task& task : tasks) {
        out << '\n';
        out << task.description.length() << ' ' << task.description << ' ' << task.done;
    }
}

std::vector<Task> Task::loadTasksFromFile(const std::string& filename) {

    if (!std::filesystem::exists(filename))
        return {};

    std::ifstream in(filename);

    int n;
    in >> n;

    std::vector<Task> tasks;
    tasks.reserve(n);

    for (int i = 0; i < n; ++i) {

        // processing string "{length} <space> {string} <space> bool"

        int length;
        in >> length;

        std::string description(length, '\0');
        // skipping space (spaces) between {length} and {string}
        in.ignore(INT_MAX, ' ');
        in.read(&description[0], length);

        bool done;
        in >> done;

        tasks.emplace_back(std::move(description), done);
    }

    return tasks;
}
