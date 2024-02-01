#pragma once

class RBNode 
{
	private:
		int color;
		int key;
		RBNode* parent;
		RBNode* leftChild;
		RBNode* rightChild;
	public:
		int getColor();
		void setColor(int newColor);
		int getKey();
		void setKey(int newKey);
		RBNode* getParent();
		RBNode* getLeftChild();
		RBNode* getRightChild();
		void setParent(RBNode* newParent);
		void setLeftChild(RBNode* newChild);
		void setRightChild(RBNode* newChild);
};