#include "type.h"

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

NeuralNetwork init_neural_network(int input_size, int output_size, int neuron_for_each_layers[], int number_of_layer);

void free_neural_network(NeuralNetwork* neural_network);

int print_mlp_specs(NeuralNetwork mlp);

float* forward_network(const NeuralNetwork* mlp, const float* inputs);

void backward_network(const NeuralNetwork* mlp);

#endif