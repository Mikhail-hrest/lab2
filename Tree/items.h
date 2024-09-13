#pragma once
#ifndef _ITEMS_H_
#define _ITEMS_H
#include <string>
#include <memory>

// '&' - is escape character

class Item {
public:
	virtual ~Item() = default;
	virtual char get_lit() const = 0;
};

class A_Node : public Item {
public:
	char lit;
	explicit A_Node(char symb) : lit(symb){};
	char get_lit() const override { return lit; }
};

class Single_Node : public Item {
public:
	std::shared_ptr<Item> child;
	explicit Single_Node(std::shared_ptr<Item> child) : child(std::move(child)) {};
};

class Dot_Node : public Single_Node{
public:
	explicit Dot_Node(std::shared_ptr<Item> child) : Single_Node(std::move(child)) {};
	char get_lit() const override {
		return '&';
	}
};

class Double_Node : public Item {
public:
	std::shared_ptr<Item> first_child;
	std::shared_ptr<Item> second_child;
	explicit Double_Node(std::shared_ptr<Item> first, std::shared_ptr<Item> second)
		: first_child(std::move(first)), second_child(std::move(second)) {};
};

class Or_Node : public Double_Node {
public:
	explicit Or_Node(std::shared_ptr<Item> left, std::shared_ptr<Item> right)
		: Double_Node(std::move(left), std::move(right)) {};
	char get_lit() const override{
		return '|';
	}
};

class Concate_Node : public Double_Node {
public:
	explicit Concate_Node(std::shared_ptr<Item> left, std::shared_ptr<Item> right) 
                : Double_Node(std::move(left), std::move(right)) {};
	char get_lit() const override {
		return '-';
	}
};

class Plus_Node : public Single_Node{
public:
	explicit Plus_Node(std::shared_ptr<Item> child) : Single_Node(std::move(child)) {};
	char get_lit() const override {
		return '+';
	}
};

class Quest_Node : public Single_Node{
public:
	explicit Quest_Node(std::shared_ptr<Item> child) : Single_Node(std::move(child)) {};
	char get_lit() const override{
		return '?';
	}
};

class Point_Node : public Item{
public:
	explicit Point_Node() = default;
	char get_lit() const override{
		return '.';
	}
};

class CurBr_Node : public Single_Node{
public:
	std::string name;
	explicit CurBr_Node(std::shared_ptr<Item> child, std::string cnt)
		: Single_Node(std::move(child)), name(cnt) {};
	char get_lit() const override {return '{';}
};

class Capture_Group_Node : public Single_Node{
public:
	std::string name;
	explicit Capture_Group_Node(std::shared_ptr<Item> child, std::string nm)
		: Single_Node(std::move(child)), name(nm) {};
	char get_lit() const override {
		return '<';
	}
};

#endif
