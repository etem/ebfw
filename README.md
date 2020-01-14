# 💩 ebfw - Evil Bit Firewall

ebfw is a Linux kernel module (LKM) firewall implementing [RFC 3514 - The Security Flag in the IPv4 Header](https://tools.ietf.org/html/rfc3514).

Comes with a Python script that interacts with the built-in character device `/dev/ebfw` to instantly toggle features and pull real-time firewall status.

Tested on Linux kernel version 5.4.0 and 5.3.0.

## Features
ebfw comes with the only three features you should need in a firewall: 

 - **Evil Block Mode** Block ALL incoming packets with the Evil Bit set.
 - **Evil User Mode** Set the Evil Bit on ALL outgoing packets.
 - **Status** List number of blocked packets and whether the modes are ON or OFF,  respectively.

## Usage
**Load the kernel module**

    root@localhost$ make
    root@localhost$ make load
or

    root@localhost$ make
    root@localhost$ insmod ebfw.ko
**Interact with the kernel module**

    root@localhost$ ./client/client.py --help
    usage: client.py [-h] [-U {ON,OFF}] [-B {ON,OFF}] [-S]

    Client interaction with ebfw
    
    optional arguments:
      -h, --help            show this help message and exit
      -U {ON,OFF}, --usermode {ON,OFF}
      -B {ON,OFF}, --blockmode {ON,OFF}
      -S, --status

## Evil Block Mode
Use Evil Block Mode to drop all incoming packets with the Evil Bit set to prevent packets with evil intent on reaching your systems.

**Enable Evil Block Mode**

    ./client.py --blockmode ON

**Disable Evil Block Mode**

    ./client.py --blockmode OFF
  
## Evil User Mode
Use Evil User Mode to flag all outgoing packets as *evil*. 

**Note**: Always enable Evil User Mode if you're attacking other systems over a network. Rather enable Evil User Mode once too much than once too little. 

**Enable Evil User Mode**

    ./client.py --usermode ON
**Disable Evil User Mode**
   

     ./client.py --usermode OFF

## Status

Check whether Evil User Mode or Evil Block Mode is ON or OFF, respectively.
Also shows the number of blocked incoming packets due to the Evil Bit set.

    ./client.py --status

## What is RFC 3514?
> Firewalls, packet filters, intrusion detection systems, and the like
> often have difficulty distinguishing between packets that have
> malicious intent and those that are merely unusual.  We define a
> security flag in the IPv4 header as a means of distinguishing the two
> cases.
## What is the Evil Bit?
The Evil Bit is a flag in the IPv4 header.
Benign packets have this bit set to 0; those that are used for an attack will have the bit set to 1.

The Evil Bit is the most significant bit of the **[Fragment Offset](https://en.wikipedia.org/wiki/IPv4#Fragment_Offset)** field or the **[Flags](https://en.wikipedia.org/wiki/IPv4#Flags)** field (3 MSB's of Fragment Offset) in the IPv4 header.
## Set the Evil Bit
**Little Endian**

    iphdr->frag_off |= 0x80

**Big Endian**

    iphdr->frag_off |= 0x8000
## Get the Evil Bit
**Little Endian**

    eb = iphdr->frag_off & 0x80

**Big Endian**

    eb = iphdr->frag_off & 0x8000

