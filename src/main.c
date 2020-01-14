#include "main.h"
#include "net.h"
#include "cdev.h"

static int __init initEbfw(void)
{
    registerCdev();
    initNetModule();

    return 0;
}

static void __exit exitEbfw(void)
{
    cleanupNetModule();
    unregisterCdev();
}

MODULE_DESCRIPTION("LKM FW IMPL. RFC 3514");
MODULE_AUTHOR("ollypwn");
MODULE_LICENSE("GPL");

module_init(initEbfw);
module_exit(exitEbfw);
