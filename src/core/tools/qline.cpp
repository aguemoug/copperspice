/***********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
* Copyright (c) 2012-2016 Ansel Sermersheim
* Copyright (c) 2012-2014 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software: you can redistribute it and/or 
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with CopperSpice.  If not, see 
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#include <qline.h>
#include <qdebug.h>
#include <qdatastream.h>
#include <qmath.h>
#include <qnumeric_p.h>

QT_BEGIN_NAMESPACE

QDebug operator<<(QDebug d, const QLine &p)
{
   d << "QLine(" << p.p1() << ',' << p.p2() << ')';
   return d;
}

#ifndef QT_NO_DATASTREAM

QDataStream &operator<<(QDataStream &stream, const QLine &line)
{
   stream << line.p1() << line.p2();
   return stream;
}

QDataStream &operator>>(QDataStream &stream, QLine &line)
{
   QPoint p1, p2;
   stream >> p1;
   stream >> p2;
   line = QLine(p1, p2);

   return stream;
}

#endif // QT_NO_DATASTREAM

inline static qreal q_deg2rad(qreal x)
{
   return x * qreal(0.01745329251994329576923690768489);    /* pi/180 */
}

inline static qreal q_rad2deg(qreal x)
{
   return x * qreal(57.295779513082320876798154814105);    /* 180/pi */
}

/*!
    \class QLineF
    \ingroup painting

    \brief The QLineF class provides a two-dimensional vector using
    floating point precision.

    A QLineF describes a finite length line (or line segment) on a
    two-dimensional surface. QLineF defines the start and end points
    of the line using floating point accuracy for coordinates.  Use
    the toLine() function to retrieve an integer based copy of this
    line.

    \table
    \row
        \o \inlineimage qline-point.png
        \o \inlineimage qline-coordinates.png
    \endtable

    The positions of the line's start and end points can be retrieved
    using the p1(), x1(), y1(), p2(), x2(), and y2() functions. The
    dx() and dy() functions return the horizontal and vertical
    components of the line, respectively.

    The line's length can be retrieved using the length() function,
    and altered using the setLength() function.  Similarly, angle()
    and setAngle() are respectively used for retrieving and altering
    the angle of the line. Use the isNull()
    function to determine whether the QLineF represents a valid line
    or a null line.

    The intersect() function determines the IntersectType for this
    line and a given line, while the angle() function returns the
    angle between the lines. In addition, the unitVector() function
    returns a line that has the same starting point as this line, but
    with a length of only 1, while the normalVector() function returns
    a line that is perpendicular to this line with the same starting
    point and length.

    Finally, the line can be translated a given offset using the
    translate() function, and can be traversed using the pointAt()
    function.

    \sa QLine, QPolygonF, QRectF
*/

/*!
    \enum QLineF::IntersectType

    Describes the intersection between two lines.

    \table
    \row
    \o \inlineimage qlinef-unbounded.png
    \o \inlineimage qlinef-bounded.png
    \row
    \o QLineF::UnboundedIntersection
    \o QLineF::BoundedIntersection
    \endtable

    \value NoIntersection Indicates that the lines do not intersect;
    i.e. they are parallel.

    \value UnboundedIntersection The two lines intersect, but not
    within the range defined by their lengths. This will be the case
    if the lines are not parallel.

    intersect() will also return this value if the intersect point is
    within the start and end point of only one of the lines.

    \value BoundedIntersection The two lines intersect with each other
    within the start and end points of each line.

    \sa intersect()
*/

/*!
    \fn QLineF::QLineF()

    Constructs a null line.
*/

/*!
    \fn QLineF::QLineF(const QPointF &p1, const QPointF &p2)

    Constructs a line object that represents the line between \a p1 and
    \a p2.
*/

/*!
    \fn QLineF::QLineF(qreal x1, qreal y1, qreal x2, qreal y2)

    Constructs a line object that represents the line between (\a x1, \a y1) and
    (\a x2, \a y2).
*/

/*!
    \fn QLineF::QLineF(const QLine &line)

    Construct a QLineF object from the given integer-based \a line.

    \sa toLine()
*/

/*!
    Returns true if the line is not set up with valid start and end point;
    otherwise returns false.
*/

bool QLineF::isNull() const
{
   return (qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y())) ? true : false;
}


/*!
    \fn QPointF QLineF::p1() const

    Returns the line's start point.

    \sa x1(), y1(), p2()
*/

/*!
    \fn QPointF QLineF::p2() const

    Returns the line's end point.

    \sa x2(), y2(), p1()
*/

/*!
    \fn QLine QLineF::toLine() const

    Returns an integer based copy of this line.

    Note that the returned line's start and end points are rounded to
    the nearest integer.

    \sa QLineF()
*/
/*!
    \fn qreal QLineF::x1() const

    Returns the x-coordinate of the line's start point.

    \sa p1()
*/

/*!
    \fn qreal QLineF::y1() const

    Returns the y-coordinate of the line's start point.

    \sa p1()
*/

/*!
    \fn qreal QLineF::x2() const

    Returns the x-coordinate of the line's end point.

    \sa p2()
*/

