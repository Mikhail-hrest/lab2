#pragma once
#ifndef _NFA_H_
#define _NFA_H_

#include "../Tree/STree.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct State;

//e-переход - char(0)
struct trans{
        char lit;
        State* out;
};



struct State {
	trans* out1;
	trans* out2;
	void add_trans(State& state, char lit){
		trans* new_trans = new trans;
		new_trans->lit = lit;
		new_trans->out = &state;
		if(out1 == nullptr) out1 = new_trans;
		else out2 = new_trans;
	}
	void add_trans(trans& tr){
		if(out1 == nullptr) out1 = &tr;
		else out2 = &tr;
	}
	State(trans* o1 = nullptr, trans* o2 = nullptr)
		: out1(o1), out2(o2) {};
};



struct Fragment{
	State* start;
	State* finish;
	Fragment(State *st = nullptr, State *fin = nullptr)
		: start(st), finish(fin) {};
};





class NFA{
public:
	Fragment* graph;
	std::vector<State*> states;
	std::vector<char> matrix;
	NFA() = default;
	NFA(const Synt_Tree& tree);
	~NFA(){
		for(auto i: states){
			if(i->out1 != nullptr) delete i->out1;
			if(i->out2 != nullptr) delete i->out2;
			delete i;
		}
	}
	void show();
	//std::vector<std::shared_ptr<Fragment>> capture_groups;
private:
	Fragment* make_fragment(std::shared_ptr<Item> item, std::vector<State*>& states);
};




void add_show(std::vector<char>& matrix, std::vector<State*>& states){
	int x = 0, y = 0, size = states.size();
	for(auto it_x : states){
		y=0;
		for(auto it_y : states){
			State* x_s = it_x;
			trans* tr1 = x_s->out1;
			trans* tr2 = x_s->out2;
			if(tr1 != nullptr){
				if(tr1->out == it_y){
					matrix[x+size*y] = tr1->lit;
					++y;
					continue;
				}
			}
			if(tr2 != nullptr){
				if(tr2->out == it_y){
					matrix[x+size*y] = tr2->lit;
					++y;
					continue;
				}
			}
			matrix[x+size*y] = '0';
			++y;
		}
		++x;
	}
	std::cout << std::endl;
	std::cout << "  ";
	for(int i = 0; i < size; ++i){
		if(i < 9)std:: cout << " " << i+1 << "  ";
		else std::cout << " " << i+1 << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < size; ++i){
		std::cout << i+1 << ") ";
		for(int j = 0; j < size; ++j){
			std::cout << matrix[i+size*j] << " | ";
		}
		std::cout << std::endl;
	}
}




void NFA::show(){
	//std::vector<char> matrix;
	matrix.reserve(states.size()*states.size());
	//std::cout << "\nbeginig os good, but " << (graph->start == nullptr) << "\n";
	if(graph->start == nullptr){
		std::cout << "\n===NFA is empty===\n";
		return ;
	}
	std::cout << "\n\n\n                 <===  NFA  ===>"; 
	add_show(matrix, states);
	int ind = 1;
	for(auto it : states){
		if(it == graph->start) std::cout << "\nStart is " << ind;
		if(it == graph->finish) std::cout << "\nEnd is " << ind;
		++ind;
	}
	//std::cout << "\nsize of set = " << states.size() << std::endl;
}



NFA::NFA(const Synt_Tree& tree){
	std::shared_ptr<Item> root = tree.root;
	this->graph = make_fragment(std::shared_ptr<Item>(root), states);
	//show();
	//std::cout << "\nsize of set = " << states.size() << std::endl;
}



