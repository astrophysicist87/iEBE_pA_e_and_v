for sys in pp AuAu
do
	for cen in 0_1 0_10 10_20 20_30 30_40 40_50 50_60 60_70 70_80 80_90 90_100
	do
		KT=400MeV
		direc=RESULTS_EA_`echo $sys`_C`echo $cen`_wHBT
		unzip -o $direc/job-1.zip job-1/event-1/Charged_eta_integrated_vndata.dat -d $direc
		unzip -o $direc/job-1.zip job-1/event-1/HBTradii_GF_cfs_no_df.dat -d $direc
		awk 'NR==1 {print $2}' $direc/job-1/event-1/Charged_eta_integrated_vndata.dat >> dNchdeta_`echo $sys`_kt`echo $KT`.dat
		awk '$1==0.4 && $2==0 {print $3, $5, $9}' $direc/job-1/event-1/HBTradii_GF_cfs_no_df.dat >> HBTradii_`echo $sys`_kt`echo $KT`.dat
		KT=450MeV
                awk 'NR==1 {print $2}' $direc/job-1/event-1/Charged_eta_integrated_vndata.dat >> dNchdeta_`echo $sys`_kt`echo $KT`.dat
                awk '$1==0.45 && $2==0 {print $3, $5, $9}' $direc/job-1/event-1/HBTradii_GF_cfs_no_df.dat >> HBTradii_`echo $sys`_kt`echo $KT`.dat
                KT=250MeV
                awk 'NR==1 {print $2}' $direc/job-1/event-1/Charged_eta_integrated_vndata.dat >> dNchdeta_`echo $sys`_kt`echo $KT`.dat
                awk '$1==0.25 && $2==0 {print $3, $5, $9}' $direc/job-1/event-1/HBTradii_GF_cfs_no_df.dat >> HBTradii_`echo $sys`_kt`echo $KT`.dat
	done
        KT=250MeV
        paste dNchdeta_`echo $sys`_kt`echo $KT`.dat HBTradii_`echo $sys`_kt`echo $KT`.dat | tac > HBTradii_vs_dNchdeta_`echo $sys`_kt`echo $KT`.dat
	KT=400MeV
	paste dNchdeta_`echo $sys`_kt`echo $KT`.dat HBTradii_`echo $sys`_kt`echo $KT`.dat | tac > HBTradii_vs_dNchdeta_`echo $sys`_kt`echo $KT`.dat
        KT=450MeV
        paste dNchdeta_`echo $sys`_kt`echo $KT`.dat HBTradii_`echo $sys`_kt`echo $KT`.dat | tac > HBTradii_vs_dNchdeta_`echo $sys`_kt`echo $KT`.dat
done
