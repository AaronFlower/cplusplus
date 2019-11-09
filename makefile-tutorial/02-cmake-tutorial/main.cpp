#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "todocore/todo.h"
using ToDoCore::ToDo;


int main(
        int     argc,
        char**  argv
)
{
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "display this help")
        ("add,a", po::value< string >(), "add a new entry to the To Do list")
        ;

    bool parseError = false;
    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (po::error& error)
    {
        cerr << "Error: " << error.what() << "\n" << endl;
        parseError = true;
    }

    if (parseError || vm.count("help"))
    {
        cout << "todo: A simple To Do list program" << "\n";
        cout                                        << "\n";
        cout << "Usage:"                            << "\n";
        cout << "   " << argv[0] << " [options]"    << "\n";
        cout                                        << "\n";
        cout << desc                                << "\n";

        if (parseError)
        {
            return 64;
        }
        else
        {
            return 0;
        }
    }

    ToDo list;

    list.addTask("write code");
    list.addTask("compile");
    list.addTask("test");

    if (vm.count("add"))
    {
        list.addTask(vm["add"].as< string >());
    }

    for (size_t i = 0; i < list.size(); ++i)
    {
        cout << list.getTask(i) << "\n";
    }

    return 0;
}
