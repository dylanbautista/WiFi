#include <unistd.h>

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "INICI EXPERIMENT" << endl << "Presiona ENTER per obtenir mesures (o 'q' per sortir)" << endl <<
            "-----IMPORTANT🔊🔊🔊------------------------------" << endl 
            << "No tocar l'ordinador mentre s'obtenen les mesures" << endl <<
            "-------------------------------------------------"  << endl;                                                                                     

    //Format files
    ofstream rssiOutput("./results/rssi.csv",ios::trunc);
    rssiOutput << "Distance" << ";" << "RSSI" << endl;
    rssiOutput.close();

    const pid_t parent = getpid(); //Saved super-parent's PID
    int dist = 50;

    //MEASURE PROGRAM
    char c = cin.get();
    while (c != 'q') {
        cout << "=========================================" << endl;
        cout << "DISTANCIA: "  << dist << " cm" << endl <<
        "INICIANT MESURES" << endl <<  "🔴 NO TOCAR ORDINADOR 🔴" << endl;

        int pid;

        rssiOutput = ofstream("./results/rssi.csv",ios::app);
        rssiOutput << dist << ";";
        rssiOutput.close();

        switch(pid = fork()) {
            case 0:

                execlp("./rssi", "rssi", NULL);
                //error
                cout << "ERROR" << endl;
                exit(1);
            case -1:
                exit(1);
            default:
                break;
        }

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 2) { 
                //If rssi program exits with status 2
                cout << "====================⚠️ ====================" << endl;
                cout << "DISTANCIA CRITICA: "  << dist << " cm" << endl <<
                        "EXPERIMENT FINALITZAT" << endl;
                cout << "====================⚠️ ====================" << endl;
                exit(0);
            }
        }

        cout << "MESURA FINALITZATZADA ✅" << endl;
        dist = dist + 50;
        cout << "=========================================" << endl << "Prem ENTER per continuar" << endl;

        c = cin.get();
    }
    if (c == 'q') cout << "Programa finalitzat manualment" << endl;
}