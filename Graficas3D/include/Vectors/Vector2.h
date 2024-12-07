#pragma once
#include "MathUtilities.h"

class
    Vector2 {
public:
    float x; // Valor X del vector
    float y; //  Valor Y del vector

    /**
      * @brief Constructor por defecto que inicializa «x» e «y» a 0
      */
    Vector2() : x(0), y(0) {};

    /**
      * @brief Constructor con parámetros para los valores «x» e «y
      */
    Vector2(float xNum, float yNum) : x(xNum), y(yNum) {}

    /**
      * @brief Destructor por defecto
      */
    ~Vector2() = default;

    

     /**
       * @brief  Sobrecarga del operador +, para añadir un vector a otro vector.
       * @param other El otro vector a añadir.
       */
    Vector2
        operator+(const Vector2& other) const {
        float new_xNum = x + other.x;
        float new_yNum = y + other.y;
        return Vector2(new_xNum, new_yNum);
    }

    /**
       * @brief Sobrecarga del operador -, para restar un vector de otro vector.
       * @param other El otro vector a añadir.
       */
    Vector2
        operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    /**
       * @brief Sobrecarga del operador *, para multiplicar un vector por un escalar.
       * @param scalar El escalar por el que multiplicar.
       */
    Vector2
        operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    /**
       * @brief Sobrecarga del operador /=, para dividir un vector por un escalar.
       * @param scalar El escalar por el que dividir.
       */
    Vector2
        operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    /**
       * @brief Sobrecarga del operador +=, para añadir otro vector a este vector.
       * @param other El vector a añadir.
       */
    Vector2&
        operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
      * @brief Calcula la magnitud de los valores vectoriales
      */
    float
        magnitude() {
        return sqrtNewthon(x * x + y * y);
    }

    /**
       * @brief Normaliza el vector, devolviendo un vector con la misma dirección
       */
    Vector2
        normalize() {
        float mag = magnitude();
        // Si la magnitud es 0, se devuelve un vector con las coordenadas (0,0)
        if (mag == 0) {
            return Vector2(0, 0);
        }
        return Vector2(x / mag, y / mag);
    }

    /**
      * @brief Método que devuelve un puntero a los componentes del vector
      */
    float*
        data() {
        return &x;
    }

    /**
      * @brief Método constante que devuelve un puntero a los componentes del vector sin modificarlos
      */
    const float*
        data() const {
        return &x;
    }

private:

};