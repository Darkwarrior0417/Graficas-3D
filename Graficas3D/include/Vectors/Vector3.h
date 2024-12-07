#pragma once
#include "MathUtilities.h"

class Vector3
{
public:
    float x; // Valor X del vector
    float y; // Valor Y del vector
    float z; // Valor Z del vector

    /**
      * @brief Constructor por defecto que inicializa  "x", "y" y "z" a 0
      */
    Vector3() : x(0), y(0), z(0) {};

    /**
      * @brief Constructor con parámetros para los valores de "x", "y" y "z"
      */
    Vector3(float xNum, float yNum, float zNum) : x(xNum), y(yNum), z(zNum) {}

    /**
      * @brief Destructor por defecto
      */
    ~Vector3() = default;

    /**
       * @brief Sobrecarga del operador + para sumar un vector a otro vector.
       * @param other El otro vector para sumar.
       */
    Vector3
        operator+(const Vector3& other) const {
        float new_xNum = x + other.x;
        float new_yNum = y + other.y;
        float new_zNum = z + other.z;
        return Vector3(new_xNum, new_yNum, new_zNum);
    }

    /**
       * @brief Sobrecarga del operador - para restar un vector de otro vector.
       * Optimizado realizando operaciones directamente en la declaración de retorno.
       * @param other El otro vector para restar.
       */
    Vector3
        operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /**
       * @brief Sobrecarga del operador * para multiplicar un vector por un escalar.
       * @param scalar El escalar por el cual multiplicar.
       */
    Vector3
        operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /**
      * @brief Calcula la magnitud de los valores del vector
      */
    float
        magnitude() {
        return MUsqrt(x * x + y * y + z * z);
    }

    /**
       * @brief Normaliza el vector, devolviendo un vector con la misma dirección
       */
    Vector3
        normalize() {
        float mag = magnitude();
        // Si la magnitud es 0, se devuelve un vector con coordenadas (0,0,0)
        if (mag == 0) {
            return Vector3(0, 0, 0);
        }
        return Vector3(x / mag, y / mag, z / mag);
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
