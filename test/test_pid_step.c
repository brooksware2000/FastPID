#include "unittest.h"
#include "FastPID.h"

FastPID pid;

int main() {
    int16_t output;

    pid_new(&pid, 1, 2, 3, 10, 16, true);

    for (int i=0; i<2; i++)
        output = pid_step(&pid, 100, 50);

    ASSERT((output == 70),
            "unexpected output from pid_step()");

    return 0;
}
