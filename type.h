#ifndef TYPE_H
#define TYPE_H

typedef struct {
    float* weights;
    float* bias;
    int neuron_number;
    int input_size;
    char act_function[30];
} Layer;

typedef struct {
    Layer* layers;
    int num_layers;
    int output_size;
} NeuralNetwork;

typedef struct {
    int memory_used;
    int num_neurons;
    int num_weights;
} LayerInfo;

float generate_random_float(int min, int max);

#endif