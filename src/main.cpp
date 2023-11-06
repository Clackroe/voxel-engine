#include "Game.h"
#include <iostream>
#include <memory>


struct AllocMets {
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrUsage() { return TotalAllocated - TotalFreed; };
};
static AllocMets s_AlocMetrics;

void* operator new(size_t size) {

    // std::cout << "Allocating " << size << std::endl;
    s_AlocMetrics.TotalAllocated += size;

    return malloc(size);

}

void operator delete(void* memory, size_t size) {

    // std::cout << "Freeing " << size << std::endl;
    s_AlocMetrics.TotalFreed += size;

    // std::cout << "Usage " << s_AlocMetrics.CurrUsage() << std::endl;

    free(memory);

}

int main() {

    Game game(1920, 1080, "Very Cool Voxel Game");


    while (game.isRunning()) {
        // std::cout << "Usage " << s_AlocMetrics.CurrUsage() << std::endl;
        game.update();
        game.render();
    }

    std::cout << "Final Usage: " << s_AlocMetrics.CurrUsage() << std::endl;

    return 0;
}