#include "Vertex.h"
#include "macros.h"
#include "Utilities.h"
#include "EquilateralTriangle.h"
#include "Rectangle.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

EquilateralTriangle::EquilateralTriangle(const Vertex vertices[3])
{
	if (!vertices[0].isValid() || !vertices[1].isValid() || !vertices[2].isValid()
		|| vertices[0].isHigherThan(vertices[1]) 
		|| vertices[1].isHigherThan(vertices[0])
		|| !vertices[2].isToTheRightOf(vertices[0])            // if not OK
		|| vertices[2].isToTheRightOf(vertices[1])
		|| !doubleEqual(distance(vertices[0], vertices[2]) , distance(vertices[2], vertices[1]))
		|| !doubleEqual(distance(vertices[0], vertices[1]) , distance(vertices[2], vertices[1]))
		|| !doubleEqual(distance(vertices[0], vertices[1]) , distance(vertices[0], vertices[2])))
	{
		m_ver0 = getVertex(0); // reset vertex
		m_ver1 = getVertex(1); // reset vertex
		m_ver2 = getVertex(2); // reset vertex

		getLength();// get leg length
		getHeight();// get height of the triangle
		getArea();// get area of the triangle
		getPerimeter();// get perimeter of the triangle
		getCenter();// get center of the triangle
	}
	else
	{
		m_ver0 = vertices[0];//update
		m_ver1 = vertices[1];
		m_ver2 = vertices[2];

		getLength();// get leg length
		getHeight();// get height of the triangle
		getArea();// get area of the triangle
		getPerimeter();// get perimeter of the triangle
		getCenter();// get center of the triangle
	}
}
//-------------------------------------------------------
Vertex EquilateralTriangle::getVertex(int index) const
{// get a vertex default
	Vertex vertice;
	if (index == V_0)
	{
		vertice.m_col = 20;
		vertice.m_row = 20;
	}
	else if (index == V_1)
	{
		vertice.m_col = 30;
		vertice.m_row = 20;
	}
	else if (index == V_2)
	{
		vertice.m_col = 25;
		vertice.m_row = 20 + sqrt(75);
	}
	return vertice;
}
//------------------------------------------------
double EquilateralTriangle::getLength()const // get leg length
{
	return abs(m_ver0.m_col - m_ver1.m_col);
}
//--------------------------------------------------
double EquilateralTriangle::getHeight()const// get height of the triangle
{
	return abs(m_ver2.m_row - m_ver1.m_row);
}
//--------------------------------------------
double EquilateralTriangle::getArea() const // get area of the triangle
{
	return ((getLength() * getHeight()) / 2);
}
//---------------------------------------------------------
double EquilateralTriangle::getPerimeter()const//get perimeter of the triangle
{
	return (getLength() * 3);
}
//-------------------------------------------------------
Vertex EquilateralTriangle::getCenter()const
{// get center of the triangle
	Vertex center;
	center.m_col = m_ver1.m_col - (getLength() / 2);
	center.m_row = (getHeight() / 2) + m_ver0.m_row;
	return center;
}
//------------------------------------------------------------------
void EquilateralTriangle::draw(Board& board)const  //draw the triangle
{ 
	board.drawLine(m_ver0, m_ver1);
	board.drawLine(m_ver1, m_ver2);
	board.drawLine(m_ver2, m_ver0);
}
//------------------------------------------------------------
Rectangle EquilateralTriangle::getBoundingRectangle()const
{ //bounding the triangle with rectangle
	Vertex bottomLeft, topRight;
	if (m_ver2.isHigherThan(m_ver0))
	{
		bottomLeft.m_col = m_ver0.m_col;
		bottomLeft.m_row = m_ver0.m_row;
		topRight.m_col = m_ver1.m_col;
		topRight.m_row = m_ver2.m_row;
	}
	else
	{
		topRight.m_col = m_ver1.m_col;
		topRight.m_row = m_ver1.m_row;
		bottomLeft.m_col = m_ver0.m_col;
		bottomLeft.m_row = m_ver2.m_row;
	}

	return Rectangle(bottomLeft, topRight);
}
//---------------------------------------------------------
bool EquilateralTriangle::scale(double factor)
{   // scaling the triangle * factor
	if (factor < 0)
		return false;
	Vertex v0, v1, v2;
	v0 = m_ver0;
	v1 = m_ver1;
	v2 = m_ver2;
	double newBase, newHeight;
	Vertex center = getCenter();
	newBase = getLength() * factor;
	newHeight = getHeight() * factor;

	if (m_ver2.isHigherThan(m_ver0))
	{
		v0.m_col = center.m_col - (newBase / 2);
		v0.m_row = center.m_row - (newHeight / 2);
		v1.m_col = center.m_col + (newBase / 2);
		v1.m_row = center.m_row - (newHeight / 2);
		v2.m_col = m_ver2.m_col;
		v2.m_row = center.m_row + (newHeight / 2);
	}
	else {
		v0.m_col = center.m_col - (newBase / 2);
		v0.m_row = center.m_row + (newHeight / 2);
		v1.m_col = center.m_col + (newBase / 2);
		v1.m_row = center.m_row + (newHeight / 2);
		v2.m_col = m_ver2.m_col;
		v2.m_row = center.m_row - (newHeight / 2);
	}

	if (!v2.isValid() || !v0.isValid() || !v1.isValid())
		return false;
	m_ver0 = v0;
	m_ver1 = v1;
	m_ver2 = v2;
	return true;
}
//---------------------------------------------------------------------
