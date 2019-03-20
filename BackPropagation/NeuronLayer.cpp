//
// Created by daveliinux on 13.3.19.
//

#include <random>
#include "NeuronLayer.h"

std::vector<double> NeuronLayer::feed_forward(std::vector<double> inputs) {
    std::vector<double> lOutput;

    for(auto nItem : _neurons)
    {
        lOutput.push_back(nItem->CalOutput(inputs));
    }

    return lOutput;
}

NeuronLayer::NeuronLayer(int num_Neurons, double bias) {
    if(bias =-1)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> gen(0,1);

        _bias = gen(rng);

    }

    for(int i = 0; i < num_Neurons;i++)
    {
        Neuron* lnew = new Neuron(_bias);
        _neurons.push_back(lnew);
    }

}

std::vector<double> NeuronLayer::get_outputs() {
    std::vector<double> outputs;
    for(auto nItem : _neurons)
    {
        outputs.push_back(nItem->getOutput());
    }
    return  outputs;
}

std::ostream &operator<<(std::ostream &os, const NeuronLayer &nLayer) {

    os << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << std::endl;
    os << "Layer" << std::endl;
    os << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << std::endl;
    os << "Num Neurons: " << nLayer._neurons.size();
    os << "═══════════════════════════" << std::endl;
    int i=0;
    for(auto& nItem : nLayer._neurons) {
        os << "    Neuron " << i << std::endl;
        os << "----------------------------" << std::endl;

        auto weight = nItem->getWeight();
        for (int j = 0; j < weight.size() ; ++j) {
         os << "        Weight " << j << " " <<  weight[j] << std::endl;
        }
        os << "Bias " << nLayer._bias << std::endl;
    }
    os << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << std::endl;


    return os;
}

std::vector<Neuron *> NeuronLayer::getNeuron() {
    return _neurons;
}
