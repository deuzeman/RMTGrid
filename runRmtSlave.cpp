#include <rmtfit.h>

void runRmtSlave()
{
  Data data(); // For slave mode, it's just a place to stash the digests
  
  data.receiveDigests(); // Wait for master here, file away for calculation of jackknife results.
  
  RmtEngine engine();
  
  Job *job = Workboard::receiveJob(); // Calls a static function designed for slaves -- no need to further interact. Return 0 on jobs finished.
  
  while (job)
  {
    engine.initialize(job); // Set up the RMT ensemble to fit the job meta data.
    engine.generateEnsemble(); // Generate the RMT data.
    job.parseEnsemble(engine.ensemble()); // Calculate the different chi values and overall results
    Workboard::reportJob(job); // Static function: call the code back.
    delete job;
    job = Workboard::receiveJob(); // Get the next job, receive 0 on jobs finished.
  }
  
  output.close();
}
