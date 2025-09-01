#ifndef LAYER_H
#define LAYER_H

#include "type.h"

Layer init_layer(int input_size, int size, char act_function[30]);

void free_layer(Layer* layer);

LayerInfo calcul_layer_info(const Layer* layer);

int print_layer_specs(const Layer* layer);

float* forward_layer(const Layer* layer, const float* inputs);

#endif