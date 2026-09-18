// KytyPS5-Lite — libkernel HLE (High Level Emulation)
// Implements Sony's libkernel PRX stubs

#include "kernel/kernel.h"
#include "common/log.h"

namespace kyty {

// Known libkernel NID stubs
// These are intercepted and handled by the HLE layer

static const std::map<std::string, KernelFunction> kLibKernelFunctions = {
    {"sceKernelAllocateMainDirectMemory", nullptr},
    {"sceKernelAvailableDirectMemorySize", nullptr},
    {"sceKernelGetDirectMemorySize", nullptr},
    {"sceKernelMapDirectMemory", nullptr},
    {"sceKernelMunmap", nullptr},
    {"sceKernelMprotect", nullptr},
    {"sceKernelVirtualQuery", nullptr},
    {"sceKernelGetProcessTime", nullptr},
    {"sceKernelUsleep", nullptr},
    {"sceKernelSleep", nullptr},
};

bool Kernel::Initialize() {
    Log::Info("Kernel: initializing HLE layer");
    // Register all libkernel stubs
    for (const auto& [name, fn] : kLibKernelFunctions) {
        Log::Info("Kernel: registered " + name);
    }
    return true;
}

uint64_t Kernel::HandleSyscall(uint64_t number, uint64_t* args) {
    switch (number) {
        case 0x01: // sceKernelAllocateMainDirectMemory
            return 0;
        case 0x02: // sceKernelAvailableDirectMemorySize
            return 0;
        default:
            Log::Warn("Kernel: unhandled syscall " + std::to_string(number));
            return 0;
    }
}

void Kernel::Shutdown() {
    Log::Info("Kernel: shutdown");
}

} // namespace kyty
