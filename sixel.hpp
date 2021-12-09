#pragma once

#include <iostream>
#include <string>

namespace si
{
    void sixel_on( )
    {
        std::string on = "\x1bPq";
        std::cout << on << std::endl;
    }

    void sixel_off( )
    {
        std::string off = "\x1b\\";
        std::cout << off << std::endl;
    }




}