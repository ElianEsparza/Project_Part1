#include "vm_manager.h"

// Constructor: initialize the physical frame usage vector with all frames free.
VirtualMemoryManager::VirtualMemoryManager(PageTable* pt)
    : pageTable(pt), frameUsage(NUM_PHYSICAL_FRAMES, false) {
}

// Allocates a frame by first searching for a free frame; if none, uses FIFO replacement.
size_t VirtualMemoryManager::allocateFrame() {
    // Search for a free frame.
    for (size_t i = 0; i < frameUsage.size(); ++i) {
        if (!frameUsage[i]) {
            frameUsage[i] = true;
            allocationOrder.push_back(i);
            return i;
        }
    }
    // No free frame found; perform FIFO replacement:
    size_t frameToEvict = allocationOrder.front();
    allocationOrder.pop_front();
    // For this simulation, we simply reuse the evicted frame.
    allocationOrder.push_back(frameToEvict);
    return frameToEvict;
}

// Translates a virtual address into a physical address using the process's page table.
// If the page is not valid (simulating a page fault), a frame is allocated and the page table is updated.
bool VirtualMemoryManager::translateAddress(size_t virtualAddress, size_t& physicalAddress) {
    // Compute the virtual page number and offset.
    size_t pageNumber = virtualAddress / PAGE_SIZE;
    size_t offset = virtualAddress % PAGE_SIZE;

    // Check if the virtual address is within the allowed range.
    if (pageNumber >= NUM_VIRTUAL_PAGES)
        return false;

    // Get the page table entry for this virtual page.
    PageTableEntry entry = pageTable->getEntry(pageNumber);

    // If the page is not valid, simulate a page fault: allocate a physical frame and update the page table.
    if (!entry.valid) {
        size_t frame = allocateFrame();
        entry.valid = true;
        entry.frameNumber = frame;
        pageTable->setEntry(pageNumber, entry);
    }

    // Calculate the physical address as (frame number * page size + offset).
    physicalAddress = entry.frameNumber * PAGE_SIZE + offset;
    return true;
}
