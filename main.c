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

typedef struct {
    int memory_used;
    int num_neurons;
    int num_weights;
} LayerInfo;


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
    
    for (int neuron_index = 0; neuron_index < number_of_layer; neuron_index++) {
        mlp.layers[neuron_index] = init_layer(latest_input_size, neuron_for_each_layers[neuron_index], "sigmoid");
        latest_input_size = neuron_for_each_layers[neuron_index];
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

LayerInfo calcul_layer_info(Layer layer) {
    LayerInfo layer_info;
    layer_info.num_neurons = layer.neuron_number;
    layer_info.num_weights = layer_info.num_neurons*layer.input_size;
    layer_info.memory_used = layer_info.num_weights*sizeof(float)+ layer_info.num_neurons * sizeof(float);

    return layer_info;
}

int print_layer_specs(Layer layer) {

    LayerInfo layer_info = calcul_layer_info(layer);

    printf("Number of neurons : %d\n", layer_info.num_neurons);
    printf("Number of weights : %d\n", layer_info.num_weights);
    printf("Memory used for layer : %d\n", layer_info.memory_used);

    return 1;
};

int print_mlp_specs(NeuralNetwork mlp) {
    int number_of_weights = 0;
    int nuumber_of_neurons = 0;
    int memory_used = 0;
    for(int layer_index = 0; layer_index < mlp.num_layers; layer_index++) {

        LayerInfo layer_info = calcul_layer_info(mlp.layers[layer_index]);

        number_of_weights += layer_info.num_weights;
        nuumber_of_neurons += layer_info.num_neurons;
        memory_used += layer_info.memory_used;

    }
    printf("Number of neurons : %d\n", nuumber_of_neurons);
    printf("Number of weights %d\n", number_of_weights);
    printf("Memory used %d\n", memory_used);

    return 1;
}


int main() {
    int neurons_for_each_layers[7] = {16,32,64,128,256,512,256};

    NeuralNetwork mlp = init_neural_network(200,5,neurons_for_each_layers, 6);
    print_mlp_specs(mlp);

    free_neural_network(&mlp);

    return 1;

}