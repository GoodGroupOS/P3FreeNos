
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <Process.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for another process to terminate");
    parser().registerPositional("PID", "PID of the process to wait for");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0;
    pid = atoi(arguments().get("PID"));

    if (pid <= 0 || pid >= ProcessClient::MaximumProcesses)
    {
        throw std::invalid_argument("Invalid PID");
    }
    
    // Run wait on the process ID
    if (Waitpid(pid, 0, 0) == -1) {
        ERROR("Failed wait: " << strerror(errno));
        return IOError;
    }
    return Success;
}
