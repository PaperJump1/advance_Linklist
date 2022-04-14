#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
template<typename node_type>
class Listnode {
public:
	int num;
	node_type data;
	Listnode<node_type>* next;
	Listnode() :data(NULL), next(NULL), num(0) {

	}

	Listnode(const node_type val) : data(val), next(NULL) {

	}

	bool operator==(const Listnode<node_type>& tmp)const {
		if (tmp.data == this->data) {
			return true;
		}
	}

	bool operator!=(const Listnode<node_type>& tmp)const {
		if (tmp.data != this->data) {
			return true;
		}
	}

	
};

template<typename container_type,typename node_type>
class Nodewrapper :public std::iterator < std::bidirectional_iterator_tag,container_type> {
public:

	container_type* this_node;
	Nodewrapper() {
		this_node = NULL;
	}

	Nodewrapper(container_type* node) {
		this_node = node;
	}

	node_type& operator*()const {
		return this_node->data;
	}

	Nodewrapper<container_type,node_type>& operator++() {
		this_node = this_node->next;
		return*this;
	}

	bool operator==(const Nodewrapper<container_type,node_type>& tmp)const {
		if (tmp.this_node == this_node) {
			return true;
		}
	}

	bool operator!=(const Nodewrapper<container_type,node_type>& tmp)const {
		if (tmp.this_node != this_node) {
			return true;
		}
	}


};

template<typename node_type>
class Linklist:public Nodewrapper<node_type,node_type>,public  Listnode<node_type>{
public:
	//friend class Nodewrapper;
	
	Linklist() {
		Top = new Listnode<node_type>();
	}


	bool is_empty() {
		if (Last == NULL) {
			return true;
		}
	}

	void insert_node(node_type val) {
		Listnode<node_type>* node = new Listnode<node_type>();
		if (Top->next == NULL) {
			Top->next = node;
			Last = Top;
		}
		Last->next = node;
		node->data = val;
		node->num = num;
		num = num + 1;
		Last = node;
	}

	void insert_external_node(Listnode<node_type>* node,node_type val) {
		Last->next = node;
		node->num = num;
		node->data = val;
		Last = node;
		num = num + 1;
	}

	void delete_node(node_type val) {
		Listnode<node_type>* pre = Top;
		Listnode<node_type>* now = Top->next;
		while (now->next != NULL) {
			if (now->num == val) {
				pre->next = now->next;
				free(now);
				amend(pre);
				break;
			}
			now = now->next;
			pre = pre->next;
		}
		
	}

	void clear() {
		Listnode<node_type>* now;
		Listnode<node_type>* tmp;
		now = Top;
		now = now->next;
		tmp = now;
		while (now->next != NULL) {
			now = now->next;
			free(tmp);
			tmp = now;
		}
		free(now);
		num = 0;
		Last = NULL;
	}

	void print_last_data() {
		if (is_empty() == true) {
			cout << "List is empty";
			
		}
		else {
			cout << Last->num << ", " << Last->data;
		}
	}

	void print_all_data() {
		if (is_empty() == true) {
			cout << "List is empty";		
		}
		else {
			Listnode<node_type>* now;
			now = Top;
			now = now->next;
			while (now->next != NULL) {
				now = now->next;
				cout << now->num << ". " << now->data << " ";
			}
		}
		
	}

	int sizeof_list() {
		return num-1 ;
	}

	Listnode<node_type>* top() {
		return *top;
	}

	Nodewrapper<Listnode<node_type>,node_type> begin()const {
		return Nodewrapper<Listnode<node_type>,node_type>(Top);
	}

	Nodewrapper<Listnode<node_type>,node_type> end()const {
		return Nodewrapper<Listnode<node_type>,node_type>(Last->next);
	 }

private:
	Listnode<node_type>* Top = new Listnode<node_type>();
	Listnode<node_type>* Last = NULL;
	node_type data=0;
	int num = 0;

	void amend(Listnode<node_type>* pre) {
		num = pre->num+1;
		while (pre->next != NULL) {
			pre = pre->next;
			pre->num = num;
			num++;
		}
	}
};




int main() {
	Linklist<int> list;
	if (list.is_empty()==true) {
		cout << "true" << endl;
	}
	list.insert_node(13);
	if (list.is_empty()==true) {
		cout << "true";
	}
	 list.print_last_data();
	 list.insert_node(10);
	 list.insert_node(15);
	 list.insert_node(19);
	 list.insert_node(80);
	 cout << endl;
	 list.print_all_data();
	 list.delete_node(2);
	 cout << endl;
	 list.print_all_data();
	 Listnode<int>* newnode=new Listnode<int>();
	 list.insert_external_node(newnode,80);
	 cout << endl;
	 list.print_all_data();
	 int n = list.sizeof_list();
	 cout << endl << n;
	 //Nodewrapper<Linklist<int>> it;
	 auto it = find(list.begin(), list.end(), 19);
	 cout << endl << *it;
	 cout << endl;
	 list.clear();
	 //list.print_all_data();
	 if (list.is_empty() == true) {
		 cout << "true";
	 }
}