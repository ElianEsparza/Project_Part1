#include "page_table.h"

PageTable::PageTable() : entries(NUM_VIRTUAL_PAGES) {}

PageTableEntry PageTable::getEntry(size_t pageNumber) const {
    if (pageNumber < entries.size())
        return entries[pageNumber];
    return PageTableEntry(); // Return a default (invalid) entry if out of range
}

void PageTable::setEntry(size_t pageNumber, const PageTableEntry& entry) {
    if (pageNumber < entries.size())
        entries[pageNumber] = entry;
}

size_t PageTable::getNumEntries() const {
    return entries.size();
}
