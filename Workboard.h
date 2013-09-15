#pragma once

#include <list>

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include <Job.h>
#include <Params.h>

class Workboard
{
  static bool      s_master;
  
  soci::session    d_db;
  
  std::list< Job > d_jobs;
  
  uint64_t         d_N;
  uint64_t         d_samples;
  uint64_t         d_max_eig;
  uint64_t         d_max_charge;
  
  public:
    Workboard(Params const &par);
    
    void clearPreviouslyFinishedJobs(&output);
    void sendFirstBatch();
    void retrieveFinishedJob();
    
    static Job *receiveJob();
};
