# 📦 RabOneEngine - Parser OBJ Personalizado

## 🎯 Descripción General

Este proyecto implementa un **parser OBJ personalizado** para cargar modelos 3D con extensión ".obj".

### ✨ Características Principales

- ✅ **Sin dependencias externas**: Solo STL de C++
- ✅ **Single Header**: `OBJ_Loader.h` (1276 líneas)
- ✅ **Interfaz simple**: Carga en 2 líneas de código
- ✅ **Optimizado**: O(n) en tiempo, O(V) en espacio
- ✅ **Bien documentado**: 3 documentos técnicos completos
- ✅ **DirectX 11 ready**: Conversión automática de coordenadas

---

## 📂 Estructura del Proyecto

```
RabOneEngine/
├── include/
│   ├── ModelLoader.h              ← Interfaz principal (30 líneas)
│   ├── OBJ_Loader.h               ← Parser personalizado (1276 líneas)
│   └── MeshComponent.h            ← Estructura de datos
│
├── src/
│   ├── BaseApp.cpp                ← Ejemplo de uso
│   ├── ModelLoader.cpp            ← Implementación
│   └── ...
│
├── bin/
│   └── models/
│       └── koroGod.obj                ← Modelo de ejemplo
│   └── textures/
│        └── korotexture.png            ← Textura de ejemplo
│ 
└── 📄 README.md                        ← Este archivo
```

---

## 🚀 Uso Rápido

### Carga de Modelo en 3 Líneas

```cpp
#include "ModelLoader.h"

ModelLoader loader;
MeshComponent mesh = loader.LoadOBJModel("models/koroGod.obj");

if (mesh.m_numVertex > 0) {
    printf("✓ Modelo cargado: %d vértices\n", mesh.m_numVertex);
}
```

### Integración con DirectX 11

```cpp
// En BaseApp::init()
koroMesh = m_loader.LoadOBJModel("models/koroGod.obj");

// Crear actor y asignar mesh
std::vector<MeshComponent> meshes;
meshes.push_back(koroMesh);
g_AKoro->SetMesh(g_device, meshes);
```

---

## 📋 Formato OBJ - Resumen

### Elementos Principales

```obj
v   x y z           # Vértice (posición)
vt  u v             # Coordenada UV (textura)
vn  x y z           # Normal (iluminación)
f   v/vt/vn ...     # Cara/Triángulo

# Ejemplo de triángulo completo:
v 0.0 0.0 0.0
v 1.0 0.0 0.0
v 0.5 1.0 0.0

vt 0.0 0.0
vt 1.0 0.0
vt 0.5 1.0

vn 0.0 0.0 1.0
vn 0.0 0.0 1.0
vn 0.0 0.0 1.0

f 1/1/1 2/2/2 3/3/3
```

### Índices en OBJ

⚠️ **IMPORTANTE**: OBJ usa 1-based indexing (comienza desde 1, no 0)

```obj
v 0 0 0    # En OBJ: índice 1 (no 0)
v 1 0 0    # En OBJ: índice 2
v 1 1 0    # En OBJ: índice 3
f 1 2 3    # Usa índices 1, 2, 3

# El parser convierte automáticamente a 0-based (C++ standard)
```

---

## 🏗️ Arquitectura de Capas

```
┌─────────────────────────────────────────┐
│         Código de Usuario               │
│  (BaseApp.cpp - ModelLoader.LoadOBJModel)
├─────────────────────────────────────────┤
│    Capa 1: Interfaz (ModelLoader)       │
│       Interfaz simple de alto nivel     │
├─────────────────────────────────────────┤
│    Capa 2: Parser (objl::Loader)        │
│    Lectura y parseo de archivo OBJ      │
├─────────────────────────────────────────┤
│    Capa 3: Utilidades                   │
│   Math (vectores) + Algoritmos (strings)│
├─────────────────────────────────────────┤
│    Capa 4: Estructuras de Datos         │
│  Vector2, Vector3, Vertex, Mesh, etc.   │
├─────────────────────────────────────────┤
│         STL + DirectX 11                │
└─────────────────────────────────────────┘
```

---

## 📊 Complejidad Computacional

### Tiempo
```
Operación               Complejidad    Ejemplo (100K vértices)
────────────────────────────────────────────────────────────
LoadFile()              O(n)           100-500 ms
Parseado completo       O(n·m)         Típico: 1-10 ms (simple)
────────────────────────────────────────────────────────────
```

### Espacio
```
Estructura          Bytes/Elemento      Ejemplo (100K vértices)
────────────────────────────────────────────────────────────
SimpleVertex        20 bytes            ~2 MB
Índices             4 bytes             ~400 KB
Total estimado      ~2.4 MB
────────────────────────────────────────────────────────────
```

