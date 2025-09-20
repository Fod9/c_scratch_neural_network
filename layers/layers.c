#include "layers.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


float generate_random_float(int min, int max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}


Layer init_layer(int input_size, int size, const char* act_function) {

    Layer layer = (Layer){0};

    snprintf(layer.act_function, sizeof(layer.act_function), "%s", act_function);

    layer.neuron_number = size;
    layer.input_size = input_size;
    layer.weights = malloc(layer.neuron_number * layer.input_size * sizeof(float));
    if (layer.weights == NULL) {
        fprintf(stderr, "Failed to allocate memory for layer weights.\n");
        layer.neuron_number = 0;
        layer.input_size = 0;
        return layer;
    }
    layer.bias = malloc(layer.neuron_number * sizeof(float));
    if (layer.bias == NULL) {
        fprintf(stderr, "Failed to allocate memory for layer bias.\n");
        free(layer.weights);
        layer.weights = NULL;
        layer.neuron_number = 0;
        layer.input_size = 0;
        return layer;
    }


    // Init bias
    for(int i = 0; i < layer.neuron_number; i++) {
        layer.bias[i] = generate_random_float(-1,1);
    };


    // Init weights
    for(int neuron_index = 0; neuron_index < layer.neuron_number; neuron_index++) {
        for(int input_index = 0; input_index < layer.input_size; input_index++) {
            layer.weights[neuron_index * layer.input_size + input_index] =  generate_random_float(-1,1);
        }
    };


    return layer;
};

void free_layer(Layer* layer) {
    if (layer->weights) {
        free(layer->weights);
        layer->weights = NULL;
    }
    if (layer->bias) {
        free(layer->bias);
        layer->bias = NULL;
    }
}

LayerInfo calcul_layer_info(const Layer* layer) {
    LayerInfo layer_info;
    layer_info.num_neurons = layer->neuron_number;
    layer_info.num_weights = layer_info.num_neurons*layer->input_size;
    layer_info.memory_used = layer_info.num_weights*sizeof(float)+ layer_info.num_neurons * sizeof(float);

    return layer_info;
}

int print_layer_specs(const Layer* layer) {

    LayerInfo layer_info = calcul_layer_info(layer);

    printf("Number of neurons : %d\n", layer_info.num_neurons);
    printf("Number of weights : %d\n", layer_info.num_weights);
    printf("Memory used for layer : %d\n", layer_info.memory_used);

    return 1;
};

float* forward_layer(const Layer* layer, const float* inputs) {
    float* outputs = malloc(layer->neuron_number * sizeof(float));
    if (outputs == NULL) {
        return NULL;
    }
    
    for(int neuron_index = 0; neuron_index < layer->neuron_number; neuron_index++) {
        float sum = layer->bias[neuron_index];
        
        for(int input_index = 0; input_index < layer->input_size; input_index++) {
            sum += inputs[input_index] * layer->weights[neuron_index * layer->input_size + input_index];
        }
        
        // Sigmoid activation
        outputs[neuron_index] = 1.0f / (1.0f + expf(-sum));
    }
    
    return outputs;
}
