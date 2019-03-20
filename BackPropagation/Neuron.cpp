//
// Created by daveliinux on 13.3.19.
//

#include <random>
#include "Neuron.h"

Neuron::Neuron(double bias) {

    _bias = bias;

}

Neuron::Neuron() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::normal_distribution<double>  gen(0,1);

    _bias = gen(rng);
}

double Neuron::Activation(double aTotalOutput) {
    return 1.0 / (1.0 +  exp(-aTotalOutput));
}

double Neuron::CalTotalOutput() {
    double lTotal = 0;


    if(_input.size() != _weight.size())
    {
        throw "Input Size have different size than weigth ";
    }

    for(int i=0;i < _input.size();i++)
    {
        lTotal += _input[i] * _weight[i];
    }

    return lTotal + _bias;
}

double Neuron::CalOutput(std::vector<double> aInput) {
    _input = aInput;
    _output = Activation(CalTotalOutput());

    return _output;

}

double Neuron::CalErorr(double targetOutput) {
    return 0.5 * pow((targetOutput - _output),2);
}

double Neuron::Cal_pd_ErrorOutput(double targetOutput) {
    return -(targetOutput - _output);
}

double Neuron::Calculate_pd_output() {
    return _output * (1 - _output);
}

double Neuron::calculate_pd_weight(int index) {
    return  _input[index];
}

double Neuron::calculate_Error_Net(double targetOutput) {
    auto lResult = Cal_pd_ErrorOutput(targetOutput) * Calculate_pd_output();
    return lResult;
}

double Neuron::getOutput() {
    return _output;
}

std::vector<double>& Neuron::getWeight() {
    return _weight;
}

void Neuron::AddWeight(double Weight) {
    _weight.push_back(Weight);
}

double Neuron::getError() {
    return _error;
}

void Neuron::SetError(double Error) {
    _error = Error;
}

void Neuron::UpdateWeight() {

    for (int i = 0; i < _weight.size() ; ++i) {

        _weight[i] += _error * _input[i];
    }

    _bias += _error ;

}

void Neuron::setWeight(int index, double aW) {
    if(_weight.size() > index)
        _weight[index] = aW;
}
