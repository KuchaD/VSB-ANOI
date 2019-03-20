//
// Created by daveliinux on 13.3.19.
//

#ifndef PERCEPTON_NEURON_H
#define PERCEPTON_NEURON_H


#include "vector"
class Neuron {
private:

    std::vector<double> _weight;
    std::vector<double> _input;
    double _output;
    double _error;

public:
    double getError();
    void SetError(double Error);
    void UpdateWeight();
    double _bias;
    Neuron(double bias);
    Neuron();
    double CalOutput(std::vector<double> aInput);
    double Activation(double aTotalOutput);
    double CalTotalOutput();

    double CalErorr(double targetOutput);
    double Cal_pd_ErrorOutput(double targetOutput);
    double Calculate_pd_output();
    double calculate_pd_weight(int index);
    double calculate_Error_Net(double targetOutput);

    double getOutput();
    void setWeight(int index,double aW);
    std::vector<double>& getWeight();
    void AddWeight(double Weight);
};


#endif //PERCEPTON_NEURON_H
