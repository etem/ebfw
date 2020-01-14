#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/fs.h>


#define IOCTL_DEUM _IO(10, 1000) // disable evil user mode
#define IOCTL_EEUM _IO(10, 1001) // enable evil user mode
#define IOCTL_GEUM _IO(10, 1002) // get evil user mode
#define IOCTL_DEBM _IO(10, 2000) // disable evil packet blocking
#define IOCTL_EEBM _IO(10, 2001) // enable evil packet blocking
#define IOCTL_GEBM _IO(10, 2002) // get evil block mode
#define IOCTL_GBLP _IO(10, 3000) // get no. of blocked packets
#define OFF 0
#define ON 1

unsigned int getEvilUserMode(void);
unsigned int getEvilBlockMode(void);
int registerCdev(void);
void unregisterCdev(void);

extern unsigned int evilUserMode;
extern unsigned int evilBlockMode;