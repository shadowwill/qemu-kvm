========================================
title: Virtual Machine Migration Strategy
author: Li Ziyu, Wang Xiaoxi
========================================



#####Complementation#####
1.Qemu source code modification
1)To track memory dirtying rate and calculate general memory access pattern, we modified the following code files:
arch_init.c
memory.h
memory.c
exec-obsolete.h
exec.c
dump.c
migration.c

2)We also add qemu shell commands 'dirtyspeed' and 'ramsize' to enable easy tracking. We modified the following code files:
hmp.h
monitor.c
hmp.c
qmp.c



2.Migration 
The outter monitor is used to monitor the vm clusters' memory info.
with this info, it can calculte and decide which candidate to migrate.
We write the following scripts which can run as a daemon to achieve the goal.
cmd.txt    --the quemu kvm launch commands
start.sh   --connect the vms with telnet protocal and capture memory dirty speed from the vm
stop.sh    --connect the vms and send command to the vm to stop memory monitoring
migrate.sh --connect the vms and send migration command
test.py    --collect the memory dirtyspeed data and calculate the best candidate
sync.sh    --start the monitor as a daemon.


