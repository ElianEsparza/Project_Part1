#ifndef VM_CONFIG_H
#define VM_CONFIG_H

#include <cstddef>

constexpr size_t PAGE_SIZE = 4096;                   // 4KB page size
constexpr size_t VIRTUAL_MEMORY_SIZE = 64 * 1024 * 1024; // 64 MB virtual memory
constexpr size_t PHYSICAL_MEMORY_SIZE = 16 * 1024 * 1024; // 16 MB physical memory

constexpr size_t NUM_VIRTUAL_PAGES = VIRTUAL_MEMORY_SIZE / PAGE_SIZE;
constexpr size_t NUM_PHYSICAL_FRAMES = PHYSICAL_MEMORY_SIZE / PAGE_SIZE;

#endif // VM_CONFIG_H
