add_executable(tracking_before_assignment_no_reset
    tracking_before_assignment_no_reset.c)
sea_attach_bc_link(tracking_before_assignment_no_reset)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(tracking_before_assignment_no_reset)

