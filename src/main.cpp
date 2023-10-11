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
    unsigned int minimum_size = 1;
    uint64_t chunk_size = 5;

    boost::program_options::options_description desc("Options");
    desc.add_options()
        ("help", "Print this message")
        ("dirs", boost::program_options::value<std::vector<std::string>>()->multitoken()->required(), "List of directories for the scan")
        ("exclude", boost::program_options::value<std::vector<std::string>>()->multitoken(), "List of directories for exclude from the scan")
        ("mask", boost::program_options::value<std::vector<std::string>>()->multitoken(), "List of masks for allowed file names")
        ("recursive", boost::program_options::bool_switch(&is_recursive), "Is recursive scan. Default: false")
        ("minimum-size", boost::program_options::value(&minimum_size), "Minimum size of file for diff. Default: 1 byte")
        ("chunk-size", boost::program_options::value<uint64_t>(&chunk_size), "File reading chink size. Default: 5 bytes");

    boost::program_options::variables_map var_map;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), var_map);

    try
    {
        boost::program_options::notify(var_map);
    }
    catch (const std::exception& e)
    {
        if (var_map.count("help"))
        {
            std::cout << std::endl << desc << std::endl;
            return EXIT_SUCCESS;
        }
        std::cout << e.what() << std::endl << std::endl << desc;
        return EXIT_FAILURE;
    }

    Differ d(var_map.at("dirs").as<std::vector<std::string>>(),
        var_map.at("exclude").as<std::vector<std::string>>(),
        var_map.at("mask").as<std::vector<std::string>>(),
        is_recursive, minimum_size, chunk_size);
    if (!d.Init() || !d.Run())
    {
        std::cout << d.GetErrorString() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
