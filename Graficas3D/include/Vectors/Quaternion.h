#pragma once
#include "MathUtilities.h"
#include "Vector3.h"

class Quaternion
{
public:
    float w; // Valor W del Quaternion
    float x; // Valor X del Quaternion
    float y; // Valor Y del Quaternion
    float z; // Valor Z del Quaternion

    /**
      * @brief Constructor por defecto que inicializa "w", "x", "y", y "z" a 0
      */
    Quaternion() : w(0), x(0), y(0), z(0) {};

    /**
      * @brief Constructor con parámetros para los valores de "w", "x", "y", y "z"
      */
    Quaternion(float wNum, float xNum, float yNum, float zNum) :
        w(wNum), x(xNum), y(yNum), z(zNum) {}

    /**
      * @brief Constructor que inicializa el Quaternion desde un ángulo y un eje de rotación.
      * @param angle Ángulo de rotación del Quaternion.
      * @param axis Eje de rotación como un Vector3
      */
    static Quaternion
        fromAxisAngle(const Vector3& axis, float angle) {
        float halfAngle = angle / 2;
        float sinHalfAngle = MUsin(halfAngle);

        float w = MUcos(halfAngle);
        float x = axis.x * sinHalfAngle;
        float y = axis.y * sinHalfAngle;
        float z = axis.z * sinHalfAngle;

        return Quaternion(w, x, y, z);
    }

    /**
       * @brief Sobrecarga del operador + para sumar un Quaternion a otro Quaternion.
       * @param other El otro Quaternion para sumar.
       */
    Quaternion
        operator+(const Quaternion& other) const {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    /**
       * @brief Sobrecarga del operador * para multiplicar un Quaternion por un escalar.
       * @param scalar El escalar por el cual multiplicar.
       */
    Quaternion
        operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y - scalar, z - scalar);
    }

    /**
       * @brief Sobrecarga del operador * para multiplicar un Quaternion por otro Quaternion.
       * @param other El otro Quaternion para multiplicar.
       */
    Quaternion
        operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w);
    }

    /**
      * @brief Calcula la magnitud de los valores del Quaternion
      */
    float
        magnitude() const {
        return MUsqrt(w * w + x * x + y * y + z * z);
    }

    /**
       * @brief Normalización devolviendo un Quaternion normalizado de magnitud 1
       */
    Quaternion
        normalize() {
        float mag = magnitude();
        if (mag == 0) {
            return Quaternion(1, 0, 0, 0);
        }
        return Quaternion(w / mag, x / mag, y / mag, z / mag);
    }

    /**
       * @brief Devuelve el conjugado del Quaternion.
       */
    Quaternion
        conjugate() {
        return Quaternion(w, -x, -y, -z);
    }

    /**
       * @brief Devuelve el inverso del Quaternion.
       */
    Quaternion
        inverse() {
        float qSquared = (1.0f / (w * w + x * x + y * y + z * z));
        return conjugate() * qSquared;
    }


    /**
       * @brief Método Vector3 que usa el Quaternion para rotar un vector v.
       * Convierte el vector en un Quaternion, luego lo normaliza y rota
       * usando q * v * q^-1
       */
    Vector3
        rotate(const Vector3& v) {
        Quaternion vectorQuat(0, v.x, v.y, v.z);

        Quaternion normalizedQuat = this->normalize();

        Quaternion rotatedQuat = normalizedQuat * vectorQuat * normalizedQuat.inverse();

        return Vector3(rotatedQuat.x, rotatedQuat.y, rotatedQuat.z);
    }


    /**
      * @brief Método que devuelve un puntero a los componentes del Quaternion
      */
    float*
        data() {
        return &w;
    }

    /**
      * @brief Método constante que devuelve un puntero a los componentes del Quaternion sin modificarlos
      */
    const float*
        data() const {
        return &w;
    }

private:

};
