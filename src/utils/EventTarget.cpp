#include "utils/EventTarget.h"

EventTarget::EventTarget()
{
    event_list = std::vector<EventInterface>();
}

EventTarget::~EventTarget()
{
    event_list.clear();
}

int EventTarget::addEventListener(const char* event_name, std::function<void(void*)> event_callback)
{
    EventInterface event_interface;
    event_interface.event_name = event_name;
    event_interface.event_callback = event_callback;
    event_list.push_back(event_interface);
    return event_list.size() - 1;
}

int EventTarget::removeEventListener(const char* event_name, int event_index)
{
    event_list.erase(event_list.begin() + event_index);
    return 0;
}

int EventTarget::dispatchEvent(const char* event_name, void* event_data)
{
    for (int i = 0; i < event_list.size(); i++)
    {
        if (strcmp(event_list[i].event_name, event_name) == 0)
        {
            std::thread event_thread(event_list[i].event_callback, event_data);
            event_thread.detach();
        }
    }
    return 0;
}

// Path: src/utils/ServerConnect.cpp