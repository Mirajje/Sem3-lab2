#include "ComplexNumber.h"

ComplexNumber::ComplexNumber()
{
    r = 0;
    im = 0;
}

ComplexNumber::ComplexNumber(const double& _r, const double& _im)
{
    r = _r;
    im = _im;
}

const double& ComplexNumber::getR()
{
    return r;
}

const double& ComplexNumber::getIm()
{
    return im;
}

void ComplexNumber::setR(const double& _r)
{
    r = _r;
}

void ComplexNumber::setIm(const double& _im)
{
    im = _im;
}

ComplexNumber ComplexNumber::operator *(const ComplexNumber& other) const
{
    return {r * other.r - im * other.im, r * other.im + im * other.r};
}

ComplexNumber ComplexNumber::operator +(const ComplexNumber& other) const
{
    return {r + other.r, im + other.im};
}

ComplexNumber ComplexNumber::operator -(const ComplexNumber& other) const
{
    return {r - other.r, im - other.im};
}

bool ComplexNumber::operator ==(const ComplexNumber& other) const
{
    return (r == other.r && im == other.im);
}

bool ComplexNumber::operator !=(const ComplexNumber& other) const
{
    return (!(r == other.r && im == other.im));
}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& num)
{
    out << "(" << num.r << " " << num.im << ")";
    return out;
}