Fragment* NFA::make_fragment(std::shared_ptr<Item> item, std::vector<State*>& states){
	char smb = item->get_lit();
	if(smb != '-' && smb != '|' && smb != '?' && smb != '+' && smb != '<' && smb != '{' && smb != '&'){
		State* s1 = new State();
		states.push_back(s1);
		State *s2 = new State();
		states.push_back(s2);
		if(smb == '.') s1->add_trans(*s2, '.');
		else s1->add_trans(*s2, smb);
		Fragment* result = new Fragment(s1, s2);
		return result;
	}else if(smb == '&'){
		auto a_node = std::dynamic_pointer_cast<Dot_Node>(item);
		State* s1 = new State();
		states.push_back(s1);
		State *s2 = new State();
		states.push_back(s2);
		s1->add_trans(*s2, a_node->child->get_lit());
		Fragment* result = new Fragment(s1, s2);
		return result;
	}else if(smb == '{'){
			auto cur_node = std::dynamic_pointer_cast<CurBr_Node>(item);
			std::string s = cur_node->name;
			int i = 0, f_num = 0, s_num = 0;
			bool flag = false;
			while(s[i]!= ',' && i < s.size()){
				f_num = f_num*10+((int)s[i])-48;
				++i;
			}
			if(s[i] == ',') flag = true;
			++i;
			while(i<s.size()){
				s_num = s_num*10+((int)s[i])-48;
				++i;
			}
			if(!flag){//{f_num}
				Fragment *r1 = make_fragment(cur_node->child, states);
				for(int a = 0; a < f_num-1; ++a){
					Fragment* rn = make_fragment(cur_node->child, states);
					r1->finish->add_trans(*rn->start, '_');
					r1->finish = rn->finish;
				}
				return r1;
			}else{
				if(s_num == 0){//{f_num, }
					Fragment *r1 = make_fragment(cur_node->child, states);
					for(int a = 0; a < f_num-1; ++a){
						Fragment* rn = make_fragment(cur_node->child, states);
						r1->finish->add_trans(*rn->start, '_');
						r1->finish = rn->finish;
					}
					Fragment *r = make_fragment(cur_node->child, states);
					State* s1 = new State();
					states.push_back(s1);

					r1->finish->add_trans(*r->start, '_');
					r1->finish->add_trans(*s1, '_');
					r->finish->add_trans(*s1, '_');
					r->finish->add_trans(*r->start, '_');
					Fragment* result = new Fragment(r1->start, s1);
					return result;
				}else{//{f_num, s_num}
					//std::cout << "\ncode5\n";
					State* s1 = new State();
					states.push_back(s1);
					State* s2 = new State();
					states.push_back(s2);
					s1->add_trans(*s2, '_');
					Fragment* r1 = new Fragment(s1, s2);
					for(int a = f_num; a <= s_num; ++a){
						Fragment* ra = make_fragment(cur_node->child, states);
						for(int b = 1; b < a; ++b){
							Fragment* rn = make_fragment(cur_node->child, states);
							ra->finish->add_trans(*rn->start, '_');
							ra->finish = rn->finish;
						}
						//std::cout << "\n" << a << "\n";
						State* st = new State();
						states.push_back(st);
						State* fin = new State();
						states.push_back(fin);
						Fragment* s1 = r1;
						Fragment* s2 = ra;
						st->add_trans(*s1->start, '_');
						st->add_trans(*s2->start, '_');
						s1->finish->add_trans(*fin, '_');
						s2->finish->add_trans(*fin, '_');
						r1->start = st;
						r1->finish = fin;
					}
					//std::cout <<"\n we are here\n";
					if(f_num != 0){
						s1->out1 = nullptr;
						//std::cout << "\nand not hear\n";
					}
					return r1;
				}
			}
			
	}
	else if (smb == '|'){
		auto or_node = std::dynamic_pointer_cast<Double_Node>(item);

		State* st = new State();
		states.push_back(st);
		State* fin = new State();
		states.push_back(fin);
		Fragment* s1 = make_fragment(or_node->first_child, states);
		Fragment* s2 = make_fragment(or_node->second_child, states);
		st->add_trans(*s1->start, '_');
		st->add_trans(*s2->start, '_');
		s1->finish->add_trans(*fin, '_');
		s2->finish->add_trans(*fin, '_');
		Fragment* result = new Fragment(st, fin);
		return result;
	}else if (smb == '-'){

		auto concate_node = std::dynamic_pointer_cast<Double_Node>(item);
		Fragment* s1 = make_fragment(concate_node->first_child, states);
		Fragment* s2 = make_fragment(concate_node->second_child, states);
		s1->finish->add_trans(*s2->start, '_');
		//s1->finish->add_trans(*s2->start, '-');
		Fragment* result = new Fragment(s1->start, s2->finish);
		return result;
	} else if (smb == '+'){

		auto plus_node = std::dynamic_pointer_cast<Single_Node>(item);
		Fragment *r = make_fragment(plus_node->child, states);
		Fragment *r1 = make_fragment(plus_node->child, states);
		State* s1 = new State();
		states.push_back(s1);

		r->finish->add_trans(*r1->start, '_');
		r->finish->add_trans(*s1, '_');
		r1->finish->add_trans(*s1, '_');
		r1->finish->add_trans(*r1->start, '_');
		Fragment* result = new Fragment(r->start, s1);
		return result;
	}else if (smb == '<'){

		auto capture_node = std::dynamic_pointer_cast<Single_Node>(item);
		Fragment* s = make_fragment(capture_node->child, states);
		/*std::shared_ptr<State> s1 = std::make_shared<State>();
		s->finish->add_trans()*/
		Fragment* result = new Fragment(s->start, s->finish);
		return result;
	}else {// (smb == '?'){

		auto quest_node = std::dynamic_pointer_cast<Single_Node>(item);
                Fragment *s = make_fragment(quest_node->child, states);
		State* s1 = new State();
		states.push_back(s1);
		State* s2 = new State();
		states.push_back(s2);

		s1->add_trans(*s->start, '_');
		s->finish->add_trans(*s2, '_');
		s1->add_trans(*s2, '_');
        Fragment* result = new Fragment(s1, s2);
		return result;
	}
}

#endif

