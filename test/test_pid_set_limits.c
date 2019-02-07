#include "unittest.h"
#include "FastPID.h"

FastPID pid;

int main() {
    pid_new(&pid, 1, 2, 3, 10, 16, true);
    pid_set_limits(&pid, -10000, 10000);

    ASSERT((pid._outmin == (int64_t)(-10000) * PARAM_MULT),
            "_outmin has incorrect value");
    ASSERT((pid._outmax == (int64_t)(10000) * PARAM_MULT),
            "_outmax has incorrect value");

    pid_set_limits(&pid, 10000, -10000);

    ASSERT(pid_err(&pid),
            "pid_set_limits() did not failed as expected");

    return 0;
}
