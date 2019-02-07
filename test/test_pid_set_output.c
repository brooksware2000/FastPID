#include "unittest.h"
#include "FastPID.h"

FastPID pid;

int main() {
    pid_new(&pid, 1, 2, 3, 10, 16, true);
    pid_set_output(&pid, 8, false);

    ASSERT((pid._outmax == (0xFFFFULL >> (16-8)) * PARAM_MULT),
            "_outmax has unexpected value");
    ASSERT((pid._outmin == 0),
            "_outmin has unexpected value");

    pid_set_output(&pid, 32, false);

    ASSERT(pid_err(&pid),
            "pid_set_output() did not failed as expected");

    return 0;
}
