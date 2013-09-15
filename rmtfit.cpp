#include <rmtfit.h>

int main(int argc, char **argv)
{
  MPI_Init(argc, argv);
  
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  boost::program_options::options_description cmd_opt("Allowed options");
  
  cmd_opt.add_options()
    ("help", "produce help message")
    ("input", boost::program_options::value< std::string >(), "name for the input file")
    ("database", boost::program_options::value< std::string >(), "name for results database file");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, cmd_opt), vm);
  boost::program_options::notify(vm);
  
  if (vm.count("help"))
  {
    std::cout << cmd_opt << std::endl;
    return 1;
  }
  
  if (rank == 0)
    runRmtMaster(argv[1] /* input file */);
  else
    runRmtSlave();

  MPI_Finalize();
  return 0;
}
