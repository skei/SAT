#pragma once

//----------------------------------------------------------------------

#include "base/sat.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_Point
{

    SAT_Point();
    SAT_Point(sat_coord_t v);
    SAT_Point(sat_coord_t ax, sat_coord_t ay);
 // SAT_Point(const SAT_Point& p);

    SAT_Point&  operator += (sat_coord_t P);
    SAT_Point&  operator -= (sat_coord_t P);
    SAT_Point&  operator *= (sat_coord_t P);
    SAT_Point&  operator /= (sat_coord_t P);
    SAT_Point&  operator += (SAT_Point P);
    SAT_Point&  operator -= (SAT_Point P);
    SAT_Point&  operator *= (SAT_Point P);
    SAT_Point&  operator /= (SAT_Point P);
 // MIP_Rect&   operator += (sat_coord_t P);
 // MIP_Rect&   operator -= (sat_coord_t P);
 
    void        scale(sat_coord_t AScale);
    void        scale(sat_coord_t sx, sat_coord_t sy);
    void        scale(SAT_Point s);
    void        add(sat_coord_t AValue);
    void        add(sat_coord_t ax, sat_coord_t ay);
    void        add(SAT_Point p);
    void        sub(sat_coord_t AValue);
    void        sub(sat_coord_t ax, sat_coord_t ay);
    void        sub(SAT_Point p);
    void        mul(sat_coord_t AValue);
    void        mul(sat_coord_t ax, sat_coord_t ay);
    void        mul(SAT_Point p);
    void        div(sat_coord_t AValue);
    void        div(sat_coord_t ax, sat_coord_t ay);
    void        div(SAT_Point p);

    union
    {
        struct { sat_coord_t x,y; };
        struct { sat_coord_t w,h; };
        struct { sat_coord_t horiz,vert; };
        sat_coord_t data[2];
    };

};

//----------------------------------------------------------------------

//----------------------------------------------------------------------

SAT_Point::SAT_Point()
{
    x = 0;
    y = 0;
}

SAT_Point::SAT_Point(sat_coord_t v)
{
    x = v;
    y = v;
}

SAT_Point::SAT_Point(sat_coord_t ax, sat_coord_t ay)
{
    x = ax;
    y = ay;
}

// SAT_Point::SAT_Point(const SAT_Point& p)
// {
//   x = p.x;
//   y = p.y;
// }

SAT_Point& SAT_Point::operator += (sat_coord_t P)
{
    add(P);
    return *this;
}

SAT_Point& SAT_Point::operator -= (sat_coord_t P)
{
    sub(P);
    return *this;
}

SAT_Point& SAT_Point::operator *= (sat_coord_t P)
{
    mul(P);
    return *this;
}

SAT_Point& SAT_Point::operator /= (sat_coord_t P)
{
    div(P);
    return *this;
}

SAT_Point& SAT_Point::operator += (SAT_Point P)
{
    add(P);
    return *this;
}

SAT_Point& SAT_Point::operator -= (SAT_Point P)
{
    sub(P);
    return *this;
}

SAT_Point& SAT_Point::operator *= (SAT_Point P)
{
    mul(P);
    return *this;
}

SAT_Point& SAT_Point::operator /= (SAT_Point P)
{
    div(P);
    return *this;
}

// MIP_Rect& SAT_Point::operator += (sat_coord_t P)
// {
//     add(P);
//     return *this;
// }

// MIP_Rect& SAT_Point::operator -= (sat_coord_t P)
// {
//     sub(P);
//     return *this;
// }

void SAT_Point::scale(sat_coord_t AScale)
{
    x *= AScale;
    y *= AScale;
}

void SAT_Point::scale(sat_coord_t sx, sat_coord_t sy)
{
    x *= sx;
    y *= sy;
}

void SAT_Point::scale(SAT_Point s)
{
    x *= s.x;
    y *= s.y;
}

void SAT_Point::add(sat_coord_t AValue)
{
    x += AValue;
    y += AValue;
}

void SAT_Point::add(sat_coord_t ax, sat_coord_t ay)
{
    x += ax;
    y += ay;
}

void SAT_Point::add(SAT_Point p)
{
    x += p.x;
    y += p.y;
}

void SAT_Point::sub(sat_coord_t AValue)
{
    x -= AValue;
    y -= AValue;
}

void SAT_Point::sub(sat_coord_t ax, sat_coord_t ay)
{
    x -= ax;
    y -= ay;
}

void SAT_Point::sub(SAT_Point p)
{
    x -= p.x;
    y -= p.y;
}

void SAT_Point::mul(sat_coord_t AValue)
{
    x *= AValue;
    y *= AValue;
}

void SAT_Point::mul(sat_coord_t ax, sat_coord_t ay)
{
    x *= ax;
    y *= ay;
}

void SAT_Point::mul(SAT_Point p)
{
    x *= p.x;
    y *= p.y;
}

void SAT_Point::div(sat_coord_t AValue)
{
    x /= AValue;
    y /= AValue;
}

void SAT_Point::div(sat_coord_t ax, sat_coord_t ay)
{
    x /= ax;
    y /= ay;
}

void SAT_Point::div(SAT_Point p)
{
    x /= p.x;
    y /= p.y;
}
