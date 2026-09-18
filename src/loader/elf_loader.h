// KytyPS5-Lite — ELF/SELF Loader for PS5 eboot.bin
// PS5 uses a modified ELF format for executables

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "common/types.h"

namespace kyty {

struct ElfSegment {
    uint64_t offset;
    uint64_t virtual_address;
    uint64_t file_size;
    uint64_t memory_size;
    uint32_t flags;
    uint32_t alignment;
};

struct ElfInfo {
    uint64_t entry_point;
    std::vector<ElfSegment> segments;
    std::string title_id;
    std::string version;
    std::vector<uint8_t> raw_data;
};

class ElfLoader {
public:
    ElfLoader() = default;
    ~ElfLoader() = default;

    std::optional<ElfInfo> Load(const std::string& path);

private:
    bool ValidateMagic(const uint8_t* data, size_t size);
    bool ParseSections(const uint8_t* data, size_t size, ElfInfo& info);
};

} // namespace kyty
