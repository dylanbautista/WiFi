#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <signal.h>
using namespace std;

int main(int argc, char* argv[]) {                                                                              
    ofstream rssiOutput("./results/rssi.csv",ios::app);

    //MEASURE PROGRAM
    pid_t pids[3];

    int fd[2];
    pipe(fd);

    pids[0] = fork();
    
    switch(pids[0]) {
        case 0: //Is Child
            //pipe1 management
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);

            //Mutate
            execlp("/system/library/privateFrameworks/Apple80211.framework/Versions/A/Resources/airport", "airport", "-I" , NULL);
            perror("Error when exec.");
        case -1:
            perror("Error when fork.");

        default: //Is parent 
            int fd2[2];
            pipe(fd2); //Create pipe2
            pids[1] = fork();
            switch(pids[1]) {
                case -1:
                    perror("Error when fork.");
                    exit(1);
                case 0:
                    //pipe1
                    close(fd[1]);
                    dup2(fd[0],0);
                    close(fd[0]);

                    //For pipe2
                    dup2(fd2[1],1);
                    close(fd2[1]);
                    close(fd2[0]);

                    //Mutate
                    execlp("grep", "grep", "agrCtlRSSI",NULL);
                    perror("error en el exec");
                    exit(1);
                default:
                    close(fd[0]);
                    close(fd[1]);
                    
                    pipe(fd); //Create pipe3

                    pids[2] = fork();
                    switch(pids[2]) {
                        case -1:
                            perror("Error en el fork");
                            exit(1);
                        case 0:
                            //pipe2 managements
                            close(fd2[1]);
                            dup2(fd2[0],0);
                            close(fd2[0]);
                            
                            //pipe3 managements
                            close(fd[0]);
                            dup2(fd[1], 1);
                            close(fd[1]);

                            execlp("awk","awk","-F ", "{print $2}", NULL);
                            exit(0);
                            perror("An error has ocurred with sed exec");
                        default:
                            //pipe2 management
                            close(fd2[0]);
                            close(fd2[1]);
                            //pipe3 management
                            close(fd[1]);

                            waitpid(pids[2], NULL,0);

                            char s[10];
                            read(fd[0], &s, 10);
                            int x = atoi(s);

                            if (x == 0) {
                                exit(2);
                            }
                            else {
                                rssiOutput << x << endl;
                            }   
                    }
            }
    }
    rssiOutput.close();
    exit(0);
}