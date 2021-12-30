#include "Geometry.h"
#include <cmath>
using namespace std;

// ============ Shape class =================

Shape::Shape() {} // REMOVE ME

Shape::Shape(int d){
	// IMPLEMENT ME
	if(d<0) throw std::invalid_argument("the depth is less than 0");
	
	  d_ = d;
	
}

bool Shape::setDepth(int d) {
	// IMPLEMENT ME
	if(d<0){
		return false;
	}
	 d_ = d;
	return true; // dummy
}

int Shape::getDepth() const {
	// IMPLEMENT ME
	return d_; // dummy
}

int Shape::dim() const {
	// IMPLEMENT ME
	return dim_; // dummy
}

void Shape::translate(float x, float y) {
	// IMPLEMENT ME
	x_+=x;
	y_+=y;
}

void Shape::rotate() {
	// IMPLEMENT ME
}

void Shape::scale(float f) {
	// IMPLEMENT ME
}

bool Shape::contains(const Point& p) const {
	// IMPLEMENT ME
	if((p.getX() == x_)&&(p.getY()==y_)){
		return true;
	}
	return false; // dummy
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d){
	// IMPLEMENT ME
	 x_ = x;
	 y_ = y; 
	 dim_ = 0;
}

float Point::getX() const {
	// IMPLEMENT ME
	return x_; // dummy
}

float Point::getY() const {
	// IMPLEMENT ME
	return y_; // dummy
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q): Shape(p.getDepth()), p_(p), q_(q) {
	// IMPLEMENT ME
	dim_ = 1;
}

float LineSegment::getXmin() const {
	// IMPLEMENT ME
	if(p_.getX()> q_.getX()){
		return q_.getX();
	}
	return p_.getX(); // dummy
}

float LineSegment::getXmax() const {
	// IMPLEMENT ME
		if(q_.getX()> p_.getX()){
		return q_.getX();
	}
	return p_.getX(); // dummy
}

float LineSegment::getYmin() const {
	// IMPLEMENT ME
		if(p_.getY()> q_.getY()){
		return q_.getY();
	}
	return p_.getY(); // dummy
}

float LineSegment::getYmax() const {
	// IMPLEMENT ME
			if(q_.getY()> p_.getY()){
		return q_.getY();
	}
	return p_.getY(); // dummy
}

float LineSegment::length() const {
	// IMPLEMENT ME
	float yLength = (getYmax()-getYmin());
	float xLength = (getXmax()-getXmin());
	float len = sqrt((yLength*yLength)+(xLength*xLength));

	return len; // dummy
}

void LineSegment::translate(float x, float y) {
	// IMPLEMENT ME		
	p_.translate(x,y);
	q_.translate(x,y);
	
}

void LineSegment::rotate(){

	if(getXmax() == getXmin()){
		int center = (getYmax()-getYmin())/2;
		if(p_.getY() == getYmax()){
			p_.translate(-center, -center);
			q_.translate(center, center);
		}
		else{
			q_.translate(-center, -center);
			p_.translate(center, center);
		}
	}

	else{
		int center = (getXmax()-getXmin())/2;
		if(p_.getX() == getXmax()){
			p_.translate(-center, -center);
			q_.translate(center, center);
		}
		else{
			q_.translate(-center, -center);
			p_.translate(center, center);
		}
	}
}

bool LineSegment::contains(Point p){
	if(getYmax() == getYmin()){
		for(int i = getXmin(); i<= getXmax(); i++){
			if((p.getY() == getYmax())&&(p.getX()==i)){
				return true;
			}
		}			
	}
	else{
		for(int i = getYmin(); i<= getYmax(); i++){
			if((p.getX() == getXmax())&&(p.getY()==i)){
				return true;
			}
		}
	}
	return false;
}

