#include <rmtfit.h>

#include <Data.h>
#include <Output.h>
#include <Params.h>
#include <Workboard.h>

void runRmtMaster(char const *inputFileName)
{
  Params par(inputFileName); // Contains parsing logic 
  
  Data data(par.getDataFileNameStub()); // Parses the data files and produces the different digests. 
  
  data.broadcastDigests(); // They are immutable and this reduces the amount of data sent for each RMT sample.

  Output output(par.getRequestedMetrics(), data.getMaximumCharge(), data.getMaximumEigenvalue()); // Set up the output file handles 
  
  Workboard workboard(par.getRequestedMetrics(), par.getRequestedParameters()); /* Maintains a list of all running jobs */
  
  workboard.clearPreviouslyFinishedJobs(&output); /* Remove completed jobs from the list. NOTE Also denote target precision in output, so we can check that too! */
  
  workboard.sendFirstBatch(); /* Just spread out the first jobs over all slaves, don't wait yet. */
  
  while (workboard.jobsRunning())
  {
    Job *job = workboard.retrieveFinishedJob(); /* Wait if nothing is done, will immediately send a new job to the finished slave. */
    job->calculateDigestForData(&data); /* Add the missing analysis part here, as we have all the data required */
    output.fileJob(job); /* Report contains the metadata needed for filing decisions. */
    delete report; /* Non-persistent, created in the retrieveFinishedJob block. */
  }
  
  output.close();
}