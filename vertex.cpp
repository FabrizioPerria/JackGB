#include "vertex.h"



Q_DECL_CONSTEXPR inline const QVector3D& Vertex::getPosition() const { return _position; }
void Vertex::setPosition(const QVector3D& position) { _position = position; }

Q_DECL_CONSTEXPR inline const QVector3D& Vertex::getColor() const { return _color; }
void Vertex::setColor(const QVector3D& color) { _color = color; }


