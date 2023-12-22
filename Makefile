all: rssi master file

rssi: obtain_rssi.cc
	g++ obtain_rssi.cc -o rssi

master: master.cc
	g++ master.cc -o master

file:
	mkdir -p results

clean:
	rm -f  *.csv
	cd ./results/
	rm -f *.csv