/*!
    \fn qreal QLineF::y2() const

    Returns the y-coordinate of the line's end point.

    \sa p2()
*/

/*!
    \fn qreal QLineF::dx() const

    Returns the horizontal component of the line's vector.
	Return value is positive if x2() >= x1() and negative if x2() < x1().

    \sa dy(), pointAt()
*/

/*!
    \fn qreal QLineF::dy() const

    Returns the vertical component of the line's vector.
	Return value is positive if y2() >= y1() and negative if y2() < y1().

    \sa dx(), pointAt()
*/

/*!
    \fn QLineF::setLength(qreal length)

    Sets the length of the line to the given \a length. QLineF will
    move the end point - p2() - of the line to give the line its new length.
    If the given \a length is negative the angle() is also changed.

    If the line is a null line, the length will remain zero regardless
    of the length specified.

    \sa length(), isNull()
*/

/*!
    \fn QLineF QLineF::normalVector() const

    Returns a line that is perpendicular to this line with the same starting
    point and length.

    \image qlinef-normalvector.png

    \sa unitVector()
*/

/*!
    \fn bool QLineF::operator!=(const QLineF &line) const

    Returns true if the given \a line is not the same as \e this line.

    A line is different from another line if their start or end points
    differ, or the internal order of the points is different.
*/

/*!
    \fn bool QLineF::operator==(const QLineF &line) const

    Returns true if the given \a line is the same as this line.

    A line is identical to another line if the start and end points
    are identical, and the internal order of the points is the same.
*/

/*!
  \fn qreal QLineF::pointAt(qreal t) const

  Returns the point at the parameterized position specified by \a
  t. The function returns the line's start point if t = 0, and its end
  point if t = 1.

  \sa dx(), dy()
*/

/*!
    Returns the length of the line.

    \sa setLength()
*/
qreal QLineF::length() const
{
   qreal x = pt2.x() - pt1.x();
   qreal y = pt2.y() - pt1.y();
   return qSqrt(x * x + y * y);
}

/*!
    \since 4.4

    Returns the angle of the line in degrees.

    The return value will be in the range of values from 0.0 up to but not
    including 360.0. The angles are measured counter-clockwise from a point
    on the x-axis to the right of the origin (x > 0).

    \sa setAngle()
*/
qreal QLineF::angle() const
{
   const qreal dx = pt2.x() - pt1.x();
   const qreal dy = pt2.y() - pt1.y();

   const qreal theta = q_rad2deg(qAtan2(-dy, dx));

   const qreal theta_normalized = theta < 0 ? theta + 360 : theta;

   if (qFuzzyCompare(theta_normalized, qreal(360))) {
      return qreal(0);
   } else {
      return theta_normalized;
   }
}

/*!
    \since 4.4

    Sets the angle of the line to the given \a angle (in degrees).
    This will change the position of the second point of the line such that
    the line has the given angle.

    Positive values for the angles mean counter-clockwise while negative values
    mean the clockwise direction. Zero degrees is at the 3 o'clock position.

    \sa angle()
*/
void QLineF::setAngle(qreal angle)
{
   const qreal angleR = q_deg2rad(angle);
   const qreal l = length();

   const qreal dx = qCos(angleR) * l;
   const qreal dy = -qSin(angleR) * l;

   pt2.rx() = pt1.x() + dx;
   pt2.ry() = pt1.y() + dy;
}

/*!
    \since 4.4

    Returns a QLineF with the given \a length and \a angle.

    The first point of the line will be on the origin.

    Positive values for the angles mean counter-clockwise while negative values
    mean the clockwise direction. Zero degrees is at the 3 o'clock position.
*/
QLineF QLineF::fromPolar(qreal length, qreal angle)
{
   const qreal angleR = q_deg2rad(angle);
   return QLineF(0, 0, qCos(angleR) * length, -qSin(angleR) * length);
}

/*!
    Returns the unit vector for this line, i.e a line starting at the
    same point as \e this line with a length of 1.0.

    \sa normalVector()
*/
QLineF QLineF::unitVector() const
{
   qreal x = pt2.x() - pt1.x();
   qreal y = pt2.y() - pt1.y();

   qreal len = qSqrt(x * x + y * y);
   QLineF f(p1(), QPointF(pt1.x() + x / len, pt1.y() + y / len));

   if (qAbs(f.length() - 1) >= 0.001) {
      qWarning("QLine::unitVector() New line does not have unit length");
   }

   return f;
}

/*!
    \fn QLineF::IntersectType QLineF::intersect(const QLineF &line, QPointF *intersectionPoint) const

    Returns a value indicating whether or not \e this line intersects
    with the given \a line.

    The actual intersection point is extracted to \a intersectionPoint
    (if the pointer is valid). If the lines are parallel, the
    intersection point is undefined.
*/

