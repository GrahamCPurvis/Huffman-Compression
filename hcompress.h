
struct tnode {
  int weight;
  int c;
  struct tnode* left;
  struct tnode* right;
  struct tnode* parent;
};

struct tnode* createFreqTable(char* name, int* x);
struct tnode* createHuffmanTree(struct tnode* name,int size);
