#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<cmath>
#include<iomanip>
#include<vector>
#include<stdio.h>

#include<gsl/gsl_sf_bessel.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_rng.h>            // gsl random number generators
#include <gsl/gsl_randist.h>        // gsl random number distributions
#include <gsl/gsl_vector.h>         // gsl vector and matrix definitions
#include <gsl/gsl_blas.h>           // gsl linear algebra stuff
#include <gsl/gsl_multifit_nlin.h>  // gsl multidimensional fitting

#include "svwr.h"
#include "Arsenal.h"
#include "gauss_quadrature.h"

using namespace std;

void replace_parentheses(std::string & tempstring)
{
	int len = tempstring.length();
	for(unsigned int i = 0; i < len; i++)
	{
		char c = tempstring[i];
		if (c == '(' || c == ')')
			tempstring[i] = '_';
	}
	
	if (tempstring[len - 1] == '_')
		tempstring.erase( len - 1 );
	
	return;
}

void SourceVariances::Output_results()
{
	ostringstream filename_stream_HBT;
	filename_stream_HBT << path << "/HBTradii_SVWR_ev" << no_df_stem << ".dat";
	ofstream outputHBT;
	outputHBT.open(filename_stream_HBT.str().c_str());
	ostringstream filename_stream_HBTcfs;
	filename_stream_HBTcfs << path << "/HBTradii_SVWR_cfs_ev" << no_df_stem << ".dat";
	ofstream outputHBTcoeffs(filename_stream_HBTcfs.str().c_str());
	ostringstream filename_stream_S;
	filename_stream_S << path << "/Sourcefunction_variances_WR" << no_df_stem << ".dat";
	ofstream output_Svars(filename_stream_S.str().c_str());

	for(int iKT = 0; iKT < nKT; iKT++)
	{
		for(int Morder=0; Morder<n_order; Morder++)
		{
			outputHBTcoeffs << K_T[iKT] << "  " << Morder
				<< "  " << R2_side_C[iKT][Morder] << "   " << R2_side_S[iKT][Morder] << "  " << R2_out_C[iKT][Morder] << "  " << R2_out_S[iKT][Morder]
				<< "  " << R2_outside_C[iKT][Morder] << "   " << R2_outside_S[iKT][Morder] << "  " << R2_long_C[iKT][Morder] << "  " << R2_long_S[iKT][Morder]
				<< "  " << R2_sidelong_C[iKT][Morder] << "   " << R2_sidelong_S[iKT][Morder] << "  " << R2_outlong_C[iKT][Morder] << "  " << R2_outlong_S[iKT][Morder] << endl;
		}
		for(int iKphi = 0; iKphi < nKphi; iKphi++)
		{
			outputHBT << K_T[iKT] << "  " << K_phi[iKphi]
				<< "  " << R2_side[iKT][iKphi] << "  " << R2_out[iKT][iKphi]
				<< "  " << R2_outside[iKT][iKphi] << "  " << R2_long[iKT][iKphi]
				<< "  " << R2_sidelong[iKT][iKphi] << "  " << R2_outlong[iKT][iKphi] << endl;
		}
	}
	for(int ipT = 0; ipT < n_pT_pts; ipT++)
	for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
		output_Svars << setprecision(8) << setw(15) 
			<< SP_pT[ipT] << "   " << SP_pphi[ipphi] << "   " << S_func[ipT][ipphi] << "   "
			<< xs_S[ipT][ipphi] << "   " << xo_S[ipT][ipphi] << "   " << xl_S[ipT][ipphi] << "   "
			<< t_S[ipT][ipphi]  << "   " << xs_t_S[ipT][ipphi] << "   "
			<< xo_t_S[ipT][ipphi] << "   " << xl_t_S[ipT][ipphi] << "   "
			<< xo_xs_S[ipT][ipphi] << "   " << xl_xs_S[ipT][ipphi] << "   "
			<< xo_xl_S[ipT][ipphi] << "   " << xs2_S[ipT][ipphi] << "   " << xo2_S[ipT][ipphi] << "   "
			<< xl2_S[ipT][ipphi] << "   " << t2_S[ipT][ipphi] << endl;

	outputHBT.close();
	output_Svars.close();

	return;
}

