#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <chrono>

int kol = 0;
float res = 0;


using namespace std;
// Класс «узел дерева»
class Node { char d;	 //тег узла
	    Node * lft;	// левый сын
	    Node * rgt;	// правый сын
public:
		Node() : lft(nullptr), rgt(nullptr) { } // конструктор узла
		~Node(){ if(lft) delete lft; // деструктор (уничтожает поддерево)
			     if (rgt) delete rgt; }
friend class Tree;	// дружественный класс «дерево»
};

template <class Item> class STACK
{ Item * S; int t;
public:
	STACK(int maxt) : S(new Item[ maxt ]), t( 0 ) { }
	int empty( ) const { return t == 0; }
	void push(Item item) { S[t++] = item; }
	Item pop( ) {return ( t ? S[ --t ] : 0 ); }
};

// Класс «дерево в целом»
class Tree
{	Node * root;	// указатель на корень дерева
char num, maxnum;		//счётчик тегов и максимальный тег
    int maxrow, offset;		//максимальная глубина, смещение корня
    char ** SCREEN;	// память для выдачи на экран
    void clrscr();	// очистка рабочей памяти
    Node* MakeNode(int depth);	// создание поддерева
    void OutNodes(Node * v, int r, int c); // выдача поддерева
    Tree (const Tree &);	// фиктивный конструктор копии
    Tree (Tree &&);		//копия с переносом (С++11)
    Tree operator = (const Tree &) const = delete;	// присваивание
    Tree operator = (Tree &&) const = delete; // то же,  с переносом
public:
	Tree(char num, char maxnum, int maxrow);
	~Tree();
	void MakeTree() // ввод — генерация дерева
	{ root = MakeNode(0); }
	bool exist() { return root != nullptr; } // проверка «дерево не пусто»
	int DFS();
	int OutTree();	// выдача на экран
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
	if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r)); //левый сын
	if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //правый сын
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
