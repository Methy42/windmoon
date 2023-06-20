#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H

#include <iostream>

struct GlobalParametersOption
{
    int window_width = 800;
    int window_height = 600;
    float renderer_scaling = 1.0f;
};

class GlobalParameters
{
private:
    GlobalParameters(/* args */);
    ~GlobalParameters();
    /* data */
    GlobalParametersOption option;
public:
    GlobalParameters* getInstance();

    // Prohibit copying constructors and copying assignment operators
    GlobalParameters(const GlobalParameters&) = delete;
    GlobalParameters& operator=(const GlobalParameters&) = delete;

    GlobalParametersOption getOption();
    void setOption(GlobalParametersOption option);
};

#endif // GLOBAL_PARAMETERS_H