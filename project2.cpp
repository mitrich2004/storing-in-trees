#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <random>
#include <chrono>
using namespace std;

struct Node
{
    string value;
    Node* left = nullptr;
    Node* right = nullptr;

	Node(string v) :
		value(v),
		left(nullptr),
		right(nullptr)
	{

	}
};

class Tree
{
private:
    Node* root;

public:
    Tree() :
        root(nullptr)
    {

    }

	void insert(string v)
	{
		Node** tmp = &root;
		while (*tmp != nullptr)
		{
			if ((*tmp)->value > v)
			{
				tmp = &((*tmp)->left);
			}
			else
			{
				tmp = &((*tmp)->right);
			}
		}
		*tmp = new Node(v);
	}

    bool contains(string v)
    {
        Node* tmp = root;
        while (tmp != nullptr)
        {
            if (tmp->value > v)
            {
                tmp = tmp->left;
            }
            else if (tmp->value < v)
            {
                tmp = tmp->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void print() const
    {
        print(root);
    }

    void structured_print() const
    {
        structured_print(root, 0);
    }

    void clear()
    {
        clear(root);
    }

    ~Tree()
    {
        clear();
    }

private:
    void print(Node* n) const
    {
        if (n != nullptr)
        {
            print(n->left);
            cout << n->value << ' ';
            print(n->right);
        }
    }

    void structured_print(Node* n, int level) const
    {
        if (n != nullptr)
        {
            structured_print(n->right, level + 1);
            for (int i = 0; i < level; ++i)
            {
                cout << "   ";
            }
            cout << n->value << endl << endl;
            structured_print(n->left, level + 1);
        }
    }

    void clear(Node* n)
    {
        if (n != nullptr)
        {
            clear(n->left);
            clear(n->right);
			delete n;
        }
    }
};

struct AVLNode
{
	string value;
	int height;
	AVLNode* left;
	AVLNode* right;

	AVLNode(string v) :
		value(v),
		left(nullptr),
		right(nullptr),
		height(0)
	{

	}
};

class AVLTree
{
private:
	AVLNode* root;

public:
	AVLTree() :
		root(nullptr)
	{

	}

	void insert(string v)
	{
		insert(&root, v);
	}

	void structured_print() const
	{
		structured_print(root, 0);
	}

	void print() const
	{
		print(root);
	}

	bool contains(string v)
	{
		AVLNode* tmp = root;
		while (tmp != nullptr)
		{
			if (tmp->value > v)
			{
				tmp = tmp->left;
			}
			else if (tmp->value < v)
			{
				tmp = tmp->right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	int count() {
		if (root == nullptr) {
			return 0;
		}
		else {
			return 1 + count(root->left) + count(root->right);
		}
	}

	void test() {
		test(root);
	}

	void clear()
	{
		clear(root);
	}

	~AVLTree()
	{
		clear();
	}

private:
	void insert(AVLNode** node, string v)
	{
		if (*node != nullptr)
		{
			if ((*node)->value > v)
			{
				insert(&(*node)->left, v);
			}
			else
			{
				insert(&(*node)->right, v);
			}

			int balance;

			if ((*node)->right == nullptr)
			{
				(*node)->height = (*node)->left->height + 1;
				balance = -(*node)->height;
			}
			else if ((*node)->left == nullptr)
			{
				(*node)->height = (*node)->right->height + 1;
				balance = (*node)->height;
			}
			else
			{
				(*node)->height = max((*node)->left->height, (*node)->right->height) + 1;
				balance = (*node)->right->height - (*node)->left->height;
			}

			if (balance == -2)
			{
				if (((*node)->left->value > v))
				{
					rotate_right(node);
				}
				else
				{
					rotate_left(&(*node)->left);
					rotate_right(node);
				}
			}
			else if (balance == 2)
			{
				if (((*node)->right->value <= v))
				{
					rotate_left(node);
				}
				else
				{
					rotate_right(&(*node)->right);
					rotate_left(node);
				}
			}
		}
		else
		{
			*node = new AVLNode(v);
		}
	}

	void rotate_right(AVLNode** node)
	{
		AVLNode* tmp = (*node)->left;
		AVLNode* tmp2 = (*node);

		(*node)->left = tmp->right;
		tmp->right = tmp2;
		(*node) = tmp;

		tmp2->height = max(height(tmp2->left), height(tmp2->right)) + 1;
		tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	}

	void rotate_left(AVLNode** node)
	{
		AVLNode* tmp = (*node)->right;
		AVLNode* tmp2 = (*node);

		(*node)->right = tmp->left;
		tmp->left = tmp2;
		(*node) = tmp;

		tmp2->height = max(height(tmp2->left), height(tmp2->right)) + 1;
		tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	}

	int height(AVLNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}

		return node->height;
	}

	void structured_print(AVLNode* n, int level) const
	{
		if (n != nullptr)
		{
			structured_print(n->right, level + 1);
			for (int i = 0; i < level; ++i)
			{
				cout << "   ";
			}
			cout << n->value << "," << n->height << endl << endl;
			structured_print(n->left, level + 1);
		}
	}

	void print(AVLNode* n) const
	{
		if (n != nullptr)
		{
			print(n->left);
			cout << n->value << ' ';
			print(n->right);
		}
	}

	int count(struct AVLNode* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return 1 + count(node->left) + count(node->right);
		}
	}

	void test(AVLNode* n) {
		if (n != nullptr) {
			assert(n->height >= 0);
			int l = (n->left == nullptr) ? -1 : n->left->height;
			int r = (n->right == nullptr) ? -1 : n->right->height;
			assert(n->height == std::max(l, r) + 1);
			int bf = r - l;
			assert(bf < 2 && bf > -2);
			test(n->left);
			test(n->right);
		}
	}

	void clear(AVLNode* n)
	{
		if (n != nullptr)
		{
			clear(n->left);
			clear(n->right);
			delete n;
		}
	}
};

int main()
{
	ifstream file_in;
	ofstream insert_file_out;
	ofstream search_file_out;

	file_in.open("dictionary.txt");
	
	int maxTimes = 100;
	int step = 100;
	int numberOfWords = 20000;

	using ns = chrono::nanoseconds;
	using clock = chrono::steady_clock;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, numberOfWords - 1);

	vector<string> words(numberOfWords);
	vector<string> not_present_words = { "asjdfksjf", "ilkpljk", "zgmfgf" };
	vector<ns> avl_insert_times(numberOfWords / step, ns(0));
	vector<ns> avl_search_times(numberOfWords / step, ns(0));
	vector<ns> bst_insert_times(numberOfWords / step, ns(0));
	vector<ns> bst_search_times(numberOfWords / step, ns(0));

	for (int i = 0; i < words.size(); ++i)
	{
		string word;
		file_in >> words[i];
	}

	int choose;
	cin >> choose;

	if (choose == 1)
	{
		//sorted
		insert_file_out.open("insert_sorted.txt");
		search_file_out.open("search_sorted.txt");
	}
	else if (choose == 2)
	{
		//partly sorted
		insert_file_out.open("insert_partly_sorted.txt");
		search_file_out.open("search_partly_sorted.txt");

		for (int i = 0; i < numberOfWords / 200; ++i)
		{
			swap(words[dist(gen)], words[dist(gen)]);
		}
	}
	else
	{
		//random
		insert_file_out.open("insert_random.txt");
		search_file_out.open("search_random.txt");

		for (int i = 0; i < numberOfWords / 2; ++i)
		{
			swap(words[dist(gen)], words[dist(gen)]);
		}
	}

	for (int times = 0; times < maxTimes; ++times)
	{
		AVLTree avl;
		Tree bst;
		for (int i = 0; i < numberOfWords; ++i)
		{
			if ((i + 1) % step == 0)
			{
				//avl insert
				auto start = clock::now();
				avl.insert(words[i]);
				auto end = clock::now();
				ns time_taken = chrono::duration_cast<ns>(end - start);
				avl_insert_times[i / step] += time_taken;

				//avl contain
				start = clock::now();
				avl.contains(words[i]);
				avl.contains(not_present_words[dist(gen) % 3]);
				end = clock::now();
				time_taken = chrono::duration_cast<ns>(end - start);
				avl_search_times[i / step] += time_taken;

				//bst insert
				start = clock::now();
				bst.insert(words[i]);
				end = clock::now();
				time_taken = chrono::duration_cast<ns>(end - start);
				bst_insert_times[i / step] += time_taken;

				//bst contain
				start = clock::now();
				bst.contains(words[i]);
				avl.contains(not_present_words[dist(gen) % 3]);
				end = clock::now();
				time_taken = chrono::duration_cast<ns>(end - start);
				bst_search_times[i / step] += time_taken;
			}
			else
			{
				avl.insert(words[i]);
				bst.insert(words[i]);
			}
		}
	}

	for (int i = 0; i < bst_insert_times.size(); ++i)
	{
		insert_file_out << (i + 1) * step << ' ' << bst_insert_times[i].count() / maxTimes << ' ' << avl_insert_times[i].count() / maxTimes << endl;
	}

	for (int i = 0; i < bst_search_times.size(); ++i)
	{
		search_file_out << (i + 1) * step << ' ' << bst_search_times[i].count() / maxTimes << ' ' << avl_search_times[i].count() / maxTimes << endl;
	}

	insert_file_out.close();
	search_file_out.close();

	file_in.close();
}