---

## ⚙️ Características Técnicas

- ✅ Parseo de vértices (v)
- ✅ Coordenadas UV (vt)
- ✅ Normales (vn)
- ✅ Caras/Triángulos (f)
- ✅ Inversión automática de UV (DirectX compatibility)
- ✅ Triangulación automática (polígonos n-lados → triángulos)
- ✅ Generación automática de índices
- ✅ Soporte para materiales (referencia)
- ✅ Manejo de errores
- ✅ Console output en modo debug

---

## 🔧 Decisiones de Implementación

### 1. Inversión Automática de Coordenada V

```cpp
vVert.TextureCoordinate.Y = 1.0f - vVert.TextureCoordinate.Y;
```

**Por qué**:
- OBJ/OpenGL: V=0 en abajo
- DirectX: V=0 en arriba
- Esto asegura que las texturas se vean correctamente

### 2. Single Header

```cpp
// Archivo único: OBJ_Loader.h
// Ventaja: Fácil de integrar, sin configuración
```

### 3. Triangulación Automática

```cpp
// Polígonos n-lados → Triángulos automáticamente
// Ventaja: Funciona con cualquier modelo
```

### 4. Namespace Personalizado

```cpp
namespace objl {
    // Evita conflictos de nombres
}
```

---

## 📝 Ejemplo Completo en BaseApp

```cpp
#include "BaseApp.h"

HRESULT BaseApp::init() {
    // ... inicialización previa ...
    
    // Crear actor
    g_AKoro = EngineUtilities::TSharedPointer<Actor>(
        new Actor(g_device)
    );
    
    if (!g_AKoro.isNull()) {
        // PASO 1: Cargar modelo OBJ
        koroMesh = m_loader.LoadOBJModel("models/koroGod.obj");
        
        // PASO 2: Cargar textura
        HRESULT hr = g_koroTexture.init(
            g_device, "textures/korotexture", PNG
        );
        if (FAILED(hr)) {
            ERROR("Main", "InitDevice", "Texture load failed");
            return hr;
        }
        
        // PASO 3: Preparar contenedores
        std::vector<MeshComponent> meshes;
        meshes.push_back(koroMesh);
        
        std::vector<Texture> textures;
        textures.push_back(g_koroTexture);
        
        // PASO 4: Asignar a actor
        g_AKoro->SetMesh(g_device, meshes);
        g_AKoro->setTextures(textures);
        
        // PASO 5: Aplicar transformación
        g_AKoro->getComponent<Transform>()->setTransform(
            EngineUtilities::Vector3(0.0f, 0.0f, 0.0f),      // Posición
            EngineUtilities::Vector3(0.0f, 3.4f, 0.0f),      // Rotación
            EngineUtilities::Vector3(0.025f, 0.025f, 0.025f) // Escala
        );
        
        g_AKoro->setCastShadow(false);
        g_actors.push_back(g_AKoro);
    }
    
    return S_OK;
}
```

---

## 🐛 Troubleshooting Común

### Problema: Archivo no encontrado

```
Error: Failed to load OBJ model: models/koroGod.obj
```

**Solución**:
1. Verificar ruta relativa desde ejecutable
2. Verificar que archivo existe
3. Usar rutas absolutas para debug

### Problema: Textura invertida

**Solución**: Ya está automáticamente invertida en el parser (línea 1050 de OBJ_Loader.h)

### Problema: Modelo negro

**Solución**:
1. Verificar carga de textura
2. Revisar iluminación de escena
3. Verificar coordenadas UV

### Problema: Modelo distorsionado

**Solución**:
1. Ajustar escala en Transform
2. Verificar escala de exportación en editor 3D

---

## ✅ Checklist de Carga

Antes de renderizar un modelo, verifica:

- [ ] Archivo .obj existe en `models/` 
- [ ] Ruta es correcta
- [ ] Formato OBJ es válido
- [ ] `mesh.m_numVertex > 0`
- [ ] `mesh.m_numIndex > 0`
- [ ] Textura cargada correctamente
- [ ] Escala aplicada en Transform
- [ ] Iluminación presente en escena

---

## 🔄 Proceso de Carga

```
Usuario → LoadOBJModel()
           ↓
        Abrir archivo
           ↓
        Parsear línea por línea
           ├─ v   → Posiciones
           ├─ vt  → Coordenadas UV
           ├─ vn  → Normales
           └─ f   → Caras/Triángulos
           ↓
        Generar índices
           ↓
        Invertir coordenada V
           ↓
        Retornar MeshComponent
           ↓
        Usuario → Asignar a Actor
                  ↓
                  Renderizar
```

---

## 📄 Licencia

RabOneEngine - Motor gráfico personalizado con fines educativos.
© 2025 JustRab

