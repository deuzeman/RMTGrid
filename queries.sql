// Creation of the tables
"CREATE TABLE IF NOT EXISTS param (param_id INTEGER PRIMARY KEY, sigma REAL, mass REAL, a6 REAL, a7 REAL, a8 REAL),"
"  CONSTRAINT chk_param CHECK (sigma > 0.0 AND mass >= 0.0 AND a6 >= 0.0 AND a7 >= 0.0 AND a8 >= 0.0)"
"CREATE TABLE IF NOT EXISTS average (param_id INTEGER FOREIGN KEY, N INTEGER, charge INTEGER, eigs INTEGER, samples INTEGER, chi_av REAL, sd_chi_av_stat REAL, sd_chi_av_rmt REAL, "
"  CONSTRAINT chk_valid_average CHECK (N > 0 AND AND charge > 0 samples > 0 AND eigs > 0 AND chi_av >= 0.0 AND sd_chi_av_stat >= 0.0 AND sd_chi_av_rmt >= 0.0), "
"  CONSTRAINT chk_unique_average UNIQUE (param_id, N, charge, eigs))"
"CREATE TABLE IF NOT EXISTS quintile (param_id INTEGER FOREIGN KEY, N INTEGER, charge INTEGER, eigs INTEGER, samples INTEGER, chi_qu REAL, sd_chi_qu_stat REAL, sd_chi_qu_rmt REAL, "
"  CONSTRAINT chk_valid_quintile CHECK (N > 0 AND charge > 0 AND samples > 0 AND eigs > 0 AND chi_qu >= 0.0 AND sd_chi_qu_stat >= 0.0 AND sd_chi_qu_rmt >= 0.0), "
"  CONSTRAINT chk_unique_quintile UNIQUE (param_id, N, charge, eigs))"

// Checking existence of parameters
"IF NOT EXISTS (SELECT 1 FROM param WHERE sigma = " << sigma << " AND mass = " << mass << " AND a6 = " << a6 << " AND a7 = " << a7 << " AND a8 = " << a8 << ")"
"  BEGIN"
"    INSERT INTO param (" << sigma << ", " << mass << ", " << a6 << ", " << a7 << ", " << a8 << ")"
"  END"

// Retrieving parameter id
"SELECT param_id FROM param WHERE sigma = " << sigma << " AND mass = " << mass << " AND a6 = " << a6 << " AND a7 = " << a7 << " AND a8 = " << a8, into(param_id);

// Check for existence of sufficiently good results
"SELECT COALESCE(MIN(samples), 0) FROM average WHERE param_id = " << param_id << " AND N = " << N << " AND eigs >= " << eigs, into (samples_on_file_average);
"SELECT COALESCE(MIN(samples), 0) FROM quintile WHERE param_id = " << param_id << " AND N = " << N << " AND eigs >= " << eigs, into (samples_on_file_quintile);

// Insert new results (or replace older ones of apparently worse quality)
"INSERT OR REPLACE INTO average VALUES (" << param_id << ", " << N << ", " << ", " << eigs << ", " << samples << ", " << chi_av << ", " << sd_chi_av_stat << ", " << sd_chi_av_rmt << ")"
"INSERT OR REPLACE INTO quintile VALUES (" << param_id << ", " << N << ", " << ", " << eigs << ", " << samples << ", " << chi_qu << ", " << sd_chi_qu_stat << ", " << sd_chi_qu_rmt << ")"