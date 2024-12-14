#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <chrono>

int kol = 0;
float res = 0;


using namespace std;
// ����� ����� ������
class Node { char d;	 //��� ����
	    Node * lft;	// ����� ���
	    Node * rgt;	// ������ ���
public:
		Node() : lft(nullptr), rgt(nullptr) { } // ����������� ����
		~Node(){ if(lft) delete lft; // ���������� (���������� ���������)
			     if (rgt) delete rgt; }
friend class Tree;	// ������������� ����� �������
};

template <class Item> class STACK
{ Item * S; int t;
public:
	STACK(int maxt) : S(new Item[ maxt ]), t( 0 ) { }
	int empty( ) const { return t == 0; }
	void push(Item item) { S[t++] = item; }
	Item pop( ) {return ( t ? S[ --t ] : 0 ); }
};

// ����� ������� � �����
class Tree
{	Node * root;	// ��������� �� ������ ������
char num, maxnum;		//������� ����� � ������������ ���
    int maxrow, offset;		//������������ �������, �������� �����
    char ** SCREEN;	// ������ ��� ������ �� �����
    void clrscr();	// ������� ������� ������
    Node* MakeNode(int depth);	// �������� ���������
    void OutNodes(Node * v, int r, int c); // ������ ���������
    Tree (const Tree &);	// ��������� ����������� �����
    Tree (Tree &&);		//����� � ��������� (�++11)
    Tree operator = (const Tree &) const = delete;	// ������������
    Tree operator = (Tree &&) const = delete; // �� ��,  � ���������
public:
	Tree(char num, char maxnum, int maxrow);
	~Tree();
	void MakeTree() // ���� � ��������� ������
	{ root = MakeNode(0); }
	bool exist() { return root != nullptr; } // �������� ������� �� �����
	int DFS();
	int OutTree();	// ������ �� �����
	void time_creation();
};


Tree :: ~Tree( ) { for(int i = 0; i < maxrow; ++i) delete [ ]SCREEN[ i ];
				  delete [ ]SCREEN; delete root; }
int Tree :: OutTree( )
{	clrscr( );
	OutNodes(root, 1, offset);
	for (int i = 0; i < maxrow; i++)
	{ SCREEN[ i ][ 79 ] = 0;
		cout << '\n' << SCREEN[ i ];
	}
	cout << '\n';
	return kol;
}

void Tree :: clrscr( )
{ for(int i = 0; i < maxrow; i++)
	memset(SCREEN[i], '.', 80);
}

void Tree :: OutNodes(Node * v, int r, int c)
{
    if (r && c && (c<80)) SCREEN[ r - 1 ][ c - 1 ] = v->d;
    if (r < maxrow) {
	if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r)); //����� ���
	if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //������ ���
	}
}
Node * Tree :: MakeNode(int depth)
{
    Node * v = nullptr;
    int Y = (depth < rand( )%6+1) && (num <= 'z');
    //cout << "Node (" << num << ',' << depth << ")1/0: "; cin >> Y;
    auto start_time = std::chrono::high_resolution_clock::now();
    if (Y) {
        v = new Node;
        v->d = num++;
        if (depth<=2)kol++;
        v->lft = MakeNode(depth+1);
        v->rgt = MakeNode(depth+1);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
    res += total_time;
    return v;
}
void Tree :: time_creation()
{
    std::cout <<endl<< "Time of creation: " << res << " sec" << std::endl;
}
int Tree :: DFS( )
{ const int MaxS = 20;
  int count = 0;
  STACK <Node *> S(MaxS);
  S.push(root);
  while (!S.empty( ))
{   Node * v = S.pop( );
	cout << v->d <<  '_'; count++;
	if (v->rgt) S.push(v->rgt);
    if (v->lft) S.push(v->lft);
  }
  return count;
}
Tree ::	Tree(char nm, char mnm, int mxr):
	  num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr),
	  SCREEN(new char * [maxrow])
	  {	for(int i = 0; i < maxrow; ++i ) SCREEN[ i ] = new char[ 80 ]; }
