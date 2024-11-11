/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#pragma once
namespace EngineUtilities {
    /**
   * @brief Clase TStaticPtr para manejo de un puntero estatico.
   *
   * La clase TStaticPtr gestiona un unico objeto estatico y proporciona metodos
   * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
   * b?sicas de manejo de memoria.
   */
    template<typename T>
    class TStaticPtr
    {
    public:
        /**
         * @brief Inicializa el puntero est?tico al objeto.
         *
         * Inicializa el puntero est?tico a nullptr.
         */
        TStaticPtr() = default;

        /**
         * @brief Constructor que toma un puntero crudo.
         *
         * @param rawPtr Puntero crudo al objeto que se va a gestionar.
         */
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

        /**
         * @brief Destructor.
         *
         * Libera la memoria del objeto gestionado si es la ?ltima instancia.
         */
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        /**
         * @brief Obtener el puntero crudo.
         *
         * @return Puntero crudo al objeto gestionado.
         */
        static T* get()
        {
            return instance;
        }

        /**
         * @brief Verificar si el puntero es nulo.
         *
         * @return true si el puntero es nulo, false en caso contrario.
         */
        static bool isNull()
        {
            return instance == nullptr;
        }

        /**
         * @brief Reiniciar el puntero est?tico con un nuevo objeto.
         *
         * Libera la memoria del objeto actual (si existe) y toma la propiedad de un nuevo puntero crudo.
         *
         * @param rawPtr Puntero crudo al nuevo objeto que se va a gestionar.
         */
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

    private:
        static T* instance; ///< Puntero est?tico al objeto gestionado.
    };
}