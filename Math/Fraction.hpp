#pragma once

#include <utility> // For std::move
#include <cstdlib> // For std::abs

namespace myMathLib {
    template <typename T>
    class Fraction {
    public:
        T numerator; // ����
        T denominator; // ��ĸ

        // ���캯��
        Fraction(const T& numerator, const T& denominator, bool reduce = false)
            : numerator(numerator), denominator(denominator) {
            if (!reduce) this->reduce();
        }

        Fraction(const T& numerator) : numerator(numerator), denominator(1) {}

        // �������캯��
        Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

        // �ƶ����캯��
        Fraction(Fraction&& other) noexcept : numerator(std::move(other.numerator)), denominator(std::move(other.denominator)) {}

        // ������ֵ�����
        Fraction& operator=(const Fraction& other) {
            if (this != &other) {
                numerator = other.numerator;
                denominator = other.denominator;
            }
            return *this;
        }

        // �ƶ���ֵ�����
        Fraction& operator=(Fraction&& other) noexcept {
            if (this != &other) {
                numerator = std::move(other.numerator);
                denominator = std::move(other.denominator);
            }
            return *this;
        }

        // Լ��
        void reduce() {
            if (numerator == 0) {
                denominator = 1;
                return;
            }
            T gcd_value = gcd(std::abs(numerator), std::abs(denominator));
            numerator /= gcd_value;
            denominator /= gcd_value;
        }

        // �ӷ�
        Fraction add(const Fraction& other) const {
            return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
        }

        // ����
        Fraction sub(const Fraction& other) const {
            return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
        }

        // �˷�
        Fraction mul(const Fraction& other) const {
            return Fraction(numerator * other.numerator, denominator * other.denominator);
        }

        // ����
        Fraction div(const Fraction& other) const {
            Fraction temp = other.reciprocal();
            return Fraction(numerator * temp.numerator, denominator * temp.denominator);
        }

        // ����
        Fraction reciprocal() const {
            if (denominator == 0) {
                throw std::runtime_error("����::���� ����Ϊ��\nFraction::reciprocal - denominator is zero");
            }
            return Fraction(denominator, numerator, true);
        }

        //�Ƚ�
        int compare(const Fraction& other) const {
            T commonNumeratorDifference = numerator * other.denominator - other.numerator * denominator;
            bool sameSign = (numerator < 0) == (other.denominator < 0); // 1Ϊ�� 0Ϊ��
            if (commonNumeratorDifference > 0) {
                return sameSign ? 1 : -1; // ���������������ø�
            }
            else if (commonNumeratorDifference < 0) {
                return sameSign ? -1 : 1; // �������������ø�
            }
            else {
                return 0;
            }
        }
        // ���������
        Fraction operator+(const Fraction& other) const {
            return add(other);
        }
        Fraction operator-(const Fraction& other) const {
            return sub(other);
        }
        Fraction operator*(const Fraction& other) const {
            return mul(other);
        }
        Fraction operator/(const Fraction& other) const {
            return div(other);
        }
        Fraction& operator+=(const Fraction& other) const {
            *this = std::move(add(other));
            return *this;
        }
        Fraction& operator-=(const Fraction& other) const {
            *this = std::move(sub(other));
            return *this;
        }
        Fraction& operator*=(const Fraction& other) const {
            *this = std::move(mul(other));
            return *this;
        }
        Fraction& operator/=(const Fraction& other) const {
            *this = std::move(div(other));
            return *this;
        }
        bool operator<(const Fraction& other)const {
            return compare(other) == -1;
        }
        bool operator>(const Fraction& other)const {
            return compare(other) == 1;
        }
        bool operator<=(const Fraction& other)const {
            return compare(other) != 1;
        }
        bool operator>=(const Fraction& other)const {
            return compare(other) != -1;
        }
        bool operator==(const Fraction& other)const {
            return compare(other) == 0;
        }
        bool operator!=(const Fraction& other)const {
            return compare(other) != 0;
        }
    };
}
