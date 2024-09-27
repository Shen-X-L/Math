#pragma once

#include <utility> // For std::move
#include <cstdlib> // For std::abs

namespace myMathLib {
    template <typename T>
    class Fraction {
    public:
        T numerator; // 分子
        T denominator; // 分母

        // 构造函数
        Fraction(const T& numerator, const T& denominator, bool reduce = false)
            : numerator(numerator), denominator(denominator) {
            if (!reduce) this->reduce();
        }

        Fraction(const T& numerator) : numerator(numerator), denominator(1) {}

        // 拷贝构造函数
        Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

        // 移动构造函数
        Fraction(Fraction&& other) noexcept : numerator(std::move(other.numerator)), denominator(std::move(other.denominator)) {}

        // 拷贝赋值运算符
        Fraction& operator=(const Fraction& other) {
            if (this != &other) {
                numerator = other.numerator;
                denominator = other.denominator;
            }
            return *this;
        }

        // 移动赋值运算符
        Fraction& operator=(Fraction&& other) noexcept {
            if (this != &other) {
                numerator = std::move(other.numerator);
                denominator = std::move(other.denominator);
            }
            return *this;
        }

        // 约分
        void reduce() {
            if (numerator == 0) {
                denominator = 1;
                return;
            }
            T gcd_value = gcd(std::abs(numerator), std::abs(denominator));
            numerator /= gcd_value;
            denominator /= gcd_value;
        }

        // 加法
        Fraction add(const Fraction& other) const {
            return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
        }

        // 减法
        Fraction sub(const Fraction& other) const {
            return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
        }

        // 乘法
        Fraction mul(const Fraction& other) const {
            return Fraction(numerator * other.numerator, denominator * other.denominator);
        }

        // 除法
        Fraction div(const Fraction& other) const {
            Fraction temp = other.reciprocal();
            return Fraction(numerator * temp.numerator, denominator * temp.denominator);
        }

        // 倒数
        Fraction reciprocal() const {
            if (denominator == 0) {
                throw std::runtime_error("分数::倒数 分子为零\nFraction::reciprocal - denominator is zero");
            }
            return Fraction(denominator, numerator, true);
        }

        //比较
        int compare(const Fraction& other) const {
            T commonNumeratorDifference = numerator * other.denominator - other.numerator * denominator;
            bool sameSign = (numerator < 0) == (other.denominator < 0); // 1为正 0为负
            if (commonNumeratorDifference > 0) {
                return sameSign ? 1 : -1; // 正正得正或正负得负
            }
            else if (commonNumeratorDifference < 0) {
                return sameSign ? -1 : 1; // 负负得正或负正得负
            }
            else {
                return 0;
            }
        }
        // 运算符重载
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
