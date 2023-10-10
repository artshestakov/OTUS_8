#include <iostream>
#include "differ.h"
//-----------------------------------------------------------------------------
int main()
{
    Differ d("C:\\Shara\\diff");
    if (!d.Init())
    {
        std::cout << d.GetErrorString() << std::endl;
        return EXIT_FAILURE;
    }

    d.Run();

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
