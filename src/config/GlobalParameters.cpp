#include "config/GlobalParameters.h"

GlobalParameters* GlobalParameters::getInstance()
{
    static GlobalParameters instance;
    return &instance;
}

GlobalParameters::GlobalParameters(/* args */)
{
}

GlobalParameters::~GlobalParameters()
{
    std::cout << "GlobalParameters::~GlobalParameters()" << std::endl;
}

GlobalParametersOption GlobalParameters::getOption()
{
    return option;
}

void GlobalParameters::setOption(GlobalParametersOption option)
{
    if (option.window_width > 0)
    {
        this->option.window_width = option.window_width;
    }

    if (option.window_height > 0)
    {
        this->option.window_height = option.window_height;
    }

    if (option.renderer_scaling > 0)
    {
        this->option.renderer_scaling = option.renderer_scaling;
    }
}