#pragma once
#include <QVector2D>
#include <QVector3D>

class Vertex
{
public:
    Q_DECL_CONSTEXPR Vertex();
    Q_DECL_CONSTEXPR explicit Vertex(const QVector2D& position);
    Q_DECL_CONSTEXPR Vertex(const QVector2D& position, const QVector3D& color);

    Q_DECL_CONSTEXPR const QVector2D& getPosition() const;
    void setPosition(const QVector2D& position);

    Q_DECL_CONSTEXPR const QVector3D& getColor() const;
    void setColor(const QVector3D& color);

    static const int PositionTupleSize = 2;
    static const int ColorTupleSize = 3;
    static Q_DECL_CONSTEXPR int positionOffset();
    static Q_DECL_CONSTEXPR int colorOffset();
    static Q_DECL_CONSTEXPR int stride();

private:
    QVector2D _position;
    QVector3D _color;
};

Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector2D &position) : _position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector2D &position, const QVector3D &color) : _position(position), _color(color) {}

Q_DECL_CONSTEXPR inline int Vertex::positionOffset() { return offsetof(Vertex, _position); }
Q_DECL_CONSTEXPR inline int Vertex::colorOffset() { return offsetof(Vertex, _color); }
Q_DECL_CONSTEXPR inline int Vertex::stride() { return sizeof(Vertex); }
