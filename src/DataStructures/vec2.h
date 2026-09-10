#pragma once

struct vec2 {
	float x;
	float y;

	vec2() { x = 0; y = 0; };
	vec2(float x, float y) { this->x = x; this->y = y; };
	
	vec2 operator+ (const vec2& other) const { return vec2( this->x + other.x, this->y + other.y ); }
	vec2 operator- (const vec2& other) const { return vec2( this->x - other.x, this->y - other.y ); }
	vec2 operator* (const float& value) const { return vec2( this->x * value, this->y * value ); }
	vec2 operator/ (const float& value) const { return vec2( this->x / value, this->y / value ); }

	vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this;	}
	bool operator== (const vec2& other) const { return this->x == other.x && this->y == other.y; }

};