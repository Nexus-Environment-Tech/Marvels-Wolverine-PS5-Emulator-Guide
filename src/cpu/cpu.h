// KytyPS5-Lite — CPU Emulation
// Based on AMD Zen 2 / RDNA 2 architecture research

#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include "common/types.h"

namespace kyty {

struct CPUContext {
    // General purpose registers (x86-64 / Zen 2)
    uint64_t rax = 0;
    uint64_t rbx = 0;
    uint64_t rcx = 0;
    uint64_t rdx = 0;
    uint64_t rsi = 0;
    uint64_t rdi = 0;
    uint64_t rbp = 0;
    uint64_t rsp = 0;
    uint64_t r8  = 0;
    uint64_t r9  = 0;
    uint64_t r10 = 0;
    uint64_t r11 = 0;
    uint64_t r12 = 0;
    uint64_t r13 = 0;
    uint64_t r14 = 0;
    uint64_t r15 = 0;

    // Instruction pointer
    uint64_t rip = 0;

    // Flags
    uint64_t rflags = 0;

    // Vector registers (AVX2)
    std::array<uint8_t, 32> ymm[16];
};

class CPU {
public:
    CPU();
    ~CPU();

    bool Initialize();
    void Shutdown();

    bool LoadProgram(const ElfInfo& elf);
    void Step();

    CPUContext& context() { return ctx_; }
    const CPUContext& context() const { return ctx_; }

private:
    CPUContext ctx_;
    bool initialized_ = false;

    // Instruction dispatch table
    using OpcodeHandler = void(*)(CPU*, uint8_t*);
    std::array<OpcodeHandler, 256> opcode_table_;
};

} // namespace kyty
