#! /usr/bin/env bash

for ((i=1; i<=1; i++))
do
	echo 'Starting' `pwd`'/event-'${i}
	rm -rf results
	cp -r ../../event-${i} ./results
        nice -n 0 time bash ./HoTCoffeeh.sh false true \
                                include_delta_f=0 include_bulk_pi=1 \
                                CF_npphi=36 CF_npT=15 CF_npY=21 \
                                qtnpts=51 qxnpts=7 qynpts=7 qznpts=7 \
                                delta_qx=0.025 delta_qy=0.025 delta_qz=0.0125 \
                                chosenParticlesMode=0 \
                                CF_resonanceThreshold=0.00 \
                                &> ./all.out
	zip -r results.zip results
	mv results.zip ../../event-${i}
done

echo 'Finished all in' `pwd`
