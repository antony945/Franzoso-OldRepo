#include "SDLclass.h"


double CCW(SDL_Point a, SDL_Point b, SDL_Point c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

long double CCWp(long double ax, long double ay, long double bx, long double by, long double cx, long double cy)
{
	return (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
}

int middle(int a, int b, int c) {
	int t;
	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	if (a <= c && c <= b) return 1;
	return 0;
}
long double middlep(long double a, long double b, long double c) {
	int t;
	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	if (a <= c && c <= b) return 1;
	return 0;
}


int intersect(line a, line b) {
	if ((CCW(a.s, a.e, b.s) * CCW(a.s, a.e, b.e) < 0) &&
		(CCW(b.s, b.e, a.s) * CCW(b.s, b.e, a.e) < 0)) return 1;

	if (CCW(a.s, a.e, b.s) == 0 && middle(a.s.x, a.e.x, b.s.x) && middle(a.s.y, a.e.y, b.s.y)) return 1;
	if (CCW(a.s, a.e, b.e) == 0 && middle(a.s.x, a.e.x, b.e.x) && middle(a.s.y, a.e.y, b.e.y)) return 1;
	if (CCW(b.s, b.e, a.s) == 0 && middle(b.s.x, b.e.x, a.s.x) && middle(b.s.y, b.e.y, a.s.y)) return 1;
	if (CCW(b.s, b.e, a.e) == 0 && middle(b.s.x, b.e.x, a.e.x) && middle(b.s.y, b.e.y, a.e.y)) return 1;

	return 0;
}

int intersectp(linep a, linep b) {
	if ((CCWp(a.sx, a.sy, a.ex, a.ey, b.sx, b.sy) * CCWp(a.sx, a.sy, a.ex, a.ey, b.ex, b.ey) < 0) &&
		(CCWp(b.sx, b.sy, b.ex, b.ey, a.sx, a.sy) * CCWp(b.sx, b.sy, b.ex, b.ey, a.ex, a.ey) < 0)) return 1;

	if (CCWp(a.sx, a.sy, a.ex, a.ey, b.sx, b.sy) == 0 && middlep(a.sx, a.ex, b.sx) && middlep(a.sy, a.ey, b.sy)) return 1;
	if (CCWp(a.sx, a.sy, a.ex, a.ey, b.ex, b.ey) == 0 && middlep(a.sx, a.ex, b.ex) && middlep(a.sy, a.ey, b.ey)) return 1;
	if (CCWp(b.sx, b.sy, b.ex, b.ey, a.sx, a.sy) == 0 && middlep(b.sx, b.ex, a.sx) && middlep(b.sy, b.ey, a.sy)) return 1;
	if (CCWp(b.sx, b.sy, b.ex, b.ey, a.ex, a.ey) == 0 && middlep(b.sx, b.ex, a.ex) && middlep(b.sy, b.ey, a.ey)) return 1;

	return 0;
}

float CalculateDistance(SDL_Point p1, SDL_Point p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

float angle(SDL_Point a, SDL_Point b) {
	return atan2(a.y - b.y, a.x - b.x) * 180 / (float)PI;
}

float slope(SDL_Point a, SDL_Point b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return dy / dx;

}

int intercepty(SDL_Point a, SDL_Point b) {
	return a.y - slope(a, b) * a.x;

}

SDL_Point endpoint(SDL_Point a, SDL_Point b, float new_x) {
	SDL_Point end;
	end.x = new_x;
	end.y = slope(a, b)*end.x + intercepty(a, b);
	return end;
}

SDL_Point interpoint(line a, line b)
{
	// Line AB represented as a1x + b1y = c1
	double a1 = a.e.y - a.s.y;
	double b1 = a.s.x - a.e.x;
	double c1 = a1*(a.s.x) + b1*(a.s.y);

	// Line CD represented as a2x + b2y = c2
	double a2 = b.e.y - b.s.y;
	double b2 = b.s.x - b.e.x;
	double c2 = a2*(b.s.x) + b2*(b.s.y);

	double determinant = a1*b2 - a2*b1;


	SDL_Point i;
	i.x = (b2*c1 - b1*c2) / determinant;
	i.y = (a1*c2 - a2*c1) / determinant;
	return i;

}

bool shortcut(line a, Sprite s, int index) {
	line b;
	b.s.x = s.collision_polygonx[index];
	b.s.y = s.collision_polygony[index];
	if (index != s.collision_polygonx.size() - 1) {
		b.e.x = s.collision_polygonx[index + 1];
		b.e.y = s.collision_polygony[index + 1];
	}
	else
	{
		b.e.x = s.collision_polygonx[0];
		b.e.y = s.collision_polygony[0];
	}
	if (intersect(a, b) == true) {
		return true;
	}
	return false;
}

bool SDLclass::linecheck(line a, vertexstruct v, int layer) {
	bool intersections = false;
	for (auto& ss : layers.at(layer).sprite) {
		for (int vv = 0; vv < ss.second.get()->collision_polygonx.size(); vv++) {
			if (v.sprite_name == ss.first) {
				if (vv != ss.second.get()->collision_polygonx.size() - 1) {
					if (vv != v.index && vv + 1 != v.index) {
						if (intersections == true) { return true; }
						if (intersections == false) {
							intersections = shortcut(a, *ss.second.get(), vv);
						}
					}
				}
				else
				{
					if (vv != v.index && 0 != v.index) {
						if (intersections == true) { return true; }
						if (intersections == false) {
							intersections = shortcut(a, *ss.second.get(), vv);
						}
					}
				}
			}
			else
			{
				if (intersections == true) { return true; }
				if (intersections == false) {
					intersections = shortcut(a, *ss.second.get(), vv);
				}
			}
		}
	}
	return intersections;
}


bool Polygon_point::is_left() {
	return x < succ->x;
}

Segment Polygon_point::line() {
	return{ { x,y },{ succ->x, succ->y } };
}

bool operator==(Polygon_point a, Polygon_point b) {
	return a.x == b.x && a.y == b.y && a.succ == b.succ;
}

bool operator==(Segment a, Segment b) {
	return (a.a == b.a && a.b == b.b) || (a.a == b.b && a.b == b.a);
}

bool operator<(Segment a, Segment b) {
	return a.a.y < b.a.y;
}
