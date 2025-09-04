#pragma once

//----------------------------------------------------------------------

#include "base/sat.h"
#include "base/type/sat_point.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_Rect
{

    SAT_Rect();
    SAT_Rect(sat_coord_t v);
    SAT_Rect(sat_coord_t aw, sat_coord_t ah);
    SAT_Rect(SAT_Point asize);
    SAT_Rect(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah);
    SAT_Rect(SAT_Point apos, SAT_Point asize);

    SAT_Rect&   operator += (sat_coord_t V);
    SAT_Rect&   operator += (SAT_Point P);
    SAT_Rect&   operator += (SAT_Rect R);
    SAT_Rect&   operator -= (sat_coord_t V);
    SAT_Rect&   operator -= (SAT_Point P);
    SAT_Rect&   operator -= (SAT_Rect R);
    SAT_Rect&   operator *= (sat_coord_t V);
    SAT_Rect&   operator *= (SAT_Point P);
    SAT_Rect&   operator *= (SAT_Rect R);
    SAT_Rect&   operator /= (sat_coord_t V);
    SAT_Rect&   operator /= (SAT_Point P);
    SAT_Rect&   operator /= (SAT_Rect R);
 // SAT_Rect&   operator += (SAT_Point> P);
 // SAT_Rect&   operator -= (SAT_Point P);

    SAT_Point   getPos();
    SAT_Point   getSize();
    void        set(sat_coord_t _v);
    void        set(sat_coord_t _w, sat_coord_t _h);
    void        set(sat_coord_t _x, sat_coord_t _y, sat_coord_t _w, sat_coord_t _h);
    void        setX1(sat_coord_t _x1);
    void        setY1(sat_coord_t _y1);
    void        setX2(sat_coord_t _x2);
    void        setY2(sat_coord_t _y2);
    sat_coord_t x1();
    sat_coord_t y1();
    sat_coord_t x2();
    sat_coord_t y2();
    void        setPos(SAT_Point p);
    void        setPos(sat_coord_t ax, sat_coord_t ay);
    void        setSize(SAT_Point s);
    void        setSize(sat_coord_t aw, sat_coord_t ah);

    void        scale(sat_coord_t AScale);
    void        scale(sat_coord_t sx, sat_coord_t sy);
    void        scale(sat_coord_t sx, sat_coord_t sy, sat_coord_t sw, sat_coord_t sh);
    void        scale(SAT_Point s);
    void        scale(SAT_Rect r);
    void        add(sat_coord_t AValue);
    void        add(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah);
    void        add(SAT_Rect R);
    void        addPos(SAT_Point P);
    void        sub(sat_coord_t AValue);
    void        sub(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah);
    void        sub(SAT_Rect R);
    void        subPos(SAT_Point P);
    void        grow(sat_coord_t AValue);
    void        grow(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah);
    void        grow(SAT_Rect R);
    void        grow(SAT_Point P);
    void        shrink(sat_coord_t AValue);
    void        shrink(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah);
    void        shrink(SAT_Rect R);
    void        shrink(SAT_Point P);
    void        addLeft(sat_coord_t ASize);
    void        addTop(sat_coord_t ASize);
    void        addRight(sat_coord_t ASize);
    void        addBottom(sat_coord_t ASize);
    void        removeLeft(sat_coord_t ASize);
    void        removeTop(sat_coord_t ASize);
    void        removeRight(sat_coord_t ASize);
    void        removeBottom(sat_coord_t ASize);

    bool        isEmpty();
    bool        isNotEmpty();
    bool        intersects(SAT_Rect R);
    bool        contains(sat_coord_t xpos, sat_coord_t ypos);
    void        overlap(SAT_Rect R);
    void        combine(SAT_Rect R);

    bool        equal(SAT_Rect R);

 // void        remove(SAT_Rect ARect);

    union {
        struct { sat_coord_t x,y,w,h; };               // rect
        struct { sat_coord_t left,top,right,bottom; }; // edge
        struct { sat_coord_t tl, tr, br, bl; };        // corners
        sat_coord_t data[4];
    };

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Rect::SAT_Rect()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

SAT_Rect::SAT_Rect(sat_coord_t v)
{
    x = 0;
    y = 0;
    w = v;
    h = v;
}

SAT_Rect::SAT_Rect(sat_coord_t aw, sat_coord_t ah)
{
    x = 0;
    y = 0;
    w = aw;
    h = ah;
}

SAT_Rect::SAT_Rect(SAT_Point asize)
{
    x = 0;
    y = 0;
    w = asize.w;
    h = asize.h;
}

SAT_Rect::SAT_Rect(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah)
{
    x = ax;
    y = ay;
    w = aw;
    h = ah;
}

SAT_Rect::SAT_Rect(SAT_Point apos, SAT_Point asize)
{
    x = apos.x;
    y = apos.y;
    w = asize.w;
    h = asize.h;
}

SAT_Rect& SAT_Rect::operator += (sat_coord_t V)
{
    add(V);
    return *this;
}

SAT_Rect& SAT_Rect::operator += (SAT_Point P)
{
    add(P);
    return *this;
}

SAT_Rect& SAT_Rect::operator += (SAT_Rect R)
{
    add(R);
    return *this;
}

SAT_Rect& SAT_Rect::operator -= (sat_coord_t V)
{
    sub(V);
    return *this;
}

SAT_Rect& SAT_Rect::operator -= (SAT_Point P)
{
    sub(P);
    return *this;
}

SAT_Rect& SAT_Rect::operator -= (SAT_Rect R)
{
    sub(R);
    return *this;
}

SAT_Rect& SAT_Rect::operator *= (sat_coord_t V)
{
    scale(V);
    return *this;
}

SAT_Rect& SAT_Rect::operator *= (SAT_Point P)
{
    scale(P);
    return *this;
}

SAT_Rect& SAT_Rect::operator *= (SAT_Rect R)
{
    scale(R);
    return *this;
}

SAT_Rect& SAT_Rect::operator /= (sat_coord_t V)
{
    sat_coord_t v;
    v = (1.0 / V);
    scale(v);
    return *this;
}

SAT_Rect& SAT_Rect::operator /= (SAT_Point P)
{
    SAT_Point p = P;
    p.x = (1.0 / P.x);
    p.y = (1.0 / P.y);
    scale(p);
    return *this;
}

SAT_Rect& SAT_Rect::operator /= (SAT_Rect R)
{
    SAT_Rect r;
    r.x = (1.0 / R.x);
    r.y = (1.0 / R.y);
    r.w = (1.0 / R.w);
    r.h = (1.0 / R.h);
    scale(r);
    return *this;
}

// SAT_Rect& SAT_Rect::operator += (SAT_Point> P)
// {
//     return *this;
// }

// SAT_Rect& SAT_Rect::operator -= (SAT_Point P)
// {
//     sub(P);
//     return *this;
// }

SAT_Point SAT_Rect::getPos()
{
    return SAT_Point(x,y);
}

SAT_Point SAT_Rect::getSize()
{
    return SAT_Point(w,h);
}

void SAT_Rect::set(sat_coord_t _v)
{
    x = _v;
    y = _v;
    w = _v;
    h = _v;
}

void SAT_Rect::set(sat_coord_t _w, sat_coord_t _h)
{
    x = 0;
    y = 0;
    w = _w;
    h = _h;
}

void SAT_Rect::set(sat_coord_t _x, sat_coord_t _y, sat_coord_t _w, sat_coord_t _h)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void SAT_Rect::setX1(sat_coord_t _x1) { w -= (_x1 - x);   x = _x1; }
void SAT_Rect::setY1(sat_coord_t _y1) { h -= (_y1 - y);   y = _y1; }
void SAT_Rect::setX2(sat_coord_t _x2) { w += (_x2 - x - w); }
void SAT_Rect::setY2(sat_coord_t _y2) { h += (_y2 - y - h); }

sat_coord_t SAT_Rect::x1() { return x; }
sat_coord_t SAT_Rect::y1() { return y; }
sat_coord_t SAT_Rect::x2() { return x + w; }
sat_coord_t SAT_Rect::y2() { return y + h; }

void SAT_Rect::setPos(SAT_Point p)
{
    x = p.x;
    y = p.y;
}

void SAT_Rect::setPos(sat_coord_t ax, sat_coord_t ay)
{
    x = ax;
    y = ay;
}

void SAT_Rect::setSize(SAT_Point s)
{
    w = s.w;
    h = s.h;
}

void SAT_Rect::setSize(sat_coord_t aw, sat_coord_t ah)
{
    w = aw;
    h = ah;
}

void SAT_Rect::scale(sat_coord_t AScale)
{
    x *= AScale;
    y *= AScale;
    w *= AScale;
    h *= AScale;
}

void SAT_Rect::scale(sat_coord_t sx, sat_coord_t sy)
{
    x *= sx;
    y *= sy;
    w *= sx;
    h *= sy;
}

void SAT_Rect::scale(sat_coord_t sx, sat_coord_t sy, sat_coord_t sw, sat_coord_t sh)
{
    x *= sx;
    y *= sy;
    w *= sw;
    h *= sh;
}

void SAT_Rect::scale(SAT_Point s)
{
    x *= s.x;
    y *= s.y;
    w *= s.x;
    h *= s.y;
}

void SAT_Rect::scale(SAT_Rect r)
{
    x *= r.x;
    y *= r.y;
    w *= r.w;
    h *= r.h;
}

void SAT_Rect::add(sat_coord_t AValue)
{
    x += AValue;
    y += AValue;
    w += AValue;
    h += AValue;
}

void SAT_Rect::add(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah)
{
    x += ax;
    y += ay;
    w += aw;
    h += ah;
}

void SAT_Rect::add(SAT_Rect R)
{
    x += R.x;
    y += R.y;
    w += R.w;
    h += R.h;
}

void SAT_Rect::addPos(SAT_Point P)
{
    x += P.x;
    y += P.y;
}

void SAT_Rect::sub(sat_coord_t AValue)
{
    x -= AValue;
    y -= AValue;
    w -= AValue;
    h -= AValue;
}

void SAT_Rect::sub(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah)
{
    x -= ax;
    y -= ay;
    w -= aw;
    h -= ah;
}

void SAT_Rect::sub(SAT_Rect R)
{
    x -= R.x;
    y -= R.y;
    w -= R.w;
    h -= R.h;
}

void SAT_Rect::subPos(SAT_Point P)
{
    x += P.x;
    y += P.y;
}

void SAT_Rect::grow(sat_coord_t AValue)
{
    x -= AValue;
    y -= AValue;
    w += (AValue + AValue);
    h += (AValue + AValue);
}

void SAT_Rect::grow(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah)
{
    x -= ax;
    y -= ay;
    w += (ax + aw);
    h += (ay + ah);
}

void SAT_Rect::grow(SAT_Rect R)
{
    x -= R.x;
    y -= R.y;
    w += (R.x + R.w);
    h += (R.y + R.h);
}

void SAT_Rect::grow(SAT_Point P)
{
    x -= P.x;
    y -= P.y;
    w += (P.x * 2.0);
    h += (P.y * 2.0);
}

void SAT_Rect::shrink(sat_coord_t AValue)
{
    x += AValue;
    y += AValue;
    w -= (AValue + AValue);
    h -= (AValue + AValue);
}

void SAT_Rect::shrink(sat_coord_t ax, sat_coord_t ay, sat_coord_t aw, sat_coord_t ah)
{
    x += ax;
    y += ay;
    w -= (ax + aw);
    h -= (ay + ah);
}

void SAT_Rect::shrink(SAT_Rect R)
{
    x += R.x;
    y += R.y;
    w -= (R.x + R.w);
    h -= (R.y + R.h);
}

void SAT_Rect::shrink(SAT_Point P)
{
    x += P.x;
    y += P.y;
    w -= (P.x * 2.0);
    h -= (P.y * 2.0);
}

void SAT_Rect::addLeft(sat_coord_t ASize)       { x -= ASize; w += ASize; }
void SAT_Rect::addTop(sat_coord_t ASize)        { y -= ASize; h += ASize; }
void SAT_Rect::addRight(sat_coord_t ASize)      { w += ASize; }
void SAT_Rect::addBottom(sat_coord_t ASize)     { h += ASize; }

void SAT_Rect::removeLeft(sat_coord_t ASize)    { x += ASize; w -= ASize; }
void SAT_Rect::removeTop(sat_coord_t ASize)     { y += ASize; h -= ASize; }
void SAT_Rect::removeRight(sat_coord_t ASize)   { w -= ASize; }
void SAT_Rect::removeBottom(sat_coord_t ASize)  { h -= ASize; }

bool SAT_Rect::isEmpty()
{
    if (w <= 0.0f) return true;
    if (h <= 0.0f) return true;
    return false;
}

bool SAT_Rect::isNotEmpty()
{
    if ((w > 0.0f) && (h > 0.0f)) return true;
    return false;
}

// returns true if any of the edges intersects

bool SAT_Rect::intersects(SAT_Rect R)
{
    if (R.x1() > x2() ) return false; // too far right
    if (R.y1() > y2() ) return false; // too far down
    if (R.x2() < x1() ) return false; // too far left
    if (R.y2() < y1() ) return false; // too far up
    return true;
}

// returns true if APoint is inside
// if widget.contains(mousex,mousey)

bool SAT_Rect::contains(sat_coord_t xpos, sat_coord_t ypos)
{
    if (xpos < x   ) return false;
    if (xpos > x2()) return false;
    if (ypos < y   ) return false;
    if (ypos > y2()) return false;
    return true;
}

/*
    R_____
    |   _ |__
    |  |XX|  |
    |__|XX|  |
       |_____|

            R____
         _ |__   |
        |  |XX|  |
        |  |XX|__|
        |_____|



    R_______     _______
    |   __  |   |  R__  |
    |  |XX| |   |  |XX| |
    |  |XX| |   |  |XX| |
    |_______|   |_______|

*/

// intersection
// largest x
// smallest x2

void SAT_Rect::overlap(SAT_Rect R)
{
    if ( R.x1() > x1() ) setX1( R.x1() );
    if ( R.x2() < x2() ) setX2( R.x2() );
    if ( R.y1() > y1() ) setY1( R.y1() );
    if ( R.y2() < y2() ) setY2( R.y2() );
}

// void SAT_Rect::overlap(SAT_Rect R)
// {
//     if ( R.x1() > x1() ) setX1( R.x1() );
//     if ( R.y1() > y1() ) setY1( R.y1() );
//     if ( R.x2() < x2() ) setX2( R.x2() );
//     if ( R.y2() < y2() ) setX2( R.y2() );
// }

// combine rects
// (so that both of them fits inside)
// parent.combine(child)

void SAT_Rect::combine(SAT_Rect R)
{
    //if (this->isEmpty()) set(R.x,R.y,R.w,R.h);
    if (R.isEmpty()) return;
    //printf("combine %.0f,%.0f,%.0f,%.0f R %.0f,%.0f,%.0f,%.0f -> ",x,y,w,h,R.x,R.y,R.w,R.h);
    if ( R.x1() < x1() ) setX1( R.x1() );
    if ( R.x2() > x2() ) setX2( R.x2() );
    if ( R.y1() < y1() ) setY1( R.y1() );
    if ( R.y2() > y2() ) setY2( R.y2() );
    //printf("%.0f,%.0f,%.0f,%.0f\n",x,y,w,h);
}

// remove ARect (so that it lies outside)

// void SAT_Rect::remove(SAT_Rect ARect)
// {
// }

bool SAT_Rect::equal(SAT_Rect R)
{
    if (abs(x - R.x) > SAT_TINY) return false;
    if (abs(y - R.y) > SAT_TINY) return false;
    if (abs(w - R.w) > SAT_TINY) return false;
    if (abs(h - R.h) > SAT_TINY) return false;
    return true;
}
