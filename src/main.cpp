#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <iterator>
#include "differ.h"
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    bool is_recursive = false;

    boost::program_options::options_description desc("Options");
    desc.add_options()
        ("help,h", "print usage message")
        ("dirs,d", boost::program_options::value<std::vector<std::string>>()->multitoken(), "List of directories for scan")
        ("recursive,r", boost::program_options::bool_switch(&is_recursive), "Is recursive scan");

    boost::program_options::variables_map var_map;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), var_map);
    boost::program_options::notify(var_map);

    if (var_map.count("help"))
    {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }
    else if (!var_map.count("dirs"))
    {
        std::cout << "The parameter 'dirs' is required" << std::endl << std::endl << desc << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<std::string> dir_list = var_map.at("dirs").as<std::vector<std::string>>();

    Differ d(dir_list, is_recursive);
    if (!d.Init())
    {
        std::cout << d.GetErrorString() << std::endl;
        return EXIT_FAILURE;
    }

    d.Run();

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
