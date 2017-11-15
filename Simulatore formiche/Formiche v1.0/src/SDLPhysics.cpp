#include "SDLclass.h"

Vettore Sprite::resultant() {
	Vettore resultant{};
	for (auto i : forces) {
		resultant += i.second;
	}
	return resultant;

}

void Sprite::updateVelocity(std::chrono::duration<long double> delta_t) {
	velocity += resultant();
	velocity *= delta_t.count();
	velocity /= mass;
}

void Sprite::updatePos(chrono::duration<long double> delta_t, const Vettore& old_v)
{
	Vettore position{ x, y };
	Vettore average_vel = (velocity + old_v) / 2;
	position += average_vel * delta_t.count();
	old_x = x;
	old_y = y;
	x = position.x;
	y = position.y;
}

pair<map<string, Vettore>::iterator, bool> Sprite::applyForce(Vettore v, string key) {
	updateSpritePosition();
	return forces.insert(pair<string, Vettore>(key, v));
}

map<string, Vettore>::size_type Sprite::removeForce(string key) {
	updateSpritePosition();
	return forces.erase(key);
}

void Sprite::updateSpritePosition() {
	auto delta_t = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - last_update);
	Vettore old_v(velocity);
	updateVelocity(delta_t);
	updatePos(delta_t, old_v);
	updatePolygonPosition();
	last_update = chrono::steady_clock::now();
}


void Sprite::insertPolygonVertex(int vertex_index, SDL_Point new_pos) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	collision_polygonx.insert(it, new_pos.x);
	collision_polygony.insert(it2, new_pos.y);
}

void Sprite::insertPolygonVertexArray(int vertex_index, vector<SDL_Point> new_pos) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	std::vector<int> x;
	std::vector<int> y;
	for (int i = 0; i < new_pos.size(); i++) {
		x.push_back(new_pos[i].x);
		y.push_back(new_pos[i].y);
	}
	collision_polygonx.insert(it, x.begin(), x.end());
	collision_polygony.insert(it2, y.begin(), y.end());
	x.clear();
	y.clear();
	new_pos.clear();
}

void Sprite::movePolygonVertex(int vertex_index, SDL_Point new_pos) {
	collision_polygonx.at(vertex_index) = new_pos.x;
	collision_polygony.at(vertex_index) = new_pos.y;
}

void Sprite::removePolygonVertexArray(int vertex_index, int number_of_vertices) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	collision_polygonx.erase(it, it + number_of_vertices);
	collision_polygony.erase(it2, it2 + number_of_vertices);
}


void Sprite::changePolygonShape(std::vector<SDL_Point> points) {
	collision_polygonx.clear();
	collision_polygony.clear();
	for (int i = 0; i < points.size(); i++) {
		collision_polygonx.push_back(x + points.at(i).x);
		collision_polygony.push_back(y + points.at(i).y);
	}
}

void Sprite::updatePolygonPosition() {

	for (int i = 0; i < collision_polygonx.size(); i++) {
		collision_polygonx[i] += x - old_x;

	}
	for (int i = 0; i < collision_polygony.size(); i++) {
		collision_polygony[i] += y - old_y;

	}
}

