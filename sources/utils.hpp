#ifndef UTILS_HPP
#define UTILS_HPP

enum class Direction {
	NONE, UP, DOWN, RIGHT, LEFT
};

struct AABB {
	double xmin, xmax, ymin, ymax;

	AABB(double x, double y, double w, double h):
		xmin(x), xmax(x + w), ymin(y), ymax(y + h) {
	}

	bool collideWith( const AABB &other) const{
		return 
			xmin < other.xmax &&
			xmax > other.xmin &&
			ymin < other.ymax &&
			ymax > other.ymin;
	}

};

#endif