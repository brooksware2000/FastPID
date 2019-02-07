#include "unittest.h"
#include "FastPID.h"

FastPID pid;

int main() {
    int16_t output;

    pid_new(&pid, 1, 2, 3, 10, 16, true);

    for (int i=0; i<2; i++)
        output = pid_step(&pid, 100, 50);

    ASSERT((pid._last_sp == 100),
            "_last_sp has unexpected value after pid_step()");

    pid_clear(&pid);

    ASSERT((pid._sum == 0),
            "_sum is not zero after calling pid_clear()");
    ASSERT((pid._last_sp == 0),
            "_last_sp is not zero after calling pid_clear()");
    ASSERT((pid._last_err == 0),
            "_last_err is not zero after calling pid_clear()");

    return 0;
}
