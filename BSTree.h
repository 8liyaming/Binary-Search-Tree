#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTreeNode  //����������
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};

template<class K>
class BSTree  //����������
{
typedef BSTreeNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);  //����һ���ڵ㲢��key����
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;  //�����Ѿ��������ֵһ���������޷�����
			}
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//�ҵ��ˣ���ʼɾ��;��Ϊ����3�������
				//1.��Ϊ��    2.��Ϊ��    3.���Ҷ���Ϊ��
				if (cur->_left == nullptr)  //��Ϊ�գ�����ָ���ҵ��ң�ɾ���Լ�
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}
					
					delete cur;
				}
				else if (cur->_right == nullptr)  //��Ϊ�գ�����ָ���ҵ���ɾ���Լ�
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					
				    delete cur;
				}
				else  //���Ҷ���Ϊ�գ�����ֱ��ɾ����ʹ���滻��
				{
					Node* rightMinParent = cur;
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}

					//�滻(����������С�ڵ��滻Ҫɾ���Ľڵ�)
					cur->_key = rightMin->_key;

					//ת������ɾ��rightMin(rightMin����Ϊ�գ�����ָ��������)
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
					}
					else
					{
						rightMinParent->_right = rightMin->_right;
					}

					delete rightMin;
				}

				return true;
			}
		}

		return false;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			//�������
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};

void TestBSTree()
{
	BSTree<int> t;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();

	//1.Ҷ��
	t.Erase(2);
	t.InOrder();
	//2.�����Ϊ��
	t.Erase(8);
	t.Erase(1);
	t.InOrder();
	//3.���Ҷ���Ϊ��
	t.Erase(5);
	t.InOrder();
	//4.ȫ��ɾ��
	for (auto e : a)
	{
		t.Erase(e);
		t.InOrder();
	}
}