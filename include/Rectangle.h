#pragma once
#include "Board.h"

enum num_vertex_t { V_0, V_1, V_2 };

class Rectangle
{
public:
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);//c-tor
	Rectangle(const  Vertex vertices[2]);//c-tor
	Rectangle(double x0, double y0, double x1, double y1);//c-tor
	Rectangle(const Vertex& center, double width, double height);//c-tor

	Vertex getBottomLeft() const; // get bottom left vertex
	Vertex getTopRight()const;// get top right vertex

	double getHeight() const;// get height of the rectangle
	double getWidth() const;// get the width of the rectangle
	double getArea() const;// get area of the rectangle
	double getPerimeter() const;// get the perimeter  of the rectangle
	Vertex getCenter()const;// get the center  of the rectangle

	void draw(Board& board)const; // draw the rectangle
	Rectangle getBoundingRectangle()const; // return rectangle 
	bool scale(double factor); // retangle * factor

private:
	Vertex m_bottomLeft; // p2 bottom left vertex
	Vertex m_topRight; // p2 top right vertex

	Vertex m_center; // p2 center

	Vertex setBottomLeft_default()const; // default bottom left
	Vertex setTopRight_default()const; // default top right
};


