#pragma once

#include <random>
#include <vector>

template <typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T> vec)
{
    os << "[ ";
    for (auto const& x : vec)
        os << x << " ";
    os << "]";
    return os;
}

namespace math {
    template <typename T>
    struct Vector : std::vector<T>
    {
        Vector (std::initializer_list<T> xs) : std::vector<T> { xs } {}
        Vector () = default;
    };

    template <typename T>
    Vector<T> operator+(Vector<T>& l, Vector<T>& r)
    {
        Vector<T> y;
        y.resize(l.size());
        for (int i = 0; i < l.size(); i++) y[i] = l[i] + r[i];
        return y;
    }

    template <typename T>
    Vector<T> operator-(Vector<T>& l, Vector<T>& r)
    {
        Vector<T> y;
        y.resize(l.size());
        for (int i = 0; i < l.size(); i++) y[i] = l[i] - r[i];
        return y;
    }

    template <typename T>
    Vector<T> operator*(Vector<T>& l, Vector<T>& r)
    {
        Vector<T> y;
        y.resize(l.size());
        for (int i = 0; i < l.size(); i++) y[i] = l[i] * r[i];
        return y;
    }

    template <typename T>
    Vector<T> vecPow (Vector<T> l, double r)
    {
        Vector<T> y;
        y.resize(l.size());
        for (int i = 0; i < l.size(); i++) y[i] = pow(l[i], r);
        return y;
    }

    template <typename T>
    T Sum (Vector<T> xs)
    {
        double r = 0.0;
        for (int i = 0; i < xs.size(); ++i, r += xs[i]);
        return *reinterpret_cast<T*>(&r);
    }

    template <typename Func>
    double derivative_x(Func f, double x)
    {
        double h = 0.000000001;
        return (f(x+h) - f(x))/h;
    }

    template <typename Func>
    auto derivative(Func f)
    {
        return [=] (double x) {
                   return derivative_x(f, x);
               };
    }

    double random_number (double lower_bound, double upper_bound)
    {
        std::random_device rd;
        std::mt19937 mt { rd() };
        std::uniform_real_distribution<double> random_value { 0.0, 1.0 };
        return random_value(mt);
    }
} // End namespace