QLineF::IntersectType QLineF::intersect(const QLineF &l, QPointF *intersectionPoint) const
{
   // ipmlementation is based on Graphics Gems III's "Faster Line Segment Intersection"
   const QPointF a = pt2 - pt1;
   const QPointF b = l.pt1 - l.pt2;
   const QPointF c = pt1 - l.pt1;

   const qreal denominator = a.y() * b.x() - a.x() * b.y();
   if (denominator == 0 || !qt_is_finite(denominator)) {
      return NoIntersection;
   }

   const qreal reciprocal = 1 / denominator;
   const qreal na = (b.y() * c.x() - b.x() * c.y()) * reciprocal;
   if (intersectionPoint) {
      *intersectionPoint = pt1 + a * na;
   }

   if (na < 0 || na > 1) {
      return UnboundedIntersection;
   }

   const qreal nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;
   if (nb < 0 || nb > 1) {
      return UnboundedIntersection;
   }

   return BoundedIntersection;
}

/*!
    \fn void QLineF::translate(const QPointF &offset)

    Translates this line by the given \a offset.
*/

/*!
    \fn void QLineF::translate(qreal dx, qreal dy)
    \overload

    Translates this line the distance specified by \a dx and \a dy.
*/

/*!
    \fn QLineF QLineF::translated(const QPointF &offset) const

    \since 4.4

    Returns this line translated by the given \a offset.
*/

/*!
    \fn QLineF QLineF::translated(qreal dx, qreal dy) const
    \overload
    \since 4.4

    Returns this line translated the distance specified by \a dx and \a dy.
*/

/*!
    \fn void QLineF::setP1(const QPointF &p1)
    \since 4.4

    Sets the starting point of this line to \a p1.

    \sa setP2(), p1()
*/


/*!
    \fn void QLineF::setP2(const QPointF &p2)
    \since 4.4

    Sets the end point of this line to \a p2.

    \sa setP1(), p2()
*/


/*!
    \fn void QLineF::setPoints(const QPointF &p1, const QPointF &p2)
    \since 4.4

    Sets the start point of this line to \a p1 and the end point of this line to \a p2.

    \sa setP1(), setP2(), p1(), p2()
*/


/*!
    \fn void QLineF::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
    \since 4.4

    Sets this line to the start in \a x1, \a y1 and end in \a x2, \a y2.

    \sa setP1(), setP2(), p1(), p2()
*/

/*!
  \fn qreal QLineF::angleTo(const QLineF &line) const

  \since 4.4

  Returns the angle (in positive degrees) from this line to the given \a
  line, taking the direction of the lines into account. If the lines
  do not intersect within their range, it is the intersection point of
  the extended lines that serves as origin (see
  QLineF::UnboundedIntersection).

  The returned value represents the number of degrees you need to add
  to this line to make it have the same angle as the given \a line,
  going counter-clockwise.

  \sa intersect()
*/
qreal QLineF::angleTo(const QLineF &l) const
{
   if (isNull() || l.isNull()) {
      return 0;
   }

   const qreal a1 = angle();
   const qreal a2 = l.angle();

   const qreal delta = a2 - a1;
   const qreal delta_normalized = delta < 0 ? delta + 360 : delta;

   if (qFuzzyCompare(delta, qreal(360))) {
      return 0;
   } else {
      return delta_normalized;
   }
}

/*!
  \fn qreal QLineF::angle(const QLineF &line) const

  \obsolete

  Returns the angle (in degrees) between this line and the given \a
  line, taking the direction of the lines into account. If the lines
  do not intersect within their range, it is the intersection point of
  the extended lines that serves as origin (see
  QLineF::UnboundedIntersection).

  \table
  \row
  \o \inlineimage qlinef-angle-identicaldirection.png
  \o \inlineimage qlinef-angle-oppositedirection.png
  \endtable

  When the lines are parallel, this function returns 0 if they have
  the same direction; otherwise it returns 180.

  \sa intersect()
*/
qreal QLineF::angle(const QLineF &l) const
{
   if (isNull() || l.isNull()) {
      return 0;
   }
   qreal cos_line = (dx() * l.dx() + dy() * l.dy()) / (length() * l.length());
   qreal rad = 0;
   // only accept cos_line in the range [-1,1], if it is outside, use 0 (we return 0 rather than PI for those cases)
   if (cos_line >= qreal(-1.0) && cos_line <= qreal(1.0)) {
      rad = qAcos( cos_line );
   }
   return q_rad2deg(rad);
}

QDebug operator<<(QDebug d, const QLineF &p)
{
   d << "QLineF(" << p.p1() << ',' << p.p2() << ')';
   return d;
}

#ifndef QT_NO_DATASTREAM
/*!
    \relates QLineF

    Writes the given \a line to the given \a stream and returns a
    reference to the stream.

    \sa {Serializing Qt Data Types}
*/

QDataStream &operator<<(QDataStream &stream, const QLineF &line)
{
   stream << line.p1() << line.p2();
   return stream;
}

/*!
    \relates QLineF

    Reads a line from the given \a stream into the given \a line and
    returns a reference to the stream.

    \sa {Serializing Qt Data Types}
*/

QDataStream &operator>>(QDataStream &stream, QLineF &line)
{
   QPointF start, end;
   stream >> start;
   stream >> end;
   line = QLineF(start, end);

   return stream;
}

#endif // QT_NO_DATASTREAM

QT_END_NAMESPACE