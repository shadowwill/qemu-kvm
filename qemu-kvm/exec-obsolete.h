/*
 * Declarations for obsolete exec.c functions
 *
 * Copyright 2011 Red Hat, Inc. and/or its affiliates
 *
 * Authors:
 *  Avi Kivity <avi@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later.  See the COPYING file in the top-level directory.
 *
 */

/*
 * This header is for use by exec.c and memory.c ONLY.  Do not include it.
 * The functions declared here will be removed soon.
 */

#ifndef EXEC_OBSOLETE_H
#define EXEC_OBSOLETE_H

#ifndef WANT_EXEC_OBSOLETE
#error Do not include exec-obsolete.h
#endif

#ifndef CONFIG_USER_ONLY


#include <stdio.h>    
#include <sys/time.h>      


ram_addr_t qemu_ram_alloc_from_ptr(ram_addr_t size, void *host,
                                   MemoryRegion *mr);
ram_addr_t qemu_ram_alloc(ram_addr_t size, MemoryRegion *mr);
void qemu_ram_free(ram_addr_t addr);
void qemu_ram_free_from_ptr(ram_addr_t addr);

struct MemoryRegion;
struct MemoryRegionSection;
void cpu_register_physical_memory_log(struct MemoryRegionSection *section,
                                      bool readonly);

void qemu_register_coalesced_mmio(target_phys_addr_t addr, ram_addr_t size);
void qemu_unregister_coalesced_mmio(target_phys_addr_t addr, ram_addr_t size);

int cpu_physical_memory_set_dirty_tracking(int enable);

#define VGA_DIRTY_FLAG       0x01
#define CODE_DIRTY_FLAG      0x02
#define MIGRATION_DIRTY_FLAG 0x08

static inline int cpu_physical_memory_get_dirty_flags(ram_addr_t addr)
{
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS];
}

static int track_flag = 0;
static int dirty_amount = 0;
static int dirty_speed = 0;

static inline void set_dirty_track_flag(int flag)
{
	track_flag = flag;
}

static inline int get_dirty_amount()
{
	return dirty_amount;
}

static inline int get_dirtyspeed()
{
	return dirty_speed;
}

static inline reset_dirty_speed()
{
	dirty_speed = 0;
}

/* read dirty bit (return 0 or 1) */
static inline int cpu_physical_memory_is_dirty(ram_addr_t addr)
{
    return cpu_physical_memory_get_dirty_flags(addr) == 0xff;
}

static inline int cpu_physical_memory_get_dirty(ram_addr_t start,
                                                ram_addr_t length,
                                                int dirty_flags)
{
    int ret = 0;
    ram_addr_t addr, end;

    end = TARGET_PAGE_ALIGN(start + length);
    start &= TARGET_PAGE_MASK;
    for (addr = start; addr < end; addr += TARGET_PAGE_SIZE) {
        ret |= cpu_physical_memory_get_dirty_flags(addr) & dirty_flags;
    }
    return ret;
}


static inline int cpu_physical_memory_get_dirty_speed_in(ram_addr_t addr,
                                                      int dirty_flags)
{
    if ((dirty_flags & MIGRATION_DIRTY_FLAG) &&
        !cpu_physical_memory_get_dirty(addr, TARGET_PAGE_SIZE,
                                       MIGRATION_DIRTY_FLAG)) {
		dirty_speed++;
	}
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] |= dirty_flags;
}

static inline long getCurrentTime()    
{    
   struct timeval tv;    
   gettimeofday(&tv,NULL);    
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}  

static inline int cpu_physical_memory_set_dirty_flags(ram_addr_t addr,
                                                      int dirty_flags)
{
    if ((dirty_flags & MIGRATION_DIRTY_FLAG) &&
        !cpu_physical_memory_get_dirty(addr, TARGET_PAGE_SIZE,
                                       MIGRATION_DIRTY_FLAG)) {       
		///////////////////////////////////////////////////
		/*char s[16];
        sprintf(s, "%d\n", addr >> TARGET_PAGE_BITS);
        FILE *fp;
        fp = fopen("address.dat", "a");

        fputs(s, fp);
        fclose(fp);*/
		////////////////////////////////////////////////////
		ram_list.dirty_pages++;
		if(track_flag == 1){
			dirty_amount++;
		}
    }
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] |= dirty_flags;
}

static inline void cpu_physical_memory_set_dirty(ram_addr_t addr)
{
    cpu_physical_memory_set_dirty_flags(addr, 0xff);
}

static inline int cpu_physical_memory_clear_dirty_flags(ram_addr_t addr,
                                                        int dirty_flags)
{
    int mask = ~dirty_flags;

    if ((dirty_flags & MIGRATION_DIRTY_FLAG) &&
        cpu_physical_memory_get_dirty(addr, TARGET_PAGE_SIZE,
                                      MIGRATION_DIRTY_FLAG)) {
        ram_list.dirty_pages--;
    }
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] &= mask;
}


static inline void cpu_physical_memory_get_dirty_speed(ram_addr_t start,
                                                       ram_addr_t length,
                                                       int dirty_flags)
{
    ram_addr_t addr, end;

    end = TARGET_PAGE_ALIGN(start + length);
    start &= TARGET_PAGE_MASK;
    for (addr = start; addr < end; addr += TARGET_PAGE_SIZE) {
        cpu_physical_memory_get_dirty_speed_in(addr, dirty_flags);
    }
}


static inline void cpu_physical_memory_set_dirty_range(ram_addr_t start,
                                                       ram_addr_t length,
                                                       int dirty_flags)
{
    ram_addr_t addr, end;

    end = TARGET_PAGE_ALIGN(start + length);
    start &= TARGET_PAGE_MASK;
    for (addr = start; addr < end; addr += TARGET_PAGE_SIZE) {
        cpu_physical_memory_set_dirty_flags(addr, dirty_flags);
    }
}

static inline void cpu_physical_memory_mask_dirty_range(ram_addr_t start,
                                                        ram_addr_t length,
                                                        int dirty_flags)
{
    ram_addr_t addr, end;

    end = TARGET_PAGE_ALIGN(start + length);
    start &= TARGET_PAGE_MASK;
    for (addr = start; addr < end; addr += TARGET_PAGE_SIZE) {
        cpu_physical_memory_clear_dirty_flags(addr, dirty_flags);
    }
}

void cpu_physical_memory_reset_dirty(ram_addr_t start, ram_addr_t end,
                                     int dirty_flags);

extern const IORangeOps memory_region_iorange_ops;

#endif

#endif
