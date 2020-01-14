#!/bin/env python3

from fcntl import ioctl
import sys
import argparse

IOCTL_DEUM  = 10 << (4*2) | 1000
IOCTL_EEUM  = 10 << (4*2) | 1001
IOCTL_GEUM  = 10 << (4*2) | 1002
IOCTL_DEBM  = 10 << (4*2) | 2000
IOCTL_EEBM  = 10 << (4*2) | 2001
IOCTL_GEBM  = 10 << (4*2) | 2002
IOCTL_GBLP  = 10 << (4*2) | 3000

ON = 1
OFF = 0

def printUsage():
    print("USAGE: %s [on/off]" % sys.argv[0])

def setEvilUserMode(mode):
    if mode == "ON":
        return ioctl(fd, IOCTL_EEUM)
    elif mode == "OFF":
        return ioctl(fd, IOCTL_DEUM)

    return -1

def setEvilBlockMode(mode):
    if mode == "ON":
        return ioctl(fd, IOCTL_EEBM)
    elif mode == "OFF":
        return ioctl(fd, IOCTL_DEBM)

    return -1

def getEvilUserMode():
    return "\033[92mON\033[0m" if (ioctl(fd, IOCTL_GEUM)) else "\033[91mOFF\033[0m"

def getEvilBlockMode():
    return "\033[92mON\033[0m" if (ioctl(fd, IOCTL_GEBM)) else "\033[91mOFF\033[0m"

def getBlockedPackets():
    return "\033[93m%u\033[0m" % (ioctl(fd, IOCTL_GBLP))

def init():
    global fd

    try:
        fd = open("/dev/ebfw", "wb")
    except:
        print("Failed to open /dev/ebfw")
        exit(0)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Client interaction with ebfw")
    parser.add_argument("-U", "--usermode", choices=["ON","OFF"], dest="usermode", type=str.upper)
    parser.add_argument("-B", "--blockmode", choices=["ON","OFF"], dest="blockmode", type=str.upper)
    parser.add_argument("-S", "--status", action="store_true", default=False)

    args = parser.parse_args()

    init()

    if (args.usermode):
        if (setEvilUserMode(args.usermode) != -1):
            print(f"\033[92m[+] Evil User Mode set to {args.usermode}\033[0m")
        else:
            print(f"\033[91m[-] Failed to set Evil User Mode to {args.usermode}\033[0m")
    if (args.blockmode):
        if (setEvilBlockMode(args.blockmode) != -1):
            print(f"\033[92m[+] Evil User Mode set to {args.blockmode}\033[0m")
        else:
            print(f"\033[91m[-] Failed to set Evil User Mode to {args.blockmode}\033[0m")
    if (args.status):
        eum = getEvilUserMode()
        ebm = getEvilBlockMode()
        blp = getBlockedPackets()
        print(f"\033[34m[*] Evil User Mode\033[0m\t{eum}")
        print(f"\033[34m[*] Evil Block Mode\033[0m\t{ebm}")
        print(f"\033[34m[*] Blocked packets\033[0m\t{blp}")