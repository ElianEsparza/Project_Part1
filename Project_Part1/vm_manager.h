#ifndef VM_MANAGER_H
#define VM_MANAGER_H

#include <cstddef>
#include <vector>
#include <deque>
#include "page_table.h"
#include "vm_config.h"

class VirtualMemoryManager {
public:
    // Constructor takes a pointer to a process's page table.
    VirtualMemoryManager(PageTable* pt);

    // Translates a virtual address into a physical address.
    // If the page is not valid, a page fault is simulated and handled.
    // Returns true if the translation succeeds, false if the virtual address is out of range.
    bool translateAddress(size_t virtualAddress, size_t& physicalAddress);

private:
    PageTable* pageTable;

    // Simulated physical memory: track usage of each physical frame.
    // 'true' indicates a frame is allocated; 'false' indicates a free frame.
    std::vector<bool> frameUsage;

    // A FIFO queue (deque) of allocated frame indices.
    // Used for page replacement when no free frames remain.
    std::deque<size_t> allocationOrder;

    // Allocates a physical frame.
    // If a free frame exists, allocate that frame; if not, evict the oldest frame (FIFO) and reuse it.
    size_t allocateFrame();
};

#endif // VM_MANAGER_H
