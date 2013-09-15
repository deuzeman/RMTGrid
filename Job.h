#pragma once

struct Job
{
  uint64_t N;
  uint64_t nu;
  
  double   Sigma;
  double   m;
  double   a6;
  double   a7;
  double   a8;
  
  uint64_t samples;
  uint64_t max_eig;
};
