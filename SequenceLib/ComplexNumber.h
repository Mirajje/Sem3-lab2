#ifndef MAIN_CPP_COMPLEXNUMBER_H
#define MAIN_CPP_COMPLEXNUMBER_H

#include "iostream"

class ComplexNumber
{
private:
    double r;
    double im;

public:
    ComplexNumber();
    ComplexNumber(const double& _r, const double& _im);

    const double& getR();
    const double& getIm();

    void setR(const double& _r);
    void setIm(const double& _im);

    ComplexNumber operator *(const ComplexNumber& other) const;

    template <class T> ComplexNumber operator *(T multiplier) const;

    ComplexNumber operator +(const ComplexNumber& other) const;
    ComplexNumber operator -(const ComplexNumber& other) const;
    bool operator ==(const ComplexNumber& other) const;
    bool operator !=(const ComplexNumber& other) const;
    friend std::ostream& operator<<(std::ostream& out, const ComplexNumber& num);
};

template <class T>
ComplexNumber ComplexNumber::operator *(T multiplier) const
{
    return {r * multiplier, im * multiplier};
}


#endif


