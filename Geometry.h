#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <memory>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Point; // forward declaration

class Shape {

public:
	// Default constructor, just to make this release version compilable.
	// If your implementation is correct this should be removed
	Shape();

	// Constructor specifying the depth of the object.
	// If d is negative, throw a std::invalid_argument exception.
	Shape(int d);

	// Set depth of object to d. If d is negative, return false and
	// do not update depth. Otherwise return true
	virtual bool setDepth(int d);

	// Return the depth of object
	int getDepth() const;
	

	// Return the dimension of the object (0, 1 or 2)
	int dim() const;

	// Translate the object horizontally by x and vertically by y
	virtual void translate(float x, float y);

	// Rotate the object 90 degrees around its centre
	virtual void rotate()= 0;

	// Scale the object by a factor f relative to its centre.
	// If f is zero or negative, throw a std::invalid-argument exception.
	virtual void scale(float f);

	// Return true if the object contains p and false otherwise.
	//bool contains(const Point& p) const;
	virtual bool contains(Point p) ;

	// the constant pi
	static constexpr double PI = 3.1415926;

protected:
	int d_;
	float x_;
	float y_;
	float dim_;

private:
	// add any protected/private member variables you need
	
};

class Point : public Shape {

public:
	// Constructor. Depth defaults to 0
	Point(float x, float y, int d=0);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	virtual void rotate(); 
	virtual bool contains(Point p); 

private:
	// add any member variables you need
	

};
class LineSegment : public Shape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x- and
	// y-coordinate, or if the line is not axis-aligned, throw a
	// std::invalid_argument exception
	LineSegment(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;
	void translate(float x, float y);
	virtual void rotate();
	virtual bool contains(Point p);
	virtual void scale(float f);

	// Return the length of the line segment
	float length() const;

private:
	// add any member variables you need
	Point p_;
	Point q_;
};

class TwoDShape : public Shape {

public:
	// Default constructor.
	// Similar comment to Student default constructor applies
	TwoDShape();

	// Constructor specifying the depth d
	TwoDShape(int d);

	// Return the area of the object
	virtual float area() const;

protected:
float length_;
float height_;
private:
	// add any protected/private member variables you need
	
};

class Rectangle : public TwoDShape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x-
	// and/or y-coordinate, throw a std::invalid_argument exception
	Rectangle(const Point& p, const Point& q);


	// Return basic information (see assignment page)
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;
	void translate(float x, float y);
	void rotate();
	bool contains(Point p);
	void scale(float f);
	float area();
	

private:
	// add any member variables you need
	Point p_;
	Point q_;


};

class Circle : public TwoDShape {

public:
	// Constructor.
	// If r is zero or negative, throw a std::invalid-argument exception.
	Circle(const Point& c, float r);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	float getR() const;
	void translate(float x, float y);
	void rotate();
	bool contains(Point p);
	void scale(float f);
	float area();
	

private:
	// add any member variables you need
	Point c_;
	float r_;
};


class Scene {

public:
	// Constructor
	Scene();

	// Add the pointer to the collection of pointers stored
	void addObject(std::shared_ptr<Shape> ptr);
	// Set the drawing depth to d
	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:
	// add any member variables you need
	vector<shared_ptr<Shape>> ptr_;

	// Draw objects as specified in the assignment page
friend std::ostream& operator<<(std::ostream& out, const Scene& s);
};

#endif /* GEOMETRY_H_ */