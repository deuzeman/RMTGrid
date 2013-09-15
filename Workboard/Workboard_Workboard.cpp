#include "Workboard.ih"

Workboard::Workboard(Params const &par)
  : d_db(sqlite3, "rmtgrid.db"),
    d_N(par.N),
    d_samples(par.samples),
    d_max_eig(par.max_eig),
    d_max_charge(par.max_charge)
{
  for (uint64_t charge = 0; charge <= d_max_charge; ++charge)
    for (double sigma = par.sigma_min; sigma <= par.sigma_max; sigma += par.sigma_step)
      for (double mass = par.mass_min; mass <= par.mass_max; mass += par.mass_step)
        for (double a6 = par.a6_min; a6 <= par.a6_max; a6 += par.a6_step)
          for (double a7 = par.a7_min; a7 <= par.a7_max; a7 += par.a7_step)
            for (double a8 = par.a8_min; a8 <= par.a8_max; a8 += par.a8_step)
            {
              d_list.push_back({d_N, charge, sigma, mass, a6, a7, a8, d_samples, d_max_eig});
            }
}
