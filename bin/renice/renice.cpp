#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ProcessClient.h>
#include <unistd.h>
#include <types.h>
#include <Process.h>
#include "renice.h"

renice::renice(int argc, char **argv)
    : POSIXApplication(argc, argv){
    parser().setDescription("Change the priority of a process");
    parser().registerPositional("PRI", "Priority to change the process to");
    parser().registerPositional("PID", "PID of the process to change");
}

renice::~renice(){

}

renice::Result renice::exec(){
    ProcessID pid = atoi(arguments().get("PID"));
    int prio = atoi(arguments().get("PRI"));

    if (pid <=  0 || pid >= ProcessClient::MaximumProcesses)
    {
        ERROR("Invalid PID: " << pid);
        return InvalidArgument;
    }

    if (prio <= 0 || prio > 5){
        ERROR("Invalid priority: " << prio);
        return InvalidArgument;
    }

    return Success;
}
