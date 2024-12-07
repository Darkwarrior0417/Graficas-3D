#pragma once
#include "MathUtilities.h"

class Vector4
{
public:
    float x; // Valor X del vector
    float y; // Valor Y del vector
    float z; // Valor Z del vector
    float w; // Valor W del vector

    /**
      * @brief Constructor por defecto que inicializa "x", "y", "z" y "w" a 0
      */
    Vector4() : x(0), y(0), z(0), w(0) {};

    /**
      * @brief Constructor con parámetros para los valores de "x", "y", "z" y "w"
      */
    Vector4(float xNum, float yNum, float zNum, float wNum) :
        x(xNum), y(yNum), z(zNum), w(wNum) {}

    /**
      * @brief Destructor por defecto
      */
    ~Vector4() = default;

    /**
       * @brief Sobrecarga del operador + para sumar un vector a otro vector.
       * @param other El otro vector para sumar.
       */
    Vector4
        operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    /**
       * @brief Sobrecarga del operador - para restar un vector de otro vector.
       * @param other El otro vector para restar.
       */
    Vector4
        operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w + other.w);
    }

    /**
       * @brief Sobrecarga del operador * para multiplicar un vector por un escalar.
       * @param scalar El escalar por el cual multiplicar.
       */
    Vector4
        operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    /**
      * @brief Calcula la magnitud de los valores del vector
      */
    float
        magnitude() {
        return MUsqrt(x * x + y * y + z * z + w * w);
    }

    /**
       * @brief Normaliza el vector, devolviendo un vector con la misma dirección
       */
    Vector4
        normalize() {
        float mag = magnitude();
        if (mag == 0) {
            return Vector4(0, 0, 0, 0);
        }
        return Vector4(x / mag, y / mag, z / mag, w / mag);
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
