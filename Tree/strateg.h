#pragma once

#ifndef _STRATEG_H_
#define _STRATEG_H_

#include "items.h"
#include <memory>
#include <algorithm>

struct Operations_parametrs {
	std::vector<std::shared_ptr<Item>>& items;
	std::vector<std::shared_ptr<Item>>::iterator& it;
	std::vector<std::shared_ptr<Item>>::iterator& end;
};

struct Capture_operations_parametrs : Operations_parametrs {
	std::unordered_map<std::string, std::shared_ptr<Item>>& capture_groups;
};

class Operation_Strategy{
public:
	virtual void apply(const Operations_parametrs& param) const = 0;
};

class Dot_Operation_Strategy: public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param){
		auto& items = param.items;
                auto& it = param.it;
                auto& end = param.end;
		*(it) = std::make_shared<Dot_Node>(std::move(*(it+1)));
		items.erase(it+1);
		end--;
	}
};

class Quest_Operations_Strategy: public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param) const override {
		auto& items = param.items;
		auto& it = param.it;
		auto& end = param.end;

		*(it) = std::make_shared<Quest_Node>(std::move(*(it+1)));
		items.erase(it+1);
		it--;
		end--;
	}
};

class Plus_Operations_Strategy : public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param) const override {
		auto& items = param.items;
		auto& it = param.it;
		auto& end = param.end;

		*(it-1) = std::make_shared<Plus_Node>(std::move(*(it-1)));
		items.erase(it);
		it--;
		end--;
	}
};

class Or_Operations_Strategy : public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param) const override {
                auto& items = param.items;
                auto& it = param.it;
                auto& end = param.end;

		*(it) = std::make_shared<Or_Node>(std::move(*(it-1)), std::move(*(it+1)));
		items.erase(it+1);
		items.erase(it-1);
		it--;
		end-=2;
	}
};

class Concate_Operations_Strategy : public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param) const override {
                auto& items = param.items;
                auto& it = param.it;
                auto& end = param.end;

		*(it) = std::make_shared<Concate_Node>(std::move(*(it-1)), std::move(*(it)));
		items.erase(it-1);
		it--;
		end--;
	}
};

class CurBr_Operations_Strategy : public Operation_Strategy{
public:
	void apply(const Operations_parametrs& param) const override{
		auto& items = param.items;
        auto& begin = param.it;
        auto& end = param.end;
		auto close = std::find_if(begin, end, [](const std::shared_ptr<Item>& item)
			{
				auto a_node = std::dynamic_pointer_cast<A_Node>(item);
				return a_node && a_node->lit == '}';
			});
		std::string name;
		for(auto i = begin +1; i < close; ++i){
			auto a_node = std::dynamic_pointer_cast<A_Node>(*i);
			name.push_back(std::move(a_node->lit));
		}
		//std::cout << "\ncapt name is - " << name << " distance = " << (std::distance(begin, close) + 1) <<"\n";
		end -= (std::distance(begin, close) + 1);
		*(begin-1) = std::make_shared<CurBr_Node>(*(begin-1), std::move(name));
		items.erase(begin, close+1);
		begin--;
		//std::cout << "distance between begin and end is " << std::distance(begin, end) << std::endl;
	}
};

class Capture_Group_Operations_Strategy{
public:
	void apply(const Capture_operations_parametrs& params, bool is_call) const {
		auto& capture_groups = params.capture_groups;
		auto& begin = params.it;
		auto& end = params.end;
		auto& items = params.items;
		//std::cout << "\nbegin obrabotka\n";
		auto close = std::find_if(begin, end, [](const std::shared_ptr<Item>& item)
			{
				auto a_node = std::dynamic_pointer_cast<A_Node>(item);
				return a_node && a_node->lit == '>';
			});
		std::string name;
		for(auto i = begin +1; i != close; ++i){
			auto a_node = std::dynamic_pointer_cast<A_Node>(*i);
			name.push_back(std::move(a_node->lit));
		}
		//std::cout << "\ncapt name is - " << name << "\n";
		end -= (std::distance(begin, end) + 1);
		if(is_call) *close = std::make_shared<Capture_Group_Node>(capture_groups[name], name);
		else *close = std::make_shared<Capture_Group_Node>(nullptr, std::move(name));
		items.erase(begin, close);
		//std::cout <<"\nend of obrabotka\n";
	}
};

class Capture_Groupe_Activate_Operations_Strategy{
public:
	void apply(const Capture_operations_parametrs& param) const {
		auto& items = param.items;
		auto& capture_groups = param.capture_groups;
		auto& begin = param.it;
		auto& end = param.end;
		//std::cout << "capt begin - " << (*begin)->get_lit() << std::endl;
		//std::cout << "capt end - " << (*end)->get_lit() << std::endl;

		auto capture_group_item = std::dynamic_pointer_cast<Capture_Group_Node>(*begin);
		capture_group_item->child = std::move(*(begin + 1));
		capture_groups[capture_group_item->name] = capture_group_item->child;
		items.erase(begin + 1);
		end-=1;
	}
};
/*
void Apply_Operations(char symb, Operations_parametrs& param) {
	switch(symb){
		case '?':{
			Quest_Operations_Strategy strat;
			strat.apply(param);
			break;
		}
		case '+':{
			Plus_Operations_Strategy strat;
			strat.apply(param);
			break;
		}
		default :
		;
	}
};
*/
#endif
