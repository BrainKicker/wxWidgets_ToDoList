#pragma once

#include "includes.h"


class Task {
public:

    std::string description;
    bool done;

    explicit Task(std::string description, bool done = false)
    : description(std::move(description)), done(done) {
    }


    /**
     * Saves vector of tasks to file with name ${filename}.
     *
     * The file will look like this after the function execution:
     * """
     * {number of tasks}
     * {length of description} <space> {description} <space> {done}
     * ...
     * """
     *
     * Example:
     * tasks = { {"1", true}, {"bla-bla", false}, {"qwerty qwe", true};
     * file(filename):
     * """
     * 3
     * 1 1 1
     * 7 bla-bla 0
     * 10 qwerty qwe 1
     * """
     */
    static void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename);
    /**
     * Reads the vector of tasks from file with name ${filename},
     * that was previously written bu saveTasksToFile function.
     */
    static std::vector<Task> loadTasksFromFile(const std::string& filename);
};