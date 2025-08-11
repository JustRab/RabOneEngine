#pragma once
#include "Prerequisites.h"
#include "Engine Utilities/Vectors/Vector3.h"
#include "Component.h"

class
  Transform : public Component {
public:
  // Constructor que inicializa posici�n, rotaci�n y escala por defecto
  Transform() : position(),
    rotation(),
    scale(),
    matrix(),
    Component(ComponentType::TRANSFORM) {
  }

  // M�todos para inicializaci�n, actualizaci�n, renderizado y destrucci�n
  // Inicializa el objeto Transform
  void
    init();

  // Actualiza el estado del objeto Transform basado en el tiempo transcurrido
  // @param deltaTime: Tiempo transcurrido desde la �ltima actualizaci�n
  void
    update(float deltaTime) override;

  // Renderiza el objeto Transform
  // @param deviceContext: Contexto del dispositivo de renderizado
  void
    render(DeviceContext& deviceContext) override {}

  // Destruye el objeto Transform y libera recursos
  void
    destroy() {}

  // M�todos de acceso a los datos de posici�n
  // Retorna la posici�n actual
  const EngineUtilities::Vector3&
    getPosition() const { return position; }

  // Establece una nueva posici�n
  void
    setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  // M�todos de acceso a los datos de rotaci�n
  // Retorna la rotaci�n actual
  const EngineUtilities::Vector3&
    getRotation() const { return rotation; }

  // Establece una nueva rotaci�n
  void
    setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  // M�todos de acceso a los datos de escala
  // Retorna la escala actual
  const EngineUtilities::Vector3&
    getScale() const { return scale; }

  // Establece una nueva escala
  void
    setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  void
    setTransform(const EngineUtilities::Vector3& newPos,
      const EngineUtilities::Vector3& newRot,
      const EngineUtilities::Vector3& newSca);

  // M�todo para trasladar la posici�n del objeto
  // @param translation: Vector que representa la cantidad de traslado en cada eje
  void
    translate(const EngineUtilities::Vector3& translation);

private:
  EngineUtilities::Vector3 position;  // Posici�n del objeto
  EngineUtilities::Vector3 rotation;  // Rotaci�n del objeto
  EngineUtilities::Vector3 scale;     // Escala del objeto

public:
  XMMATRIX matrix;    // Matriz de transformaci�n
};