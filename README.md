========================================
title: Virtual Machine Migration Strategy
author: Li Ziyu
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




