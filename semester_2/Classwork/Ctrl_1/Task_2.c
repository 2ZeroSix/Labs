#include <stdio.h>
#include <stdlib.h>

typedef struct _tree{
  int value;
  struct _tree* left;
  struct _tree* right;
}tree;

tree* push_in_tree(tree* head, int element){
  tree* new = (tree*)calloc(1, sizeof(tree));
  new->value = element;
  if (head) {
    tree* cur = head;
    char go = 1;
    while(go) {
      if (cur->value > element) {
        if (cur->left) {
          cur = cur->left;
        }
        else {
          cur->left = new;
          go = 0;
        }
      }
      else {
        if (cur->right) {
          cur = cur->right;
        }
        else {
          cur->right = new;
          go = 0;
        }
      }
    }
  }
  else {
    head = new;
  }
  return head;
}

void depth_print(FILE* output, tree* head) {
  if (!head) {
    return;
  }
  fprintf(output, "%d ", head->value);
  depth_print(output, head->left);
  depth_print(output, head->right);
}

void depth_free(tree* head) {
  if (!head) {
    return;
  }
  depth_print(head->left);
  depth_print(head->right);
  free(head);
}

void readtree(FILE* input, tree** head) {
  int numb;
  while(fscanf(input, "%d", &numb)) {
    *head = push_in_tree(*head, numb);
  }
}

void delleaf(tree** head, int numb) {
	if (head) {
    tree* cur = head;
    tree* prev = NULL;
    char stat = 0;
    char go = 1;
    while(go) {
      if (cur->value > numb) {
        if (cur->left) {
        	prev = cur;
        	stat = -1;
          cur = cur->left;
        }
        else {
          go = 0;
        }
      }
      else {
        if (cur->right) {
        	stat = 1;
        	prev = cur;
          cur = cur->right;
        }
        else {
          go = 0;
        }
      }
    }
    tree* del = cur;
    if(del->left && del->right) {
    	cur = del->right;
    	tree* last = del;
    	while (cur->left){
    		last = cur;
    		cur = cur->left;
    	}
    	if (cur->right) {
    		tree* tmp = cur->left;
    		last = cur->left = cur->right;
    		cur->right = NULL;
    		cur = tmp;
    	}
    	last->left = NULL;
    	switch (stat) {
    		case -1:
    			prev->left = cur;
    			break;
    		case 1:
	    		prev->right = cur;
	    		break;
	    	default:
	    	break;
    	}
    	free(del);
    }
    else if(del->left) {
    	switch (stat) {
    		case -1:
    			prev->left = del->left;
    			break;
    		case 1:
	    		prev->right = del->left;
	    		break;
	    	default:
	    	break;
    	}
    	free(del);
    }
    else if(del->right) {
    	switch (stat) {
    		case -1:
    			prev->left = del->right;
    			break;
    		case 1:
	    		prev->right = del->right;
	    		break;
	    	default:
	    	break;
    	}
    	free(del);
    }
    else {
    	switch (stat) {
    		case -1:
    			prev->left = NULL;
    			break;
    		case 1:
	    		prev->right = NULL;
	    		break;
	    	default:
	    	break;
    	}
    	free(del);
    }
  }
}

int main(int argc, char** argv) {
	if (argc > 1) {
		FILE* in;
		tree* head = NULL;
		if (in = fopen(argv[1], "r")) {
			int i;
			readtree(in, &head);
			for(i = 2; i < argc; i++){
				delleaf(&head, atoi(argv[i]));
			}
			depth_print(stdout, head);
		}
	}
}