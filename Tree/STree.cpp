#include "STree.h"

/*
Synt_Tree::Synt_Tree(const std::string& regex){
	std::vector<std::shared_ptr<Item>> items;
	//вносим в вектор ноды и закрываем все выражение в скобки
	items.push_back(std::make_shared<A_Node>('('));
	for(auto i : regex) items.push_back(std::make_shared<A_Node>(i));
	items.push_back(std::make_shared<A_Node>(')'));
	while(items.size() != 1){
		//std::cout << "items.size = " << items.size()<<std::endl;
		//ищем  ближайшие скобки
		for(auto it : items){
			std::cout << it->get_lit();
		}
		//std::cout << std::endl;
		std::pair<std::vector<std::shared_ptr<Item>>::iterator,
		 std::vector<std::shared_ptr<Item>>::iterator> pair = closest_brackets(items.begin(), items.end());
		auto& begin = pair.first;
		auto& end = pair.second;
		//std::cout<<"\n first brack " << (*begin)->get_lit();
		//std::cout<<"\n second brack " << (*end)->get_lit();

		//std::cout<<"branch is good\n";
                for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;


		for(auto it = begin; it < end; ++it){
			if(auto a_node = std::dynamic_pointer_cast<A_Node>(*it)){
				if(a_node->lit == '&'){
					std::shared_ptr<Dot_Operation_Strategy> strategy;
					Operations_parametrs p = {items, it, end};
					strategy->apply(p);
				}
			}
		}


		std::cout<<"& is good\n";
                for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;


		for(auto it = begin; it < end; ++it){
			if(auto a_node = std::dynamic_pointer_cast<A_Node>(*it)){
				if(a_node->lit == '<'){
					bool fl = !(it == begin);
					std::shared_ptr<Capture_Group_Operations_Strategy> strategy;
					Capture_operations_parametrs parametrs = {items, it, end, capture_groups};
					strategy->apply(parametrs, fl);
				}
			}
		}


		std::cout << "Cuptcher groop is good\n";
                for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;


		for(auto it = begin+1; it < end; ++it){
			if(auto a_node = std::dynamic_pointer_cast<A_Node>(*it)){
				Operations_parametrs p = {items, it, end};
				//Apply_Operations(a_node->lit, p);
				switch(a_node->lit){
					case '?':{
						Quest_Operations_Strategy strat;
						strat.apply(p);
						break;
					}
					case '+':{
						Plus_Operations_Strategy strat;
						strat.apply(p);
						break;
					}
				}
			}
		}


		std::cout << "+ and ? is good\n";
                for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;


		for(auto it = begin+2; it < end; ++it){
			if(auto a_node = std::dynamic_pointer_cast<A_Node>(*it)){
				if(a_node->lit == '|'){
					it++;
					continue;
				}
			}
			if(auto cupt = std::dynamic_pointer_cast<Capture_Group_Node>(*(it-1))){
				if(cupt->child == nullptr) {
					std::cout << "\nnullptr-ing children\n";
					continue;
				}
			}
			Concate_Operations_Strategy strat;
			Operations_parametrs p = {items, it, end};
			strat.apply(p);
		}
		for(auto it = begin+2; it < end; ++it){
			if(auto a_node = std::dynamic_pointer_cast<A_Node>(*it)){
				if(a_node->lit == '|'){
					Or_Operations_Strategy strat;
					Operations_parametrs p = {items, it, end};
					strat.apply(p);
				}
			}
		}


		std::cout << " | is good\n";
                for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;

                pair = closest_brackets(items.begin(), items.end());
                begin = pair.first;
                end = pair.second;

		if(auto cupt = std::dynamic_pointer_cast<Capture_Group_Node>(*(begin+1))){
			Capture_Groupe_Activate_Operations_Strategy strat;
			begin++;
			Capture_operations_parametrs p = {items, begin, end, capture_groups};
			strat.apply(p);
		}
		pair = closest_brackets(items.begin(), items.end());
                begin = pair.first;
                end = pair.second;
		std::cout<<"\n first brack " << (*begin)->get_lit();
                std::cout<<"\n second brack" << (*end)->get_lit() << "\n";
		items.erase(pair.second);
		items.erase(pair.first);
		std::cout << capture_groups.size();
		std::cout << "\nerase is good\n";
		for(auto it : items){
                        std::cout << it->get_lit();
                }
                std::cout << std::endl;
	}
	root = items[0];
}

void show_item(const std::shared_ptr<Item>& item, int lvl){
	if(item == nullptr) return;
	for(int i = 0; i < lvl; ++i) std::cout << "	";
	std::cout << item->get_lit() << std::endl;
	if(auto doub = std::dynamic_pointer_cast<Double_Node>(item)){
		show_item(doub->first_child, lvl+1);
		show_item(doub->second_child, lvl+1);
	} else if (auto single = std::dynamic_pointer_cast<Single_Node>(item)) show_item(single->child, lvl+1);
}

void Synt_Tree::show() const {
	if(root) show_item(root, 0);
	else std::cout<<"\n === Syntaxis Tree is free === \n";
}



*/
