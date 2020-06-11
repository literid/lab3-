#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "Tree.h"

int multx2(int x)
{
	return 2 * x;
}

bool more_than_fifty(int x) 
{
	if (x > 50) return true;
	return false;
}

int lin(int x, int y) 
{
	return 2*x + y;
}

std::string plus_hello(std::string s) 
{
	return s + "hello";
}

bool have_hello(std::string s) 
{
	return (s.find("hello") != std::string::npos);
}

std::string str_reduce(std::string s1,std::string s2)
{
	return s1 + s2;
}
int main() {
	BSTree<int> b1(15,150); //key = data / 10
	b1.add(10,100);
	b1.add(20,200);
	b1.add(30,300);

	assert(b1.get_size() == 4);
	b1.remove(10);
	assert(b1.get_size() == 3);

	assert(b1.search(20) == 200);
	assert(b1.search(30) == 300);

	BSTree<int> b2(10,20);
	b2.add(5, 10);
	b2.add(13, 26);
	b2.add(20, 40);
	b2.add(30, 60);

	std::vector<int> tree_vector1;
	b2.to_string(tree_vector1); // default NLR
	std::vector<int> true_vector1 = { 20, 10, 26, 40, 60 };
	assert(tree_vector1 == true_vector1);

	std::string order = "NRL";
	std::vector<int> tree_vector2;
	std::vector<int> true_vector2 = { 20, 26, 40, 60, 10 }; 
	b2.to_string(tree_vector2,order);
	assert(tree_vector2 == true_vector2);

	b2.map(multx2);
	std::vector<int> tree_vector3;
	std::vector<int> true_vector3 = { 40, 20, 52, 80, 120};
	b2.to_string(tree_vector3);
	assert(tree_vector3 == true_vector3);

	BSTree<int>* b3 = b2.where(more_than_fifty);
	std::vector<int> tree_vector4;
	std::vector<int> true_vector4 = { 52, 80, 120 };
	b3->to_string(tree_vector4); 
	assert(tree_vector4 == true_vector4);
	delete b3;

	assert(b2.reduce(lin, 10) == 634);

	using std::string;
	BSTree<string> d1(5, "house");
	d1.add(7, "jupiter");
	d1.add(4, "hell");
	d1.add(6, "papers");

	assert(d1.get_size() == 4);
	d1.remove(4);
	assert(d1.get_size() == 3);
	
	std::vector<string> tree_vec1;
	std::vector<string> true_vec1 = { "house","jupiter","papers" };
	d1.to_string(tree_vec1);
	assert(tree_vec1 == true_vec1);

	d1.map(plus_hello);
	std::vector<string> tree_vec2;
	std::vector<string> true_vec2 = { "househello","jupiterhello","papershello" };
	d1.to_string(tree_vec2);
	assert(tree_vec2 == true_vec2);

	BSTree<string>* d2 = d1.where(have_hello);
	std::vector<string> tree_vec3;
	std::vector<string> true_vec3 = { "househello","jupiterhello","papershello" };
	d2->to_string(tree_vec3);
	assert(tree_vec3 == true_vec3);
	delete d2;

	assert(d1.reduce(str_reduce, "cat") == "papershellojupiterhellohousehellocat");
}	
