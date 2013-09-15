#pragma once


class Params
{ 
  Params(char const *inputFilename);
}

Params::Params(char const *inputFilename)
{
  boost::program_options::options_description config("Configuration file options");
  
  config.add_options()
}
