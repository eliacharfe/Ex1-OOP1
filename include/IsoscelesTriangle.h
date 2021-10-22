#pragma once
#include "Board.h"
#include "Rectangle.h"

class IsoscelesTriangle
{
public:
	IsoscelesTriangle(const Vertex vertices[3]);// c-tor
	IsoscelesTriangle(const Vertex& v0, const Vertex& v1, double height);//c-tor

	Vertex getVertex(int index) const;// get a vertex
	double getBaseLength()const;// get the base of the triangle
	double getLegLength()const;// get the leg length of the triangle
	double getHeight()const;// get height of the tritangle
	double getArea() const; // get area of the triangle
	double getPerimeter() const;// get perimeter of the tritangle
	Vertex getCenter()const;// get the center of the triangle

	void draw(Board& board)const; //draw the triangle
	Rectangle getBoundingRectangle()const; // bounding the triangle with rectangle
	bool scale(double factor);// scaling the triangle * factor

private:
	Vertex m_ver0; // vertex 0
	Vertex m_ver1; // vertex 1
	Vertex m_ver2; // vertex 2
};