void SDLclass::raycast(int layer, string light_name) {
	SDL_Point light_center{ layers.at(layer).lights.at(light_name).x ,layers.at(layer).lights.at(light_name).y };
	vector<vertexstruct> vertices, final_vertices;
	vector<long double> polygon_vertex_x, polygon_vertex_y;
	for (auto& s : layers.at(layer).sprite) {
		for (int v = 0; v < s.second.get()->collision_polygonx.size(); v++) {
			vertexstruct t;
			t.vertex.x = s.second.get()->collision_polygonx[v];
			t.vertex.y = s.second.get()->collision_polygony[v];
			t.angle = angle(light_center, t.vertex);
			t.index = v;
			t.sprite_name = s.first;
			vertices.push_back(t);
		}
	}
	std::sort(vertices.begin(), vertices.end(), [](vertexstruct val1, vertexstruct val2) {return val1.angle > val2.angle; });
	for (auto& v : vertices) {
		bool intersections = false;
		line a{ light_center,v.vertex }, b;
		intersections = linecheck(a, v, layer);
		if (intersections == false) {
			SDL_Point old_ae = a.e;
			if (a.e.x < light_center.x) {
				a.e = endpoint(light_center, a.e, -10000);
			}
			else
			{
				a.e = endpoint(light_center, a.e, 10000);
			}
			bool Loop = true;
			int intersections_finds = 0;
			vector<vertexstruct> intersection;
			map<string, shared_ptr<Sprite>>::iterator it;
			for (it = layers.at(layer).sprite.begin(); it != layers.at(layer).sprite.end() && Loop == true; ++it) {
				for (int vv = 0; vv < it->second.get()->collision_polygonx.size() && Loop == true; vv++) {
					if (v.sprite_name == it->first) {
						if (vv != it->second.get()->collision_polygonx.size() - 1) {
							if (vv != v.index && vv + 1 != v.index) {
								if (shortcut(a, *it->second.get(), vv) == true) {
									if (v.sprite_name != it->first) {
										line b;
										b.s.x = it->second.get()->collision_polygonx.at(vv);
										b.s.y = it->second.get()->collision_polygony.at(vv);
										if (vv != it->second.get()->collision_polygonx.size() - 1) {
											b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
											b.e.y = it->second.get()->collision_polygony.at(vv + 1);
										}
										else
										{
											b.e.x = it->second.get()->collision_polygonx[0];
											b.e.y = it->second.get()->collision_polygony[0];
										}
										vertexstruct o;
										o.vertex = interpoint(a, b);
										o.distance = CalculateDistance(light_center, o.vertex);
										o.sprite_name = v.sprite_name;
										if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
											intersection.push_back(o);
											intersections_finds++;
										}
									}
									else
									{
										if (intersection.size() >= intersections_finds) {
											intersection.erase(intersection.end() - intersections_finds, intersection.end());
										}
										Loop = false;
									}
								}
							}
						}
						else
						{
							if (vv != v.index && 0 != v.index) {
								if (shortcut(a, *it->second.get(), vv) == true) {
									if (v.sprite_name != it->first) {
										line b;
										b.s.x = it->second.get()->collision_polygonx.at(vv);
										b.s.y = it->second.get()->collision_polygony.at(vv);
										if (vv != it->second.get()->collision_polygonx.size() - 1) {
											b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
											b.e.y = it->second.get()->collision_polygony.at(vv + 1);
										}
										else
										{
											b.e.x = it->second.get()->collision_polygonx[0];
											b.e.y = it->second.get()->collision_polygony[0];
										}
										vertexstruct o;
										o.vertex = interpoint(a, b);
										o.distance = CalculateDistance(light_center, o.vertex);
										o.sprite_name = v.sprite_name;
										if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
											intersection.push_back(o);
											intersections_finds++;
										}
									}
									else
									{
										if (intersection.size() >= intersections_finds) {
											intersection.erase(intersection.end() - intersections_finds, intersection.end());
										}
										Loop = false;
									}
								}
							}
						}
					}
					else
					{
						if (shortcut(a, *it->second.get(), vv) == true) {
							if (v.sprite_name == it->first) { break; }
							line b;
							b.s.x = it->second.get()->collision_polygonx.at(vv);
							b.s.y = it->second.get()->collision_polygony.at(vv);
							if (vv != it->second.get()->collision_polygonx.size() - 1) {
								b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
								b.e.y = it->second.get()->collision_polygony.at(vv + 1);
							}
							else
							{
								b.e.x = it->second.get()->collision_polygonx[0];
								b.e.y = it->second.get()->collision_polygony[0];
							}
							vertexstruct o;
							o.vertex = interpoint(a, b);
							o.distance = CalculateDistance(light_center, o.vertex);
							o.sprite_name = it->first;
							if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
								intersection.push_back(o);
								intersections_finds++;
							}
						}
					}
				}
			}
			sort(intersection.begin(), intersection.end(), [](vertexstruct v1, vertexstruct v2) {
				return v1.distance < v2.distance;
			});
			if (intersection.size() > 0) {
				a.e = intersection.at(0).vertex;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				SDL_Point aa{ polygon_vertex_x.at(polygon_vertex_x.size() - 1) ,polygon_vertex_y.at(polygon_vertex_x.size() - 1) };
				vertexstruct t;
				t.vertex = aa;
				t.sprite_name = intersection.at(0).sprite_name;
				if (final_vertices.size() > 0) {
					if (t.sprite_name == final_vertices.at(final_vertices.size() - 1).sprite_name) {



						t.angle = angle(light_center, t.vertex);
						t.priority = 1;
						final_vertices.push_back(t);
					}
					else
					{
						t.angle = angle(light_center, t.vertex);
						t.priority = 0;
						final_vertices.push_back(t);
					}
				}
				else
				{
					t.angle = angle(light_center, t.vertex);
					t.priority = 0;
					final_vertices.push_back(t);
				}
				a.e = old_ae;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				aa.x = polygon_vertex_x.at(polygon_vertex_x.size() - 1);
				aa.y = polygon_vertex_y.at(polygon_vertex_x.size() - 1);
				t.vertex = aa;
				t.angle = angle(light_center, t.vertex);
				t.sprite_name = v.sprite_name;
				if (final_vertices.at(final_vertices.size() - 1).priority == 1) {
					t.priority = 0;
				}
				else {
					t.priority = 1;

				}
				final_vertices.push_back(t);
			}
			else
			{
				a.e = old_ae;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				SDL_Point aa;
				aa.x = polygon_vertex_x.at(polygon_vertex_x.size() - 1);
				aa.y = polygon_vertex_y.at(polygon_vertex_x.size() - 1);
				vertexstruct t;
				t.vertex = aa;
				t.angle = angle(light_center, t.vertex);
				t.sprite_name = v.sprite_name;
				t.priority = 1;
				final_vertices.push_back(t);
			}
		}
	}
	vertices.clear();
	std::sort(final_vertices.begin(), final_vertices.end(), [](vertexstruct val1, vertexstruct val2) {
		if (val1.angle - val2.angle <= 0.25 && val1.angle - val2.angle >= -0.25) {
			return val1.priority < val2.priority;
		}
		else {
			return val1.angle < val2.angle;
		}
	});
	polygon_vertex_x.clear();
	polygon_vertex_y.clear();
	for (auto& v : final_vertices) {
		polygon_vertex_x.push_back(v.vertex.x);
		polygon_vertex_y.push_back(v.vertex.y);
	}
	final_vertices.clear();
	filledPolygonRGBA(renderer, polygon_vertex_x, polygon_vertex_y, polygon_vertex_x.size(), layers.at(layer).lights.at(light_name).r, layers.at(layer).lights.at(light_name).b, layers.at(layer).lights.at(light_name).g, layers.at(layer).lights.at(light_name).intensity, HEIGHT);
	polygon_vertex_x.clear();
	polygon_vertex_y.clear();
}


