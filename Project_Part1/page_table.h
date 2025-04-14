#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <cstddef>
#include <vector>
#include "vm_config.h"

struct PageTableEntry {
    bool valid;
    size_t frameNumber;
    bool dirty;
    PageTableEntry() : valid(false), frameNumber(0), dirty(false) {}
};

class PageTable {
public:
    PageTable();
    PageTableEntry getEntry(size_t pageNumber) const;
    void setEntry(size_t pageNumber, const PageTableEntry& entry);
    size_t getNumEntries() const;
private:
    std::vector<PageTableEntry> entries;
};

#endif // PAGE_TABLE_H
