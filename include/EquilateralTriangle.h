#pragma once
#include "Board.h"
#include "Rectangle.h"

class EquilateralTriangle
{
public:
	EquilateralTriangle(const Vertex vertices[3]);//c-tor
	
	Vertex getVertex(int index) const; // get vertex
	double getLength()const; // get leg length
	double getHeight()const;// get height of the triangle
	double getArea() const; // get area of the triangle
	double getPerimeter() const;// get perimeter of the triangle
	Vertex getCenter()const;// get center of the triangle

	void draw(Board& board)const; //draw the triangle
	Rectangle getBoundingRectangle()const; //bounding the triangle with rectangle
	bool scale(double factor);// scaling the triangle * factor

private:
	Vertex m_ver0; // vertex 0
	Vertex m_ver1; // vertex 1
	Vertex m_ver2; // vertex 2
};