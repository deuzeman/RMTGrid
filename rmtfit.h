#ifndef GUARD_RMTFIT_H
#define GUARD_RMTFIT_H

#include <iostream>

#include <mpi.h>

#include <boost/program_options.h>

void runRmtMaster(char const *inputFileName);
void runRmtSlave();

#endif
