#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ProcessClient.h>
#include <unistd.h>
#include <types.h>
#include <Process.h>
#include "renice.h"

renice::renice(int argc, char **argv) : POSIXApplication(argc, argv){
    parser().setDescription("Change the priority of a process");
    parser().registerPositional("PRI", "Priority to change the process to");
    parser().registerPositional("PID", "PID of the process to change");
    parser().registerFlag('n', "setPriority", "Changes process priority to new priority");
}

renice::~renice(){

}

renice::Result renice::exec(){
    //ProcessID pid = atoi(arguments().get("PID"));
    //int prio = atoi(arguments().get("PRI"));
    int prio = atoi(argv[2]);
    ProcessID pid = atoi(argv[3]);

    if (pid <=  0 || pid >= ProcessClient::MaximumProcesses)
    {
        ERROR("Invalid PID: " << pid);
        return InvalidArgument;
    } else if (prio <= 0 || prio > 5){
        ERROR("Invalid priority: " << prio);
        return InvalidArgument;
    } else {
        process.setPriority(prio);
        out << "Priority Changed!!!!!!!!!!\r\n";
    }

    return Success;
}
