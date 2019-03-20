//
// Created by daveliinux on 13.3.19.
//

#ifndef PERCEPTON_NEURALNETWORK_H
#define PERCEPTON_NEURALNETWORK_H


#include "NeuronLayer.h"

class NeuralNetwork {
private:
    int _num_inputs;
    NeuronLayer* _hiddenLayer;
    NeuronLayer* _outputLayer;
    double RateLearning = 0.1;
public:
    NeuralNetwork(int num_input,int num_hidden,int num_output,double hiddenLayer_bias = -1,double outputLayer_bias = -1);
    void int_weight_input_hidden();
    void int_weight_hidden_output();

    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &nNN);
    std::vector<double> feed_forward(std::vector<double> inputs);
    void Train(std::vector<double> inputs,std::vector<double> outputs);
    double Calculate_Error(std::vector<double> inputs, std::vector<double> output);
    int MaxIndex(std::vector<double> aMax);
};


#endif //PERCEPTON_NEURALNETWORK_H
