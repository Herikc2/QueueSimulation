#pragma once

template <typename DATA>
struct ELEMENT
{
	DATA data;
	ELEMENT* next;
};

template <typename DATA>
struct QUEUE
{
	ELEMENT<DATA>* first;
};

template <typename DATA>
void initialize_queue(QUEUE<DATA>& list)
{
	list.first = nullptr;
}

// Cria um novo elemento.
template <typename DATA>
ELEMENT<DATA>* create_new_element(DATA type)
{
	ELEMENT<DATA>* element = new ELEMENT<DATA>();
	element->next = nullptr;
	element->data = type;
	return element;
}

// Insere o dado no final da fila de espera.
template <typename DATA>
bool queue(QUEUE<DATA>& list, DATA data)
{
	ELEMENT<DATA>* new_element = create_new_element(data);
	if (list.first == nullptr) {
		list.first = new_element;
	}
	else {
		ELEMENT<DATA>* current = list.first;
		while (current->next != nullptr)
			current = current->next;
		current->next = new_element;
	}
	return true;
}

// Remove o dado do início da fila.
template <typename DATA>
bool dequeue(QUEUE<DATA>& list) {
	if (list.first != nullptr) {
		ELEMENT<DATA>* delete_element = list.first;
		list.first = delete_element->next;
		delete delete_element;
		return true;
	}
	return false;
}

// Retorna o dado do início da fila.
template <typename DATA>
DATA back(QUEUE<DATA> list)
{
	if (list.first != nullptr)
		return list.first->data;
}

template <typename DATA>
int queue_data_amount(QUEUE<DATA> list)
{
	int counter = 0;
	ELEMENT<DATA>* current = list.first;
	while (true) {
		if (current == nullptr)
			return counter;
		current = current->next;
		counter++;
	}
}

// Exibe a lista
template <typename DATA>
void print_queue(QUEUE<DATA> list)
{
	ELEMENT<DATA>* current = list.first;
	while (current != nullptr) {
		print_data(current->data);
		current = current->next;
	}
}

template <typename DATA>
void print_data(DATA data)
{
	print_data(data);
}