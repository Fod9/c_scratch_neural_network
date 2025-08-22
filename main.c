#include <stdio.h>
#include <stdlib.h>

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
} NeuralNetwork;


Layer init_layer(int input_size, int size, char act_function[30]) {

    Layer layer;

    snprintf(layer.act_function, sizeof(layer.act_function),"%s", act_function);
    
    layer.neuron_number = size;
    layer.input_size = input_size;
    layer.weights = malloc(layer.neuron_number * layer.input_size * sizeof(float));
    layer.bias = malloc(layer.neuron_number * sizeof(float));

    if(layer.weights == NULL) {
        printf("MALLOC ALLOCATION FAILED");
    }


    // Init bias
    for(int i = 0; i < layer.neuron_number; i++) {
        // TODO : Randomize initalization
        layer.bias[i] = i;
    };


    // Init weights
    for(int neuron_index = 0; neuron_index < layer.neuron_number; neuron_index++) {
        for(int input_index = 0; input_index < layer.input_size; input_index++) {
            // TODO : Randomize initialization
            layer.weights[neuron_index * layer.input_size + input_index] =  input_index;
        }
    };

    
    return layer;
};


NeuralNetwork init_neural_network(int input_size, int output_size, int neuron_for_each_layers[], int number_of_layer) {
    NeuralNetwork mlp;
    mlp.num_layers = number_of_layer;
    mlp.layers = malloc(number_of_layer * sizeof(Layer));
    int latest_input_size = input_size;
    
    for(int neuron_index = 0; neuron_index < number_of_layer; neuron_index++) {
        init_layer(latest_input_size, neuron_for_each_layers[neuron_index], "sigmoid");
    }

    return mlp;
}

void free_layer(Layer* layer) {
    if (layer->weights != NULL) {
        free(layer->weights);
        layer->weights = NULL;
    }
}

void free_neural_network(NeuralNetwork* neural_network) {
   if (neural_network->layers != NULL) {
        free(neural_network->layers);
        neural_network->layers = NULL;
    } 
}

int print_layer_specs(Layer layer) {

    printf("Number of neurons : %d\n", layer.neuron_number);
    printf("Number of weights : %d\n", layer.neuron_number * layer.input_size);
    printf("Memory used for layer : %zu\n", layer.neuron_number * layer.input_size * sizeof(float));

    return 1;
};


int main() {
    int neurons_for_each_layers[4] = {1,2,3,5};

    NeuralNetwork mlp = init_neural_network(1,2,neurons_for_each_layers, 4);

    free_neural_network(&mlp);

    return 1;

}