//
// Created by daveliinux on 13.3.19.
//

#ifndef PERCEPTON_NEURONLAYER_H
#define PERCEPTON_NEURONLAYER_H


#include <vector>
#include <ostream>
#include "Neuron.h"

class NeuronLayer {
private:
    std::vector<Neuron*> _neurons;
    double _bias;
public:
    NeuronLayer(int num_Neurons,double bias = -1);
    std::vector<double> feed_forward(std::vector<double> inputs);

    std::vector<double> get_outputs();
    std::vector<Neuron*> getNeuron();
    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &nLayer);
};


#endif //PERCEPTON_NEURONLAYER_H
