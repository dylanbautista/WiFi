# README #

Aquest repositori conté la següent informació:
* Codi del programa per recollir les observacions de l'RSSI
* Dades recollides als dos experiments realitzats

## A cerca del programa ##

Els arixus que conformen el programa són els següents:
* [Makefile](https://github.com/dylanbautista/WiFi/blob/main/Makefile)
* [master.cc](https://github.com/dylanbautista/WiFi/blob/main/master.cc)
* [obtain_rssi.cc](https://github.com/dylanbautista/WiFi/blob/main/obtain_rssi.cc)

A l'executar el Makefile es compilaran automàticament els codis i s'hi generarà un executable anomenat _master_ que és el que s'ha
d'executar.

El programa llegirà automàticament el valor de l'RSSI i el guardarà, juntament amb la distància, en un arxiu .csv per poder processar
les dades obtingudes posteriorment.

El programa només funcionarà amb ordinadors que funcionim amb el sitema operatiu MacOS (ARM).

## A cerca de les dades ##

S'ha inclòs dos conjunts de dades corresponents als dos experiments realitzats. Juntament amb les dades, hi ha dos arxius de text
que emmagatzemen la informació d'interès dels experiments (l'hora d'inici, l'hora d'acabament, localització...).

Les dades de l'experiment realitzat a la _Plaça de les Constel·lacions_:
* [rssi_pconst.csv](https://github.com/dylanbautista/WiFi/blob/main/rssi_pconst.csv)
* [Info](https://github.com/dylanbautista/WiFi/blob/main/info_exp_pconst.txt)

Les dades de l'exeperiment realitzat al _Pavelló Firal de Tortosa_:
* [rssi_pavello.csv](https://github.com/dylanbautista/WiFi/blob/main/rssi_pavello.csv)
* [Info](https://github.com/dylanbautista/WiFi/blob/main/info_exp_pavello.txt)



