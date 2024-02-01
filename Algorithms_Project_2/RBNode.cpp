#pragma once
#include "RBNode.h"


int RBNode::getColor()
{
	return color;
}

void RBNode::setColor(int newColor)
{
	color = newColor;
}

int RBNode::getKey()
{
	return key;
}

void RBNode::setKey(int newKey)
{
	key = newKey;
}

RBNode* RBNode::getParent()
{
	return parent;
}

RBNode* RBNode::getLeftChild()
{
	return leftChild;
}

RBNode* RBNode::getRightChild()
{
	return rightChild;
}

void RBNode::setParent(RBNode* newParent)
{
	parent = newParent;
}

void RBNode::setLeftChild(RBNode* newChild)
{
	leftChild = newChild;
}

void RBNode::setRightChild(RBNode* newChild)
{
	rightChild = newChild;
}