void SourceVariances::Readin_results()
{
	double dummy;
	ostringstream filename_stream_HBT;
	filename_stream_HBT << path << "/HBTradii_SVWR_ev" << no_df_stem << ".dat";
	ifstream inputHBT(filename_stream_HBT.str().c_str());
	ostringstream filename_stream_S;
	filename_stream_S << path << "/Sourcefunction_variances_WR" << no_df_stem << ".dat";
	ifstream input_Svars(filename_stream_S.str().c_str());

	for(int iKT = 0; iKT < nKT; iKT++)
	{
		for(int iKphi = 0; iKphi < nKphi; iKphi++)
		{
			inputHBT >> dummy;
			inputHBT >> dummy;
			inputHBT >> dummy;
			inputHBT >> R2_side[iKT][iKphi];
			inputHBT >> R2_out[iKT][iKphi];
			inputHBT >> R2_outside[iKT][iKphi];
			inputHBT >> R2_long[iKT][iKphi];
			inputHBT >> R2_sidelong[iKT][iKphi];
			inputHBT >> R2_outlong[iKT][iKphi];
		}
	}
	for(int ipT = 0; ipT < n_pT_pts; ipT++)
	for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
	{
         	input_Svars >> dummy;
        	input_Svars >> dummy;
        	input_Svars >> S_func[ipT][ipphi];
        	input_Svars >> xs_S[ipT][ipphi];
        	input_Svars >> xo_S[ipT][ipphi];
        	input_Svars >> xl_S[ipT][ipphi];
        	input_Svars >> t_S[ipT][ipphi];
        	input_Svars >> xs_t_S[ipT][ipphi];
        	input_Svars >> xo_t_S[ipT][ipphi];
        	input_Svars >> xl_t_S[ipT][ipphi];
        	input_Svars >> xo_xs_S[ipT][ipphi];
        	input_Svars >> xl_xs_S[ipT][ipphi];
        	input_Svars >> xo_xl_S[ipT][ipphi];
        	input_Svars >> xs2_S[ipT][ipphi];
        	input_Svars >> xo2_S[ipT][ipphi];
        	input_Svars >> xl2_S[ipT][ipphi];
        	input_Svars >> t2_S[ipT][ipphi];
	}

	inputHBT.close();
	input_Svars.close();

	return;
}

/*void SourceVariances::Readin_ev_plane_psi()
{
	ostringstream filename_stream_planepsi;
	//filename_stream_planepsi << path << "/plane_psi_ev.dat";
	filename_stream_planepsi << path << "/plane_psi_ev" << no_df_stem << ".dat";
	ifstream inputplanepsi(filename_stream_planepsi.str().c_str());

	inputplanepsi >> global_plane_psi;

	inputplanepsi.close();

	return;
}

void SourceVariances::Output_ev_plane_psi()
{
	ostringstream filename_stream_planepsi;
	//filename_stream_planepsi << path << "/plane_psi_ev.dat";
	filename_stream_planepsi << path << "/plane_psi_ev" << no_df_stem << ".dat";
	ofstream outputplanepsi(filename_stream_planepsi.str().c_str());

	outputplanepsi << global_plane_psi << endl;

	outputplanepsi.close();

	return;
}

void SourceVariances::Output_ev_plane_psis()
{
	ostringstream filename_stream_planepsis;
	//filename_stream_planepsis << path << "/plane_psis_ev.dat";
	filename_stream_planepsis << path << "/plane_psis_ev" << no_df_stem << ".dat";
	ofstream outputplanepsis(filename_stream_planepsis.str().c_str());

	for (int i = 0; i < n_order; i++)
		outputplanepsis << i << "   " << plane_angle[i] << endl;

	outputplanepsis.close();

	return;
}*/

