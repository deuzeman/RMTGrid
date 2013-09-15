#include "Workboard.ih"

void Workboard::clearPreviouslyFinishedJobs()
{
  uint64_t charge;
  double sigma, mass, a6, a7, a8;
  
  soci::statement st = (d_db.prepare << "SELECT charge, sigma, mass, a6, a7, a8"
                                        "  FROM average LEFT JOIN param"
                                        "  WHERE N = " << d_N << 
                                        "  AND samples >= " << d_samples <<
                                        "  AND eigs = " << d_max_eig << 
                                        "  ORDER BY charge, sigma, mass, a6, a7, a8 ASC",
                                          soci::into(eigs), soci::into(sigma), soci::into(mass), 
                                          soci::into(a6), soci::into(a7), soci::into(a8));

  st.execute();
  std::list< Job >::iterator job = d_jobs.begin();
  while (st.fetch())
  {
    // We're going to use the fact that both lists should be sorted!
    while (job->charge < charge)
      ++job;   
    if (job->charge > charge)
      continue;
    
    // NOTE Use an epsilon for these comparisons on floating points!
    while (job->sigma < sigma)
      ++job;   
    if (job->sigma > sigma)
      continue;
    
    while (job->mass < mass)
      ++job;   
    if (job->mass > mass)
      continue;    

    while (job->a6 < a6)
      ++job;   
    if (job->a6 > a6)
      continue; 

    while (job->a7 < a7)
      ++job;   
    if (job->a7 > a7)
      continue; 

    while (job->a8 < a8)
      ++job;   
    if (job->a8 > a8)
      continue;
    
    // If we're here, we found a record containing the right information.
  }
}
