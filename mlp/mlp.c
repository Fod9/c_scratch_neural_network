#include "mlp.h"
#include "layers.h"
#include <stdlib.h>
#include <stdio.h>


NeuralNetwork init_neural_network(int input_size, int output_size, int neuron_for_each_layers[], int number_of_layer) {
    NeuralNetwork mlp = (NeuralNetwork){0};

    int hidden_layers = number_of_layer;
    mlp.num_layers = hidden_layers + 1;
    mlp.layers = malloc(mlp.num_layers * sizeof(Layer));
    if (mlp.layers == NULL) {
        fprintf(stderr, "Failed to allocate memory for neural network layers.\n");
        mlp.num_layers = 0;
        return mlp;
    }

    mlp.output_size = output_size;
    int latest_input_size = input_size;

    for (int i = 0; i < hidden_layers; i++) {
        mlp.layers[i] = init_layer(latest_input_size, neuron_for_each_layers[i], "sigmoid");
        if (mlp.layers[i].weights == NULL || mlp.layers[i].bias == NULL) {
            fprintf(stderr, "Failed to initialize hidden layer %d.\n", i);
            for (int j = 0; j < i; ++j) {
                free_layer(&mlp.layers[j]);
            }
            free(mlp.layers);
            mlp.layers = NULL;
            mlp.num_layers = 0;
            mlp.output_size = 0;
            return mlp;
        }
        latest_input_size = neuron_for_each_layers[i];
    }

    mlp.layers[hidden_layers] = init_layer(latest_input_size, output_size, "sigmoid");
    if (mlp.layers[hidden_layers].weights == NULL || mlp.layers[hidden_layers].bias == NULL) {
        fprintf(stderr, "Failed to initialize output layer.\n");
        for (int j = 0; j < hidden_layers; ++j) {
            free_layer(&mlp.layers[j]);
        }
        free(mlp.layers);
        mlp.layers = NULL;
        mlp.num_layers = 0;
        mlp.output_size = 0;
        return mlp;
    }

    return mlp;
}




void free_neural_network(NeuralNetwork* neural_network) {
   if (neural_network->layers) {
        for(int i=0;i<neural_network->num_layers;i++) {
            free_layer(&neural_network->layers[i]);
        }
        free(neural_network->layers);
        neural_network->layers = NULL;
    }
}



int print_mlp_specs(NeuralNetwork mlp) {
    int number_of_weights = 0;
    int number_of_neurons = 0;
    int memory_used = 0;
    for(int layer_index = 0; layer_index < mlp.num_layers; layer_index++) {

        LayerInfo layer_info = calcul_layer_info(&mlp.layers[layer_index]);

        number_of_weights += layer_info.num_weights;
        number_of_neurons += layer_info.num_neurons;
        memory_used += layer_info.memory_used;

    }
    printf("Number of neurons : %d\n", number_of_neurons);
    printf("Number of weights %d\n", number_of_weights);
    printf("Memory used %d\n", memory_used);

    return 1;
}
float* forward_network(const NeuralNetwork* mlp, const float* inputs) {
    if (mlp == NULL || mlp->layers == NULL || mlp->num_layers <= 0) {
        return NULL;
    }
    const float* current_input = inputs;
    float* output = NULL;

    for (int i = 0; i < mlp->num_layers; ++i) {
        output = forward_layer(&mlp->layers[i], current_input);
        if (!output) {
            if (current_input != inputs) {
                free((void*)current_input);
            }
            return NULL;
        }
        if (i > 0) {
            free((void*)current_input);
        }
        current_input = output;
    }
    return output;
}

void backward_network(const NeuralNetwork* mlp) {
    (void)mlp;
}
