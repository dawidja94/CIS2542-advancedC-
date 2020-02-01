// FILE: nodeTemplateToolkit.h
// IMPLEMENTS: The functions of the nodeTemplate template class and the
// linked list toolkit.
//
// INVARIANT for the nodeTemplate class:
//   The data of a nodeTemplate is stored in data_field, and the link in link_field.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t

//   template <class Item>
//   size_t list_length(const nodeTemplate<Item>* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The value returned is the number of nodeTemplates in the linked
//     list.
//
template <class Item>
std::size_t list_length(const nodeTemplate<Item>* head_ptr) {
	const nodeTemplate<Item> *cursor;
	std::size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link())
		++answer;

	return answer;
}

//   template <class Item>
//   void list_head_insert(nodeTemplate<Item>*& head_ptr, const Item& entry) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: A new nodeTemplate containing the given entry has been added at
//     the head of the linked list; head_ptr now points to the head of the new,
//     longer linked list.
//
template <class Item>
void list_head_insert(nodeTemplate<Item>*& head_ptr, const Item& entry) {
	head_ptr = new nodeTemplate<Item>(entry, head_ptr);
}

//   template <class Item>
//   void list_insert(nodeTemplate<Item>* previous_ptr, const Item& entry) 
//     Precondition: previous_ptr points to a nodeTemplate in a linked list.
//     Postcondition: A new nodeTemplate containing the given entry has been added
//     after the nodeTemplate that previous_ptr points to.
//
template <class Item>
void list_insert(nodeTemplate<Item>* previous_ptr, const Item& entry) {
	nodeTemplate<Item> *insert_ptr;

	insert_ptr = new nodeTemplate<Item>(entry, previous_ptr->link());
	previous_ptr->set_link(insert_ptr);
}

//   template <class nodeTemplatePtr, class Item>
//   nodeTemplatePtr list_search
//   (nodeTemplatePtr head_ptr, const Item& target) 
//   The nodeTemplatePtr may be either nodeTemplate<Item>* or const nodeTemplate<Item>*
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The return value is a pointer that points to the first
//     nodeTemplate containing the specified target in its data member. If there is no
//     such nodeTemplate, the nullptr pointer is returned.
//
template <class nodeTemplatePtr, class Item>
nodeTemplatePtr list_search(nodeTemplatePtr head_ptr, const Item& target) {
	nodeTemplatePtr cursor;

	for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link())
		if (target == cursor->data())
			return cursor;
	return nullptr;
}

//   template <class nodeTemplatePtr, class SizeType>
//   nodeTemplatePtr list_locate(nodeTemplatePtr head_ptr, SizeType position)
//   The nodeTemplatePtr may be either nodeTemplate<Item>* or const nodeTemplate<Item>*
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0.
//     Postcondition: The return value is a pointer that points to the nodeTemplate at
//     the specified position in the list. (The head nodeTemplate is position 1, the
//     next nodeTemplate is position 2, and so on). If there is no such position, then
//     the nullptr pointer is returned.
//
template <class nodeTemplatePtr, class SizeType>
nodeTemplatePtr list_locate(nodeTemplatePtr head_ptr, SizeType position) {
	nodeTemplatePtr cursor;
	SizeType i;
	// ensure valid position
	assert(0 < position);
	cursor = head_ptr;
	for (i = 1; (i < position) && (cursor != nullptr); ++i)
		cursor = cursor->link();
	return cursor;
}

//   template <class Item>
//   void list_head_remove(nodeTemplate<Item>*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one nodeTemplate.
//     Postcondition: The head nodeTemplate has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
template <class Item>
void list_head_remove(nodeTemplate<Item>*& head_ptr) {
	nodeTemplate<Item> *remove_ptr;

	remove_ptr = head_ptr;
	head_ptr = head_ptr->link();
	delete remove_ptr;
}

//   template <class Item>
//   void list_remove(nodeTemplate<Item>* previous_ptr) 
//     Precondition: previous_ptr points to a nodeTemplate in a linked list, and this
//     is not the tail nodeTemplate of the list.
//     Postcondition: The nodeTemplate after previous_ptr has been removed from the
//     linked list.
//
template <class Item>
void list_remove(nodeTemplate<Item>* previous_ptr) {
	nodeTemplate<Item> *remove_ptr;

	remove_ptr = previous_ptr->link();
	previous_ptr->set_link(remove_ptr->link());
	delete remove_ptr;
}

//   template <class Item>
//   void list_clear(nodeTemplate<Item>*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All nodeTemplates of the list have been returned to the heap,
//     and the head_ptr is now nullptr.
//
template <class Item>
void list_clear(nodeTemplate<Item>*& head_ptr) {
	while (head_ptr != nullptr)
		list_head_remove(head_ptr);
}

//   template <class Item>
//   void list_copy
//   (const nodeTemplate<Item>* source_ptr, nodeTemplate<Item>*& head_ptr, nodeTemplate<Item>*& tail_ptr)
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//
template <class Item>
void list_copy(
	const nodeTemplate<Item>* source_ptr,
	nodeTemplate<Item>*& head_ptr,
	nodeTemplate<Item>*& tail_ptr
) {
	// Library facilities used: cstdlib
	head_ptr = nullptr;
	tail_ptr = nullptr;

	// Handle the case of the empty list
	if (source_ptr == nullptr)
		return;

	// Make the head nodeTemplate for the newly created list, and put data in it
	list_head_insert(head_ptr, source_ptr->data());
	tail_ptr = head_ptr;

	// Copy rest of the nodeTemplates one at a time, adding at the tail of new list
	source_ptr = source_ptr->link();
	while (source_ptr != nullptr)
	{
		list_insert(tail_ptr, source_ptr->data());
		tail_ptr = tail_ptr->link();
		source_ptr = source_ptr->link();
	}
}
