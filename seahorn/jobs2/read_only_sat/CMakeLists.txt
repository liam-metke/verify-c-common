add_executable(read_only_sat
    read_only_sat.c)
sea_attach_bc_link(read_only_sat)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(read_only_sat)

