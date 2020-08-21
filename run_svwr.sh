#! /usr/bin/env bash

for ((i=1; i<=125; i++))
do
	echo 'Starting' `pwd`'/event-'${i}
	rm -rf results
	cp -r ../../event-${i} ./results
	nice -n 0 time bash ./HoTCoffeeh.sh true false \
				include_delta_f=0 include_bulk_pi=1 \
				SV_resonanceThreshold=0.00 \
				chosenParticlesMode=0 \
				&> ./all.out
	zip -r results.zip results
	mv results.zip ../../event-${i}
done

echo 'Finished all in' `pwd`
