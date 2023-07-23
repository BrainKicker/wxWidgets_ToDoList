#pragma once

#include <includes.h>


class ToDoListApp : public wxApp {
public:

    const static inline std::string APP_NAME = "To-Do List";

    bool OnInit() override;
};