#pragma once

#include "./paracefas_math.hpp"

#include <cmath>

namespace paracefas {
    struct Neuron
    {
        using Function = double(*)(double);
        using DataSet  = math::Vector<std::pair<math::Vector<double>, double>>;

        static double ZeroOne (double x) { return x >= 0 ? 1 : 0; }
        static double Sigmoid (double x) { return 1/(1+ exp(-x)); }
    public:
        Neuron (DataSet d) : data { d }
        {
            activation = ZeroOne;
            computeWs();
        }

        Neuron (Function act, double lr, DataSet d) : activation { act }, learning_rate {lr}, data { d }
        {
            computeWs();
        }

        double Compute (math::Vector<double> xs)
        {
            return activation(math::Sum(xs*ws));
        }

        void Update ()
        {
            for (int j = 0; j < data.size(); ++j) {
                auto& [xs, y] = data[j];
                double delta = (y - Compute(xs)) * math::derivative(activation)(math::Sum(xs*ws));
                for (int i = 0; i < ws.size(); ++i)
                    ws[i] += learning_rate * delta * xs[i];
            }
        }

        // The Sum of the Squared Errors (SSE)
        double SSE ()
        {
            math::Vector<double> yhat, ys;
            for (int i = 0; i < data.size(); ++i) {
                auto& [xs, y] = data[i];
                yhat.push_back(Compute(xs));
                ys.push_back(y);
            }
            return 0.5 * Sum(vecPow(ys - yhat,2));
        }

    private:
        DataSet data;
        math::Vector<double> ws;
        Function activation;
        double learning_rate = 0.1;
        std::uniform_real_distribution<double> random_value;
    private:
        void computeWs ()
        {
            size_t size = data[0].first.size();
            if(size == 0) return;
            ws.resize(size);
            for (auto& w : ws)
                w = math::random_number(0.0, 1.0);
        }
    };
} // End namespace.
