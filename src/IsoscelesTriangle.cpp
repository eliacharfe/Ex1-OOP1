#include "Board.h"
#include "Vertex.h"
#include "macros.h"
#include "Utilities.h"
#include "IsoscelesTriangle.h"
#include "Rectangle.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
{
	if (!vertices[0].isValid() || !vertices[1].isValid() || !vertices[2].isValid()
		|| vertices[0].isHigherThan(vertices[1]) 
		|| vertices[1].isHigherThan(vertices[0])
		|| !vertices[2].isToTheRightOf(vertices[0])         // if not OK
		|| vertices[2].isToTheRightOf(vertices[1])  
		|| !doubleEqual(distance(vertices[0], vertices[2]) , distance(vertices[2], vertices[1])))

	{
		m_ver0 = getVertex(0);// get vertex 0
		m_ver1 = getVertex(1);// get vertex 1
		m_ver2 = getVertex(2);// get vertex 2
		getBaseLength();// get the base of the triangle
		getLegLength();// get the leg length of the triangle
		getHeight();// get height of the  triangle
		getArea();// get area of the  triangle
		getPerimeter();// get perimeter of the  triangle
		getCenter();// get the center of the triangle
	}
	else
	{ // if OK
		m_ver0 = vertices[0]; // update
		m_ver1 = vertices[1]; //update
		m_ver2 = vertices[2]; //update
		getBaseLength();// get the base of the triangle
		getLegLength();// get the leg length of the triangle
		getHeight();// get height of the triangle
		getArea();// get area of the triangle
		getPerimeter();// get perimeter of the  triangle
		getCenter();// get the center of the triangle
	}
}
//-------------------------------------------------------
IsoscelesTriangle::IsoscelesTriangle(const Vertex& v0, const Vertex& v1, double height)
{
	Vertex v2 = Vertex(v0.m_col + (distance(v0, v1) / 2), v0.m_row + (height / 2));
	if (!v0.isValid() || !v1.isValid() 
		|| v0.isHigherThan(v1) || v1.isHigherThan(v0)
		|| distance(v0, v2) != distance(v2, v1))
	{
		m_ver0 = getVertex(0);// get vertex 0
		m_ver1 = getVertex(1);// get vertex 0
		m_ver2 = getVertex(2);// get vertex 0
		getBaseLength();// get the base of the triangle
		getLegLength();// get the leg length of the triangle
		getHeight();// get height of the  triangle
		getArea();// get area of the triangle
		getPerimeter();// get perimeter of the  triangle
		getCenter();// get the center of the triangle
	}
	else
	{
		m_ver0 = v0;// update
		m_ver1 = v1;// update
		m_ver2 = v2;// update
		getBaseLength();// get the base of the triangle
		getLegLength();// get the leg length of the triangle
		getHeight();// get height of the  triangle
		getArea();// get area of the  triangle
		getPerimeter();// get perimeter of the triangle
		getCenter();// get the center of the triangle
	}
}
//-------------------------------------------------
Vertex IsoscelesTriangle::getVertex(int index) const // get a vertex
{
	Vertex vertice;
	if (index == V_0) // enum = 0
	{
		vertice.m_col = 20;
		vertice.m_row = 20;
	}
	else if (index == V_1) // enum = 1
	{
		vertice.m_col = 30;
		vertice.m_row = 20;
	}
	else if (index == V_2) // enum = 2
	{
		vertice.m_col = 25;
		vertice.m_row = 20 + sqrt(75);
	}
	return vertice;
}
//------------------------------------------------
double IsoscelesTriangle::getBaseLength()const// get the base of the triangle
{
	return abs(m_ver0.m_col - m_ver1.m_col);
}
//-------------------------------------------------
double IsoscelesTriangle::getLegLength()const
{// get the leg length of the triangle
	return abs(m_ver0.m_col - m_ver2.m_col);
}
//-----------------------------------------------------
double IsoscelesTriangle::getHeight()const // get height of the  triangle
{
	return abs(m_ver2.m_row - m_ver0.m_row);
}
//--------------------------------------------
double IsoscelesTriangle::getArea() const// get area of the  triangle
{
	return (( getBaseLength() * getHeight() ) / 2);
}
//---------------------------------------------------------
double IsoscelesTriangle::getPerimeter() const
{// get perimeter of the  triangle
	return ( (getLegLength() * 2) + getBaseLength());
}
//-------------------------------------------------------
Vertex IsoscelesTriangle::getCenter()const
{// get the center of the triangle
	Vertex center;
    center.m_col = m_ver1.m_col - (getBaseLength() / 2);
	center.m_row = (getHeight() / 2) + m_ver0.m_row;
	return center;
}
//------------------------------------------------------------------
void IsoscelesTriangle::draw(Board& board)const //draw the triangle
{
	board.drawLine(m_ver0, m_ver1);
	board.drawLine(m_ver1, m_ver2);
	board.drawLine(m_ver2, m_ver0);
}
//------------------------------------------------------------
Rectangle IsoscelesTriangle::getBoundingRectangle()const
{// bounding the triangle with  triangle
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
bool IsoscelesTriangle::scale(double factor)
{// scaling the triangle * factor
	if (factor < 0)
		return false;
	Vertex v0, v1, v2;
	v0 = m_ver0; v1 = m_ver1; v2 = m_ver2;

	Vertex center = getCenter();
	double newBase, newHeight;
	newBase = getBaseLength() * factor;
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