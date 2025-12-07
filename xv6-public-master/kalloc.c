#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"

#define CPU_CACHE 16

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

struct {
  int count;
  struct run* list[CPU_CACHE];
} cpu_cache[NCPU];

void
kinit1(void *vstart, void *vend)
{
  initlock(&kmem.lock, "kmem");
  freerange(vstart, vend);
}

void
kfree(char *v)
{
  struct run *r;

  if((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
    panic("kfree");

  memset(v, 1, PGSIZE);
  r = (struct run*)v;

  int id = cpuid();
  if(cpu_cache[id].count < CPU_CACHE){
    cpu_cache[id].list[cpu_cache[id].count++] = r;
    return;
  }

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

char*
kalloc(void)
{
  struct run *r;

  int id = cpuid();
  if(cpu_cache[id].count > 0){
    r = cpu_cache[id].list[--cpu_cache[id].count];
    return (char*)r;
  }

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  return (char*)r;
}