void SourceVariances::Output_dN_dypTdpTdphi()
{
	ostringstream filename_stream_dN_dypTdpTdphi;
	filename_stream_dN_dypTdpTdphi << path << "/dN_dypTdpTdphi_ev" << no_df_stem << ".dat";
	ofstream output_dN_dypTdpTdphi(filename_stream_dN_dypTdpTdphi.str().c_str());

	for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
	for(int ipT = 0; ipT < n_pT_pts; ipT++)
		output_dN_dypTdpTdphi << SP_pT[ipT] << "   " << SP_pphi[ipphi] << "   " << dN_dypTdpTdphi[ipT][ipphi] << endl;

	output_dN_dypTdpTdphi.close();

	return;
}

void SourceVariances::Output_dN_dypTdpT()
{
	ostringstream filename_stream_dN_dypTdpT;
	filename_stream_dN_dypTdpT << path << "/dN_dypTdpT_ev" << no_df_stem << ".dat";
	ofstream output_dN_dypTdpT(filename_stream_dN_dypTdpT.str().c_str());

	for(int ipT = 0; ipT < n_pT_pts; ipT++)
		output_dN_dypTdpT << SP_pT[ipT] << "   " << dN_dypTdpT[ipT] << endl;

	output_dN_dypTdpT.close();

	return;
}

void SourceVariances::Output_all_dN_dypTdpTdphi()
{
	for(int wfi = 0; wfi < n_weighting_functions; wfi++)
	{
		ostringstream filename_stream_all_dN_dypTdpTdphi;
		filename_stream_all_dN_dypTdpTdphi << path << "/all_res_dN_dypTdpTdphi_mom_"
						<< setfill('0') << setw(2) << wfi << "_ev" << no_df_stem << ".dat";
		ofstream output_all_dN_dypTdpTdphi(filename_stream_all_dN_dypTdpTdphi.str().c_str());
		for(int ii = 0; ii < Nparticle; ii++)
		for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
		{
			for(int ipT = 0; ipT < n_pT_pts; ipT++)
				output_all_dN_dypTdpTdphi << scientific << setprecision(8) << setw(12) << dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi] << "   ";
			output_all_dN_dypTdpTdphi << endl;
		}
		output_all_dN_dypTdpTdphi.close();
	}

	return;
}

