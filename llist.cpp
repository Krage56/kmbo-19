#include <llist.h>

#include <stdexcept>

LList::Container::Container(const int &value, LList::Container *next) {
    this->value = value;
    this->next = next;
}

LList::Container::~Container() {}

void LList::Container::insertNext(const int &value) {
    Container* newContainer = new Container(value, this->next);
    this->next = newContainer;
}

void LList::Container::insertNext(LList::Container *container) {
    Container* tmp = this->next;
    this->next = container;
    container->next = tmp;
}

void LList::Container::removeNext() {
    Container* removeContainer = this->next;
    Container* newNext = removeContainer->next;
    this->next = newNext;
    removeContainer->next = nullptr;
    delete removeContainer;
}


LList::LList() : _head(nullptr), _size(0){}

LList::~LList() {
    forceContainerDelete(_head);
}

void LList::push_back(int val) {
    if (_size == 0) {
        push_front(val);
    }
    else{
        insert_at(_size, val);
    }
}

void LList::push_front(int val) {
    _head = new Container(val, _head);
    ++_size;
}

size_t LList::size() const {
    return _size;
}

int &LList::operator[](size_t idx) {
    return getContainer(idx)->value;
}

LList::Container* LList::getContainer(const size_t pos) const
{
    if (pos < 0) {
        throw std::out_of_range("Index of required Container is "
                                "out of range\n");
    }
    else if (pos >= this->_size) {
        throw std::out_of_range("Index of required Container is"
                                "out of range\n");
    }

    Container* bufContainer = this->_head;
    for (int i = 0; i < pos; ++i) {
        bufContainer = bufContainer->next;
    }

    return bufContainer;
}

int LList::operator[](size_t idx) const {
    return getContainer(idx)->value;
}

void LList::erase_at(size_t idx) {
    if (idx < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (idx > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (idx == 0) {
        Container* bufContainer = _head->next;
        delete _head;
        _head = bufContainer;
    }
    else {
        getContainer(idx - 1)->removeNext();
    }
    --_size;
}

void LList::insert_at(size_t idx, int val) {
    if (idx < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (idx > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (idx == 0) {
        push_front(val);
    }
    else {
        getContainer(idx - 1)->insertNext(val);
        ++_size;
    }
}

void LList::pop_back(int val) {
    erase_at(_size - 1);
}

void LList::pop_front(int val) {
    Container* bufContainer = _head->next;
    delete _head;
    _head = bufContainer;
    --_size;
}

void LList::reverse() {
    if(_size > 1){
        Container *tmp;
        for(int i = 0; i < _size; ++i){
            tmp = getContainer(_size - 1);
            this->insertContainer(i, tmp);
        }
        //иначе петля в последнем элементе
        tmp->next = nullptr;
    }
}

void LList::insertContainer(const size_t pos, LList::Container *container) {
    if (pos < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (pos > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (pos == 0) {
        Container *tmp = _head;
        _head = container;
        _head->next = tmp;
    }
    else {
        getContainer(pos - 1)->insertNext(container);
    }
}

void LList::forceContainerDelete(LList::Container *container) {
    if (container == nullptr) {
        return;
    }

    Container* nextDeleteContainer = container->next;
    delete container;
    forceContainerDelete(nextDeleteContainer);
}