void LineSegment::scale(float f){
	 f = (length()*(f-1))/2;
	if(getYmax() == getYmin()){
		if(p_.getX()>q_.getX()){
			p_.translate(f,0);
			q_.translate(-f,0);
		}
		else{
			q_.translate(f,0);
			p_.translate(-f,0);
		}
	}
	else{
		if(p_.getY()>q_.getY()){
			p_.translate(0,f);
			q_.translate(0,-f);
		}
		else{ 
			q_.translate(0,f);
			p_.translate(0,-f);
		}
	}
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(){} // REMOVE ME

TwoDShape::TwoDShape(int d): Shape(d){
	// IMPLEMENT ME
	dim_ = 2;


}

float TwoDShape::area() const {
	// IMPLEMENT ME
	// dummy
	return length_*height_;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q): TwoDShape(p.getDepth()), p_(p),q_(q) {
	// IMPLEMENT ME
	Point px1 = Point(getXmax(),getYmin());
	Point px2 = Point(getXmin(),getYmin());
	Point py1 = Point(getXmin(),getYmax());
	Point py2 = Point(getXmin(),getYmin());
	LineSegment horizon = LineSegment(px1,px2);
	LineSegment vertical = LineSegment(py1,py2);
	length_ = horizon.length();
	height_ = vertical.length();
}

float Rectangle::getXmin() const {
	// IMPLEMENT ME
	if(p_.getX()>q_.getX()){
		return q_.getX();
	}
	return p_.getX(); // dummy
}

float Rectangle::getYmin() const {
	// IMPLEMENT ME
		if(p_.getY()>q_.getY()){
		return q_.getY();
	}
	return p_.getY(); // dummy
}

float Rectangle::getXmax() const {
	if(p_.getX()<q_.getX()){
		return q_.getX();
	}
	return p_.getX(); // dummy
}

float Rectangle::getYmax() const {
	if(p_.getY()<q_.getY()){
		return q_.getY();
	}
	return p_.getY();// dummy
}
bool Rectangle::contains(Point p){
	for(int i = getXmin(); i<=getXmax(); i++){
		for(int j = getYmin(); j<=getYmax(); j++){
			if((p.getX()==i)&&(p.getY()==j)){
				return true;
			}
		}
	}
	return false;
}

void Rectangle::translate(float x, float y){
	p_.translate(x,y);
	q_.translate(x,y);
}

void Rectangle::scale(float f){
	Point px1 = Point(getXmax(),getYmin());
	Point px2 = Point(getXmin(),getYmin());
	Point py1 = Point(getXmin(),getYmax());
	Point py2 = Point(getXmin(),getYmin());
	LineSegment horizon = LineSegment(px1,px2);
	LineSegment vertical = LineSegment(py1,py2);
	horizon.scale(f);
	vertical.scale(f);
	if(p_.getX()>q_.getX()){
		float xmax = horizon.getXmax()-p_.getX();
		float xmin = horizon.getXmin()-q_.getX();
		float ymax = vertical.getYmax()-p_.getY();
		float ymin = vertical.getYmin()-q_.getY();
		p_.translate(xmax,ymax);
		q_.translate(xmin,ymin);
	}
	else{
		float xmax = horizon.getXmax()-q_.getX();
		float xmin = horizon.getXmin()-p_.getX();
		float ymax = vertical.getYmax()-q_.getY();
		float ymin = vertical.getYmin()-p_.getY();
		q_.translate(xmax,ymax);
		p_.translate(xmin,ymin);
	}
	

}

void Rectangle::rotate(){
	float xcen = (getXmax()-getXmin())/2;
	float ycen = (getYmax()-getYmin())/2;
	
	// edithib
	if(p_.getX()>q_.getX()){
		float xmax = (getXmax()+(ycen - xcen))-p_.getX();
		float xmin = (getXmin()-(ycen-xcen))-q_.getX();
		float ymax = (getYmax()+(xcen - ycen))-p_.getY();
		float ymin = (getYmin()-(xcen-ycen))-q_.getY();
		p_.translate(xmax,ymax);
		q_.translate(xmin,ymin);
	}
	else{
		float xmax = (getXmax()+(ycen - xcen))-q_.getX();
		float xmin = (getXmin()-(ycen-xcen))-p_.getX();
		float ymax = (getYmax()+(xcen - ycen))-q_.getY();
		float ymin = (getYmin()-(xcen-ycen))-p_.getY();
		q_.translate(xmax,ymax);
		p_.translate(xmin,ymin);
	}

	//edithb
}

/*float Rectangle::area(){
	Point px1 = Point(getXmax(),getYmin());
	Point px2 = Point(getXmin(),getYmin());
	Point py1 = Point(getXmin(),getYmax());
	Point py2 = Point(getXmin(),getYmin());
	LineSegment horizon = LineSegment(px1,px2);
	LineSegment vertical = LineSegment(py1,py2);
	float answer = horizon.length()*vertical.length();
	return answer;
}*/

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) :TwoDShape(c.getDepth()), c_(c), r_(r) {
	// IMPLEMENT ME
	length_ = r_;
	height_ = PI*r;
}

float Circle::getX() const {
	// IMPLEMENT ME
	return c_.getX(); // dummy
}

float Circle::getY() const {
	// IMPLEMENT ME
	return c_.getY(); // dummy
}

float Circle::getR() const {
	// IMPLEMENT ME
	return r_; // dummy
}

bool Circle::contains(Point p){
	LineSegment radi = LineSegment(c_,p);
	if(radi.length()<=r_){
		return true;
	}
	return false;
}
void Circle::rotate(){
	return;
}

void Circle::translate(float x, float y){
	c_.translate(x,y);

}

void Circle::scale(float f){
	r_ *= f;

}

/*float Circle::area(){
	float answer = (r_*r_)*PI;
	return answer;
}*/

// ================= Scene class ===================

Scene::Scene() {
	// IMPLEMENT ME
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	// IMPLEMENT ME
}

void Scene::setDrawDepth(int depth) {
	// IMPLEMENT ME
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	// IMPLEMENT ME
	return out;
}