void SourceVariances::Output_total_target_dN_dypTdpTdphi()
{
	string local_name = all_particles[target_particle_id].name;
	replace_parentheses(local_name);

	for (int wfi = 0; wfi < n_weighting_functions; wfi++)
	{
		ostringstream filename_stream_target_dN_dypTdpTdphi;
		filename_stream_target_dN_dypTdpTdphi << path << "/total_" << local_name << "_dN_dypTdpTdphi_mom_"
								<< setfill('0') << setw(2) << wfi << "_ev" << no_df_stem << ".dat";
		ofstream output_target_dN_dypTdpTdphi(filename_stream_target_dN_dypTdpTdphi.str().c_str());
	
		for (int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
		{
			for (int ipT = 0; ipT < n_pT_pts; ipT++)
				output_target_dN_dypTdpTdphi << scientific << setprecision(8) << setw(12) << dN_dypTdpTdphi_moments[target_particle_id][wfi][ipT][ipphi] << "   ";
			output_target_dN_dypTdpTdphi << endl;
		}
	
		output_target_dN_dypTdpTdphi.close();
	}

	return;
}

void SourceVariances::Output_target_quantities_to_average()
{
	string local_name = all_particles[target_particle_id].name;
	replace_parentheses(local_name);

	ostringstream filename_stream_target_qta;
	filename_stream_target_qta << path << "/total_" << local_name << "_quantities_to_average" << no_df_stem << ".dat";
	ofstream output_target_qta(filename_stream_target_qta.str().c_str());

	for (int iqta = 0; iqta < n_quantities_to_average; iqta++)	
	for (int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
	{
		for (int ipT = 0; ipT < n_pT_pts; ipT++)
			output_target_qta
				<< scientific << setprecision(8) << setw(12)
				<< quantities_to_average[target_particle_id][iqta][ipT][ipphi] << "   ";
		output_target_qta << endl;	
	}

	output_target_qta.close();

	return;
}

void SourceVariances::Output_chosen_resonances()
{
	ostringstream filename_stream_crf;
	filename_stream_crf << path << "/chosen_resonances.dat";
	ofstream output_crf(filename_stream_crf.str().c_str());

	output_crf << particle_monval << endl;
	for (int icr = 0; icr < (int)chosen_resonances.size(); icr++)
		output_crf << all_particles[chosen_resonances[icr]].monval << endl;

	output_crf.close();

	return;
}

void SourceVariances::Read_in_all_dN_dypTdpTdphi()
{
	for(int wfi = 0; wfi < n_weighting_functions; wfi++)
	{
		ostringstream filename_stream_all_dN_dypTdpTdphi;
		filename_stream_all_dN_dypTdpTdphi << path << "/all_res_dN_dypTdpTdphi_mom_"
								<< setfill('0') << setw(2) << wfi << "_ev" << no_df_stem << ".dat";
		ifstream input_all_dN_dypTdpTdphi(filename_stream_all_dN_dypTdpTdphi.str().c_str());
	
		int local_filelength = get_filelength(filename_stream_all_dN_dypTdpTdphi.str().c_str());
		int local_filewidth = get_filewidth(filename_stream_all_dN_dypTdpTdphi.str().c_str());
		if (VERBOSE > 0) *global_out_stream_ptr << "Read_in_all_dN_dypTdpTdphi(): nrows = "
							<< local_filelength << " and ncols = " << local_filewidth << endl;
		if ((Nparticle * n_pphi_pts != local_filelength) || (n_pT_pts != local_filewidth))
		{
			cerr << "Read_in_all_dN_dypTdpTdphi(): Mismatch in dimensions in file "
				<< "all_res_dN_dypTdpTdphi_mom_" << setfill('0') << setw(2) << wfi
				<< "_ev" << no_df_stem << ".dat!" << endl;
			exit(1);
		}
	
		for(int ii = 0; ii < Nparticle; ii++)
		for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
		for(int ipT = 0; ipT < n_pT_pts; ipT++)
		{
			input_all_dN_dypTdpTdphi >> dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi];
			if (abs(dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi]) > 1e-100)
			{
				ln_dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi] = log(abs(dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi]));
				sign_of_dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi] = sgn(dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi]);
			}
			//cout << "Read in (pT, pphi, EdNdp3 ST moms) = " << SP_pT[ipT] << "   " << SP_pphi[ipphi] << "   "
			//	<< scientific << setprecision(8) << setw(12) << dN_dypTdpTdphi_moments[ii][wfi][ipT][ipphi] << endl;
		}
	
		input_all_dN_dypTdpTdphi.close();
		if (VERBOSE > 0) *global_out_stream_ptr << "Successfully read in " << filename_stream_all_dN_dypTdpTdphi.str().c_str() << endl;
	}


	ostringstream filename_stream_pTpts;
	filename_stream_pTpts << path << "/pT_gauss_table.dat";
	ifstream input_pTpts(filename_stream_pTpts.str().c_str());
	ostringstream filename_stream_pphipts;
	filename_stream_pphipts << path << "/phi_gauss_table.dat";
	ifstream input_pphipts(filename_stream_pphipts.str().c_str());

	double * dummy_pT_wts = new double [n_pT_pts];
	double * dummy_pphi_wts = new double [n_pphi_pts];

	for(int ipT = 0; ipT < n_pT_pts; ipT++)
		input_pTpts >> SP_pT[ipT] >> dummy_pT_wts[ipT];

	for(int ipphi = 0; ipphi < n_pphi_pts; ipphi++)
		input_pphipts >> SP_pphi[ipphi] >> dummy_pphi_wts[ipphi];

	if (VERBOSE > 0) *global_out_stream_ptr << "Read_in_all_dN_dypTdpTdphi(): read in pT and pphi points!" << endl;

	input_pTpts.close();
	input_pphipts.close();

	return;
}

//End of file
