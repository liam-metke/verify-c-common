add_executable(read_only_unsat
    read_only_unsat.c)
sea_attach_bc_link(read_only_unsat)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(read_only_unsat)

