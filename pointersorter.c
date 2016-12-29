#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NODEMEMORY malloc(sizeof(Node))

typedef struct node{ //linked list struct for tokens.
	char *val;
	struct node *next;
}Node;

Node *nodeCreate(char* input){ //create and sort tokens

    if(input==0||input==NULL||strlen(input)<=0){  //input string empty  
    	printf("empty input string");
    	return NULL;
    }
    
    else{
    	int letterCount=0;
    	char *c=input;
    	Node *temp, *prev;
    	Node *head=NULL; 

    	while(*input!='\0'){ 
        	if(isalpha(*c)){ //check each char if letter, b/c of delimiters 
        		c++; letterCount++;
        	}
        	else{
        		if(letterCount>0){//letters present
                        Node *new_Node=NODEMEMORY; //create new linked list node to hold them
                        new_Node->val=malloc(letterCount); 
                        strncpy(new_Node->val,input,letterCount);

                        if(head==NULL) {
                        	new_Node->next=head;
                        	head=new_Node;
                        }
                        else{
                        	temp=head;
                        	prev=head;
		while(temp!=NULL){//sort by comparing both Nodes
			int cmp=strcmp(temp->val, new_Node->val);
						if (cmp>=0){ //temp value greater
							new_Node->next=temp;
							if (temp==head)
								head=new_Node;
							else //prev
								prev->next=new_Node;
							break;
						}
						else{ // <=0 new_Node value greater
							prev=temp;
							temp=temp->next;
						}
					}

					if(temp==NULL) {
						new_Node->next=temp;
						prev->next=new_Node;
					}
				}
			}//no letters
			c++;
			input=c;
			letterCount=0;
		}
	}
	return head;
}
}

void printNode(Node* head){ //print tokens, recursively done
	printf("%s\n",head->val);
	if(head->next==NULL){
		return;
	}
	printNode(head->next);
}

int main(int argc,char ** argv){
	
	if (argc!=2){  //incorrect # of arguments 
		printf("Correct format: ./pointersorter strings");
		return 1;
	}
	
	char *input;
	Node *final=NULL;
	const char *temp=argv[1];

	input=malloc(sizeof(char)*strlen(temp));
	strcpy(input,temp);
	final=nodeCreate(input);
	printNode(final);
	free(final);
	final=NULL;
	return 0;
}

