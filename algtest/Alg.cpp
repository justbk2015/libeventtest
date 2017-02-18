#include <stdio.h>
#include "Alg.h"
zb::Log g_log("z0229791", LOG_DEBUG, LOG_FORMAT_ALL, LOG_OUT_CF, "");
void test1()
{
    logd("just a test!\n");
}
int add(int a, int b)
{
    logd("%d + %d = %d", a, b, a+b);
    return a+b;
}