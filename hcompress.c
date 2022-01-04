#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "LinkedList.h"
struct tnode* createFreqTable(char* name, int* x) {
	FILE* f;
	f = fopen(name, "r");
	if(f == NULL)
		printf("error\n");
	//read all characters into array
	char c[1000000];
	int size = 0;
	char buff = fgetc(f);
	while(buff != EOF) {
		*(c+size) = buff;
		//printf("%c\n", buff);
		size++;
		buff = fgetc(f);
	}
	struct tnode* arr = malloc(size*sizeof(struct tnode));
	for(int k = 0; k < size; k++) {
		arr[k].weight = 0;
		arr[k].left = NULL;
		arr[k].right = NULL;
		arr[k].parent = NULL;
	}
	//take the character array and make a histogram
	fclose(f);
	int histSize = 1;
	for(int j = 0; j < size; j++) {
                for(int i = 0; i <= histSize; i++) {
			if ((arr + i)->c == c[j]) {
				//printf("here2\n");
				(arr+i)->weight++;
				break;
			} else if (i == histSize - 1){
				//printf("here2\n");
				(arr + i)->c = c[j];
				(arr+i)->weight++;
				histSize += 1;
				break;
			}
		}
	}
	*x = histSize - 1;
	return arr;
}
char* decToBin(int dec) {
        char *arr = malloc(100 * sizeof(char));
        char temp[9];
        int length = 0;
        while (dec > 0) {
                if (dec % 2 == 1) {
                        temp[length] = '1';
                } else {
                        temp[length] = '0';
                }
                dec = dec / 2;
                length++;
        }
        int current = 0;
        for(int i = 7; i > - 1; i--) {
		if(i <= length-1) {
			arr[current] = temp[i];
			current++;
		}else {
			arr[current] = '0';
			current++;
		}
        }
        return arr;
}
char binToDec(char* bin) {
        int zeroPos = strlen(bin);
        int pow2 = 0;
        int result1 = 0;
        for(int i = zeroPos - 1; i > -1; --i) {
                if(bin[i] == '1') {
                        result1 += 1*pow(2, pow2);
                }
                pow2++;
        }
	char result = result1;
        return result;
}
struct tnode* createHuffmanTree(struct tnode* name, int size) {
	LLIST* list = LLCreate();
	for(int i = 0; i < size;i++){
		list_add_in_order(&list, &(name[i]));
	}
	//adding all nodes in ^
	//One by one creating the tree by putting the two smallest nodes together
	int a = size;
	while(a != 1) {
		struct tnode* parent = malloc(sizeof(struct tnode));
		list->data->parent = parent;
		list->next->data->parent = parent;
		//printf("%d, %d\n", list->data->weight, list->next->data->weight);
		parent->weight = list->data->weight + list->next->data->weight;
		parent->parent = NULL;
		parent->c = 300;
		parent->left = list->data;
		parent->right = list->next->data;
		//printf("%d\n", parent->weight);
		list_remove(&list);
		list_remove(&list);
		list_add_in_order(&list, parent);
		a--;
	}
	return list->data;
}
void encodeFile(char* name, struct tnode* leafs, int size) {
	FILE* fin;
        fin = fopen(name, "r");
        if(fin == NULL) {
                printf("Input file does not exist\n");
	}
	//adding the .huf extension
	int a = strlen(name);
	char newName[a+4];
	newName[a] = '.';
	newName[a+1] = 'h';
	newName[a+2] = 'u';
        newName[a+3] = 'f';
	for(int i = 0; i < a;i++) {
		newName[i] = name[i];
	}
	printf("%s", newName);
	FILE* fout;
	fout = fopen(newName, "w");
	if(fout == NULL) {
                printf("Output file does not exist\n");
        }
	int current = fgetc(fin);
	char subString[50];
	struct tnode* curr;
	int currCindex = 0;
	int currBit = 7;
	int buffInt = 0;
	int overFlag = 0;
	//loop throught the file for each character
	while(current != EOF) {
		//finding the correct character from the histogram
                for(int i = 0; i < size; i++) {
			if(leafs[i].c == current) {
				curr = &leafs[i];
				//looping through for each character
				//and getting backwards code
				while(curr->parent != NULL) {
					if(curr->parent->left == curr) {
						subString[currCindex] = '0';
						currCindex++;
					} else {
						subString[currCindex] = '1';
						currCindex++;
					}
					curr = curr->parent;
				}
				break;
			}
		}
		//printf("%c\n", current);
		//reversing character string and putting in the 
		// char when 8 bits are read 
		for(int k = currCindex; k > -1;k--) {
			if(subString[k] == '1') {
				buffInt += 1*pow(2, currBit);
				subString[k] = 'n';
				currBit--;
				//printf("1");
			} else if(subString[k] == '0') {
				subString[k] = 'n';
				currBit--;
				//printf("0");
			}
			if(currBit == -1) {
				char buff = buffInt;
                                fputc(buff, fout);
                                currBit = 7;
				k = currCindex;
				buffInt = 0;
			}
		}
		//if statement check for final char
                current = fgetc(fin);
		if(current == EOF && buffInt > 0) {
			char buff = buffInt;
			fputc(buff, fout);
		}
		currCindex = 0;
        }
	fclose(fin);
	fclose(fout);
	//printf("Original bytes: %d\nConverted bytes %d\n", charCount, compCount);
}
void decodeFile(char* name, struct tnode* root) {
	FILE* fin;
        fin = fopen(name, "r");
        if(fin == NULL) {
                printf("Input file does not exist\n");
        }
        FILE* fout;
	int a = strlen(name);
        char newName[a+4];
        newName[a] = '.';
        newName[a+1] = 'd';
        newName[a+2] = 'e';
        newName[a+3] = 'c';
        for(int i = 0; i < a;i++) {
                newName[i] = name[i];
        }
	fout = fopen(newName, "w");
        if(fout == NULL) {
                printf("Output file does not exist\n");
        }
	int currentchar = fgetc(fin);
	struct tnode *curr;
	char* current;
	int i = -1;
	curr = root;
	//looping through coded file
        while(currentchar != EOF) {
		current = decToBin(currentchar);
		//for each 8 bit string loops through and follows
		//the current code down to the leaf and places 
		//that leafes char
                while(i < 8) {
			i++;
			if(current[i] == '0') {
				curr = curr->left;
			}else if(current[i] == '1'){
				curr = curr->right;
			}
			if(curr->left == NULL && curr->right == NULL) {
				//printf("%c", curr->c);
				fputc(curr->c, fout);
				curr = root;
			}
		}
		i = -1;
		currentchar = fgetc(fin);
        }
	fclose(fin);
	fclose(fout);
}
//recursive freeTree method that checks if passed in 
//tree node is NULL or part of the leaf array
//if not frees the current node and passes that 
//nodes left and right nodes into the function
void freeTree(struct tnode* root) {
	if(root == NULL || root->c != 300) {
		return; 
	}
	//printf("freed");
	freeTree(root->left);
	freeTree(root->right);
	free(root);

} 
int main(int argc, char *argv[]) {
	// Check the make sure the input parameters are correct
	if (argc != 3) {
		printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf%d\"\n", argc); fflush(stdout);
		exit(1);
	}
	int size = 0;
	// Create the frequency table by reading the generic file
	struct tnode* leafNodes = createFreqTable("decind.txt", &size);

	//Create the huffman tree from the frequency table
	struct tnode* treeRoot = createHuffmanTree(leafNodes, size);
	// encode
	//printf("%d\n", size);
	if (strcmp(argv[1], "-e") == 0) {

		// Pass the leafNodes since it will process bottom up
		encodeFile(argv[2], leafNodes, size);
		printf("\nencoding finished\n");
		freeTree(treeRoot);
	} else { // decode
		// Pass the tree root since it will process top down
		decodeFile(argv[2], treeRoot);
		freeTree(treeRoot);
		printf("\ndecoding finished\n");
	}
	return 0;
}
