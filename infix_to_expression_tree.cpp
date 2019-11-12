#include<iostream>
using namespace std;

template <class T>
class Stack{
public: 
	int top;
	T a[50];
  
	Stack() { top = -1; } 
	bool push(T x){
		if (top >= 49) { 
        		return false; 
    		} 
    		else{ 
        		a[++top] = x; 
        		return true; 
		}
	};

	T pop(){
    		if (top < 0){ 
        		return 0; 
    		} 
    		else{ 
        		T x = a[top--]; 
        		return x;
		}
	};

	T peek(){ 
    		if (top < 0) { 
        		return 0; 
    		} 
    		else { 
        		T x = a[top]; 
        		return x; 
    		} 
	}; 

	bool isEmpty(){ 
    		return (top < 0); 
	};
 
};

struct tree{ 
    char value; 
    tree* left, *right; 
}; 
  
int priority(char op){
	if ((op =='+') || (op =='-'))
		return 1;
	else if ((op =='/') || (op =='*'))
		return 2;
	else if (op == '^')
		return 3;
}

bool isOperator(char c) 
{ 
    	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') 
       		return true; 
   	return false; 
};

tree* newNode(int v) 
{ 
    tree *temp = new tree; 
    temp->left = temp->right = NULL; 
    temp->value = v; 
    return temp; 
};

void postorder(tree *t){ 
    	if(t){ 
		postorder(t->left); 
		postorder(t->right); 
		cout<< t->value; 
		
    	} 
};

void preorder(tree *t){
	if(t){
		cout<<t->value;
		preorder(t->left); 
		preorder(t->right); 
	}
};

void inorder(tree *t){
	if(t){
		inorder(t->left);
		cout<<t->value;
		inorder(t->right); 
	}
};

tree* constructTree(char str[]) 
{ 
	char temp;
	int length;
	Stack<char> infix;
	Stack<tree *>oper; 
	Stack<tree *>treenode;
	tree *t1, *t2;
	
	for(length = 0; str[length] != '\0'; ++length);

	for(int i = 0; i<length; i++)
		infix.push(str[i]);

	while(!infix.isEmpty()){
		temp = infix.pop();

		if(!isOperator(temp))
			treenode.push(newNode(temp));

		else if(temp == ')')
			oper.push(newNode(temp));

		else if(temp == '('){
			while(oper.peek() -> value != ')'){
				t1 = oper.pop();
				t1->left = treenode.pop();
				t1->right = treenode.pop();
				treenode.push(t1);
			}
			oper.pop();
		}
		
		else{
			bool pushed = false;
			while(!pushed){
				if(oper.isEmpty()){
					oper.push(newNode(temp));
					pushed = true;
				}
				else if(oper.peek() ->value == ')'){
					oper.push(newNode(temp));
					pushed = true;
				}
				else if((priority(temp) > priority(oper.peek() -> value)) || (priority(temp)==priority(oper.peek() -> value))){
					oper.push(newNode(temp));
					pushed = true;
				}
				else{
					t1 = oper.pop();
					t1->left = treenode.pop();
					t1->right = treenode.pop();
					treenode.push(t1);
				}
			}
		}
	}
	while(!oper.isEmpty()){
		t1 = oper.pop();
		t1->left = treenode.pop();
		t1->right = treenode.pop();
		treenode.push(t1);
	}
	return treenode.peek();
}



int main(){
	cout<<"Enter the infix expression"<<endl;
	char infix[50];
	cin>>infix;
    	tree* r = constructTree(infix); 
    	cout<<"Infix expression is \n"; 
    	inorder(r);
	cout<<endl;
	cout<<"Prefix expression is \n"; 
    	preorder(r);
	cout<<endl;
	cout<<"Postfix expression is \n"; 
    	postorder(r);
	cout<<endl;
    	return 0; 

} 










