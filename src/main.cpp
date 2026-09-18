// KytyPS5-Lite — PlayStation 5 Emulator
// Copyright (c) 2026 KytyPS5-Lite Contributors
// Licensed under GPL-2.0

#include <iostream>
#include <string>
#include "common/log.h"
#include "common/types.h"
#include "cpu/cpu.h"
#include "loader/elf_loader.h"
#include "kernel/kernel.h"
#include "graphics/host_gpu.h"

namespace kyty {

class Emulator {
public:
    Emulator() = default;
    ~Emulator() = default;

    bool Initialize() {
        Log::Info("KytyPS5-Lite v0.0.1");
        Log::Info("Initializing CPU core...");
        if (!cpu_.Initialize()) {
            Log::Error("CPU initialization failed");
            return false;
        }

        Log::Info("Initializing kernel...");
        if (!kernel_.Initialize()) {
            Log::Error("Kernel initialization failed");
            return false;
        }

        Log::Info("Initializing Vulkan backend...");
        if (!gpu_.Initialize()) {
            Log::Error("GPU initialization failed");
            return false;
        }

        Log::Info("Emulator ready");
        return true;
    }

    bool LoadGame(const std::string& eboot_path) {
        Log::Info("Loading game: " + eboot_path);
        
        auto elf = loader_.Load(eboot_path);
        if (!elf) {
            Log::Error("Failed to load ELF/eboot.bin");
            return false;
        }

        Log::Info("Entry point: 0x" + ToHex(elf->entry_point));
        Log::Info("Segments: " + std::to_string(elf->segments.size()));
        
        return cpu_.LoadProgram(*elf);
    }

    void Run() {
        Log::Info("Starting emulation loop...");
        while (running_) {
            cpu_.Step();
            gpu_.Present();
        }
    }

    void Shutdown() {
        Log::Info("Shutting down...");
        gpu_.Shutdown();
        kernel_.Shutdown();
        cpu_.Shutdown();
    }

private:
    CPU cpu_;
    Kernel kernel_;
    HostGPU gpu_;
    ElfLoader loader_;
    bool running_ = true;
};

} // namespace kyty

int main(int argc, char** argv) {
    using namespace kyty;

    if (argc < 2) {
        std::cerr << "Usage: kyty_emulator --game <path-to-eboot.bin>" << std::endl;
        return 1;
    }

    std::string game_path;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--game" && i + 1 < argc) {
            game_path = argv[++i];
        }
    }

    if (game_path.empty()) {
        std::cerr << "Error: no game path specified" << std::endl;
        return 1;
    }

    Emulator emulator;
    if (!emulator.Initialize()) {
        return 1;
    }

    if (!emulator.LoadGame(game_path)) {
        emulator.Shutdown();
        return 1;
    }

    emulator.Run();
    emulator.Shutdown();

    return 0;
}
