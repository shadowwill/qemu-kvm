========================================
title: Virtual Machine Dynamic Migration
author: Li Ziyu, Wang Xiaoxi
========================================



#####Experiment environment#####
System: Linux 10.04LTS Desktop i386
VM: qemu-kvm-1.2
Hardware: intel-i5, 4GRAM



#####Complementation#####
1.Innner Qemu source code
Here we mainly modified the memory info and qmp modules
In qemu shell, we add two commands 'dirtyspeed' and 'ramsize'
We modified the following source code to achieve that:
dump.c
hmp.h
monitor.c
hmp.c
vl.c
qmp.c
migration.c
memory.h
memory.c
kvm-all.c
exec-obsolete.h
exec.c
arch_init.c


2.Outter Monitor script
The outter monitor is used to monitor the vm clusters' memory info.
with this info, it can calculte and decide which candidate to migrate.
We write the following scripts which can run as a daemon to achieve the goal.
cmd.txt    --the quemu kvm launch commands
start.sh   --connect the vms with telnet protocal and capture memory dirty speed from the vm
stop.sh    --connect the vms and send command to the vm to stop memory monitoring
migrate.sh --connect the vms and send migration command
test.py    --collect the memory dirtyspeed data and calculate the best candidate
sync.sh    --start the monitor as a daemon.


