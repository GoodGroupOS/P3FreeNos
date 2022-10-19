#include "renice.h"

int main(int argc, char **argv)
{
    renice app(argc, argv);
    return app.run();
}