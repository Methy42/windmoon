#ifndef EVENT_TARGET_H
#define EVENT_TARGET_H

#include <vector>
#include <thread>
#include <functional>
#include <iostream>

struct EventInterface
{
    const char* event_name;
    std::function<void(void*)> event_callback;
};

struct EventCallbackParam
{
    const char* type;
    const char* message;
    void* data;
};

class EventTarget
{
private:
    std::vector<EventInterface> event_list;
public:
    EventTarget();
    ~EventTarget();

    int addEventListener(const char* event_name, std::function<void(void*)> event_callback);
    int removeEventListener(const char* event_name, int event_index);
    int dispatchEvent(const char* event_name, void* event_data);
};

#endif // EVENT_TARGET_H