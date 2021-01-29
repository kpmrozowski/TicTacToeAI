#pragma once

struct Move {
	Move(){};
	Move(int s) : score{s}, win{s}, lose{s}, tie{s} {}
	~Move() {}
	int column{1}, row{1}, score{}, win{}, lose{}, tie{};
};
