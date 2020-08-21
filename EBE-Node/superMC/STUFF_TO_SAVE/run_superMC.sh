#!/usr/bin/env bash

nohup ./superMC.e which_mc_model=5  sub_model=1  lambda=0.288  et=0  lgx=0  tmax=71  tmax_subdivision=3  alpha=0.14  glb_entropy_width=0.5  aproj=1  atarg=197  proj_deformed=0  targ_deformed=0  include_nn_correlation=1  shape_of_nucleons=2  shape_of_entropy=2  quark_width=0.2  gaussian_lambda=1.27  gauss_nucl_width=0.5  ecm=200  bmin=0  bmax=12.7739  npmin=2  npmax=500  cutdsdy=1  cutdsdy_lowerbound=0.000122956  cutdsdy_upperbound=1e+06  nev=1e+06  randomseed=-1  backup_number=100000  operation=2  finalfactor=28.656  average_from_order=2  average_to_order=3  ecc_from_order=1  ecc_to_order=3  use_sd=1  use_ed=0  use_4col=0  use_block=1  use_5col=0  use_ptcol=0  pt_flag=1  mixedmode=0  pt_min=0.1  pt_max=2  pt_order=2  d_pt=0.1  maxx=13  maxy=13  dx=0.1  dy=0.1  ny=1  ymax=0  cc_fluctuation_model=6  cc_fluctuation_k=0.75  cc_fluctuation_gamma_theta=0.75  output_tatb=0  output_rho_binary=0  output_ta=0  output_rhob=0  generate_reaction_plane_avg_profile=0  model_name=0 &>> superMC.out &

nohup ./run_clean.sh 1 &
nohup ./run_clean.sh 2 &
nohup ./run_clean.sh 3 &
