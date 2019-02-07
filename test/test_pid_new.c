#include "unittest.h"
#include "FastPID.h"

FastPID pid;

int main() {
    pid_new(&pid, 1, 2, 3, 10, 16, true);

    ASSERT((pid._p == pid_float_to_param(&pid, 1)),
            "_p term is incorrect");
    ASSERT((pid._i == pid_float_to_param(&pid, (float)2/10)),
            "_i term is incorrect");
    ASSERT((pid._d == pid_float_to_param(&pid, (float)3*10)),
            "_d term is incorrect");

    return 0;
}
