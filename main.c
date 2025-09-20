
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "type.h"
#include "layers/layers.h"
#include "mlp/mlp.h"


float cost(const float* predicted, const float* real, int output_size) {
  float loss = 0.0;
  for(int index = 0; index < output_size; index++) {
    float error = real[index] - predicted[index];
    loss += error*error;
  }

  return loss;
}


int main() {
    srand(time(NULL));

    int neurons_for_each_layers[7] = {16,32,64,128,256,512,256};
    float real[5] = {1,2,3,4,5}; 

    NeuralNetwork mlp = init_neural_network(1,5,neurons_for_each_layers, 6);
    if (mlp.layers == NULL) {
        fprintf(stderr, "Failed to initialize neural network.\n");
        return EXIT_FAILURE;
    }
    float input = 1.0f;
    float *result = forward_network(&mlp, &input);


    printf("Outputs : ");
    if(result){
      for(int result_index = 0; result_index < 5; result_index++) {
        printf("%f ",result[result_index]);
      }
      printf("\n");
    } else {
      fprintf(stderr, "Failed to compute network outputs.\n");
    }
    free_neural_network(&mlp);
    float loss = 0.0f;
    if (result) {
      loss = cost(result, real, 5);
      free(result);
    }
    printf("Loss : %f\n", loss);
    return 0;
}