bool rect_collision(SDL_Rect a, SDL_Rect b) {
	return !(a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y);
}


bool point_inside_polygon(Polygon_point point, const Sprite& polygon) {
	Segment s{ { -10e9, -10e9 }, point };
	int count{};
	for (int i{}; i < polygon.collision_polygonx.size(); ++i) {
		if (i != polygon.collision_polygonx.size() - 1) {
			if (intersectp({ polygon.collision_polygonx[i], polygon.collision_polygony[i] , polygon.collision_polygonx[i + 1], polygon.collision_polygony[i + 1] }, s))
				count++;
		}
		else {
			if (intersectp({ polygon.collision_polygonx[i], polygon.collision_polygony[i] , polygon.collision_polygonx[0], polygon.collision_polygony[0] }, s))
				count++;
		}
	}
	return count % 2;
}

bool polygon_collision(const Sprite& a, const Sprite& b) {
	if (point_inside_polygon({ a.collision_polygonx[0], a.collision_polygony[0] }, b) || point_inside_polygon({ b.collision_polygonx[0], b.collision_polygony[0] }, a))
		return true;
	vector<Polygon_point> points;

	int i{};
	for (; i < a.collision_polygonx.size(); ++i) {
		points.push_back({ a.collision_polygonx[i], a.collision_polygony[i] });
		if (i != 0)
			points[i - 1].succ = &points[i];
		else if (i == a.collision_polygonx.size() - 1)
			points[i].succ = &points[0];
	}
	for (; i < b.collision_polygonx.size(); ++i) {
		points.push_back({ b.collision_polygonx[i], b.collision_polygony[i] });
		if (i != a.collision_polygonx.size())
			points[i - 1].succ = &points[i];
		else if (i == a.collision_polygonx.size() + b.collision_polygonx.size() - 1)
			points[i].succ = &points[a.collision_polygonx.size()];
	}
	sort(points.begin(), points.end(), [](Polygon_point a, Polygon_point b) {return a.x < b.x; });
	set<Segment> lines;
	for (int i{}; i < a.collision_polygonx.size() + b.collision_polygonx.size(); ++i) {
		if (points[i].is_left()) {
			lines.insert(points[i].line());
			auto current_line{ lines.find(points[i].line()) };
			if (current_line != lines.begin()) {
				if (intersectp(points[i].line(), *prev(current_line)))//ERRORE QUA
					return true;
			}
			if (current_line != prev(lines.end())) {
				if (intersectp(points[i].line(), *(next(current_line))))
					return true;
			}
		}
		else {
			auto current_line{ lines.find(points[i].line()) };
			if (current_line != lines.begin() && current_line != prev(lines.end())) {
				if (intersectp(*(prev(current_line)), *(next(current_line))))
					return true;
			}
			lines.erase(points[i].line());
		}
	}
	return false;
}


void Sprite::teleport(int new_x, int new_y) {
	old_x = x;
	old_y = y;
	x = (long double)new_x;
	y = (long double)new_y;
	updatePolygonPosition();
}



void LightSource::teleport(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}
