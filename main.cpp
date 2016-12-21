#include <stdio.h>
#include <stdio.h>
#include <list>
#include <string>

#define TABLE 0
#define BLOCK 1

using namespace std;

class Obj{

	private:

		int type;
		bool clear;
		string name;
		Obj* support_obj;

	public:

		Obj(int type,string name){
			this->type			= type;
			this->name			= name;
			this->clear			= false;
			this->support_obj	= NULL;
		}

		int get_type(){
			return this->type;
		}

		string get_name(){
			return this->name;
		}

		bool get_clear(){
			return this->clear;
		}

		void set_clear(bool clear){
			this->clear = clear;
		}

		void set_on(Obj* support_obj){
			this->support_obj = support_obj;
		}

		Obj* get_on(){
			return this->support_obj;
		}
};

class World{

	private:

		list <Obj> obj_list;

		Obj* find(string name){
			for (list<Obj>::iterator it=obj_list.begin(); it != obj_list.end(); ++it)
				if(it->get_name().compare(name) == 0)
					return &(*it);
			return NULL;
		}

	public:

		World(){
			this->add(TABLE,"Table");
		}

		void add(int type,string name){
			obj_list.push_back(Obj(type,name));
		}

		bool set_on(string name_a,string name_b){
			Obj* a = find(name_a);
			Obj* b = find(name_b);
			if(a == NULL || b == NULL)
				return false;
			a->set_on(b);
			return true;
		}

		string get_on(string name){
			Obj* obj = find(name);
			if(obj == NULL)
				return string("ERROR");
			Obj* support_obj = obj->get_on();
			if(support_obj == NULL)
				return string("nothing");
			return support_obj->get_name();
		}

		bool on(string name_a,string name_b){
			Obj* a = find(name_a);
			Obj* b = find(name_b);
			if(a == NULL || b == NULL)
				return false;
			Obj* support_obj = a->get_on();
			return support_obj == b;
		}

		bool set_clear(string name,bool clear = true){
			Obj* obj = find(name);
			if(obj == NULL)
				return false;
			obj->set_clear(clear);
			return true;
		}

		bool get_clear(string name){
			Obj* obj = find(name);
			if(obj == NULL)
				return false;
			return obj->get_clear();
		}

		bool block(string name){
			Obj* obj = find(name);
			if(obj == NULL)
				return false;
			return obj->get_type()==BLOCK;
		}

		bool move(string b,string x,string y){

			// Precondition check
			bool pre = true;
			pre = pre && on(b,x);
			pre = pre && get_clear(b);
			pre = pre && get_clear(y);
			pre = pre && block(b);
			pre = pre && block(y);
			pre = pre && b!=x;
			pre = pre && b!=y;
			pre = pre && x!=y;
			if(!pre) return false;

			// Effect
			set_on(b,y);
			set_clear(x);
			set_clear(y,false);

			return true;

		}

		bool moveToTable(string b,string x){

			// Precondition check
			bool pre = true;
			pre = pre && on(b,x);
			pre = pre && get_clear(b);
			pre = pre && block(b);
			pre = pre && b!=x;
			if(!pre) return false;

			// Effect
			set_on(b,"Table");
			set_clear(x);

			return true;

		}
};

void print_clear(World *world,string name){
	if(world->get_clear(name))
		printf("%s clear: true.\n",name.c_str());
	else
		printf("%s clear: false.\n",name.c_str());
}

void print_on(World *world,string name){
	printf("%s is on %s.\n",name.c_str(),world->get_on(name).c_str());
}

void print_all(World *world){
	print_on(world,"A");
	print_on(world,"B");
	print_on(world,"C");
	print_on(world,"D");
	printf("=====================\n");
}

int main(int argc, char **argv){

	World *world = new World();

	// Initial state
	world->add(BLOCK,"A");
	world->add(BLOCK,"B");
	world->add(BLOCK,"C");
	world->add(BLOCK,"D");
	world->set_clear("A");
	world->set_clear("B");
	world->set_clear("C");
	world->set_clear("D");
	world->set_on("A","Table");
	world->set_on("B","Table");
	world->set_on("C","Table");
	world->set_on("D","Table");

	print_all(world);
	world->move("B", "Table", "A");

	print_all(world);
	world->move("C", "Table", "B");

	print_all(world);
	world->move("D", "Table", "C");

	print_all(world);

	return 0;
}
