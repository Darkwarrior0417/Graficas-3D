#pragma once

/* Librerías estándar de C++*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream> 

/* Las Third Parties */
#include <SFML/Graphics.hpp>    
#include "Memory\TSharedPointer.h"
#include "Memory\TWeakPointer.h"
#include "Memory\TStaticPtr.h"
#include "Memory\TUniquePtr.h"

// Imgui
#include <imgui.h>
#include <imgui-SFML.h>


/*Enumeración que define los tipos de formas disponibles */
enum
ShapeType {
    EMPTY = 0, /*Forma vacía/no definida*/
    CIRCLE = 1, /* Forma de círculo*/
    RECTANGLE = 2, /* Forma de rectángulo */
    TRIANGLE = 3 /* Forma de triángulo*/
};

enum
ConsolErrorType {
    NORMAL = 0,
    WARNING = 1,
    ERROR = 2
};

/*  Macro para liberar de forma segura punteros */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

/* Macro para generar mensajes en consola al crear recursos */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state <<"] \n";\
    std::cerr << os_.str();                                   \
}

/* Macro para generar mensajes de error en consola y finalizar el programa*/
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error in data from params [" << errorMSG"] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}