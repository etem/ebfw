#include "cdev.h"
#include "net.h"

// FUNCTIONS
static long setEvilUserMode(int mode);
static long setEvilBlockMode(int mode);
static long cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

// VARIABLES
unsigned int evilUserMode = 0;
unsigned int evilBlockMode = 0;
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = cdev_ioctl
};
static struct miscdevice cdev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "ebfw",
    .fops = &fops
};

static long setEvilUserMode(int mode)
{
    evilUserMode = mode;
    return evilUserMode;
}

static long setEvilBlockMode(int mode)
{
    evilBlockMode = mode;
    return evilBlockMode;
}

static long cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case IOCTL_DEUM:
            return setEvilUserMode(OFF);
        case IOCTL_EEUM:
            return setEvilUserMode(ON);
        case IOCTL_GEUM:
            return evilUserMode;
        case IOCTL_DEBM:
            return setEvilBlockMode(OFF);
        case IOCTL_EEBM:
            return setEvilBlockMode(ON);
        case IOCTL_GEBM:
            return evilBlockMode;
        case IOCTL_GBLP:
            return blockedPackets;
    }

    return -1;
}

int registerCdev(void)
{
    int ret;

    ret = misc_register(&cdev);

    return ret;
}

void unregisterCdev(void)
{
    misc_deregister(&cdev);
}