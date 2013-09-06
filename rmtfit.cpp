#include <rmtfit.h>

int main(int argc, char **argv)
{
  MPI_Init(argc, argv);
  
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  // Error handling on input
  
  if (rank == 0)
    runRmtMaster(argv[1] /* input file */);
  else
    runRmtSlave();

  MPI_Finalize();
  return 0;
}
