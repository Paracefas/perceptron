#include <iostream>
#include "./../hdr/paracefas_neuron.hpp"

int main (int argc, char const** argv)
{
    paracefas::Neuron n {
        /* Activation function. */
        paracefas::Neuron::Sigmoid,
        /* Learning rate.       */
        1.0,
        /* Data set.            */
        {/* Bark,  Miaw,  Bite, Scratch,  Dog=0 || Cat=1*/
            { {1,     0,     1,      0},    0 },
            { {1,     0,     1,      1},    0 },
            { {0,     1,     1,      1},    1 }
        }
    };

    for (int i = 0; i < 10000; ++i) {
        std::cout << "Epoch: " << i << '\n';
        std::cout << "SSE: " << n.SSE()  << '\n';
        std::cout << "====================================\n";
        n.Update();
    }
    std::cout << "Expected 0, Computed value: " << n.Compute({1, 0, 1, 0}) << '\n';
    std::cout << "Expected 0, Computed value: " << n.Compute({1, 0, 1, 1}) << '\n';
    std::cout << "Expected 1, Computed value: " << n.Compute({0, 1, 1, 1}) << '\n';
    std::cout << "Expected unknown (1?), Computed value: " << n.Compute({0, 1, 0, 1}) << '\n';
    std::cout << "Expected unknown (0?), Computed value: " << n.Compute({1, 0, 0, 0}) << '\n';
}
