template <typename T>
string_map<T>::string_map(): _size(0), raiz(nullptr){
    raiz = new Nodo;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
}
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for (auto clave: _clavesDefinidas) {
        erase(clave);
    }

    for (auto clave: d._clavesDefinidas) {
        this->insert(make_pair(clave, d.at(clave)));
    }
}

template <typename T>
string_map<T>::~string_map(){
    if (raiz != nullptr){
        raiz->destruir(raiz);
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& value_type) {
    Nodo *nodo_iesimo = raiz;
    pair<string, T> clave_ = value_type;
    T* signi = new T(clave_.second);

    if (count(clave_.first) == 0){
        _size++;
    }
    _clavesDefinidas.insert(clave_.first);

    for (int i = 0; i < clave_.first.size(); ++i) {
        int valorEnASCII = int(clave_.first[i]);
        if (nodo_iesimo->siguientes[valorEnASCII] == nullptr){
            if (i == clave_.first.size()-1)
            {
                nodo_iesimo->siguientes[valorEnASCII] = new Nodo(signi);
            }
            else
            {
                nodo_iesimo->siguientes[valorEnASCII] = new Nodo();
            }
        }
        else
        {
            if (i == clave_.first.size()-1)
            {
                nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
                if (nodo_iesimo->definicion != nullptr){
                    delete nodo_iesimo->definicion;
                }
                nodo_iesimo->definicion = signi;
            }
        }
        nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
    }

}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* nodo_iesimo = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int valorEnASCII = int(clave[i]);
        if (nodo_iesimo->siguientes[valorEnASCII] != nullptr)
        {
            nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
        }
        else
        {
            return 0;
        }
    }
    if (nodo_iesimo->definicion != nullptr){
        return 1;
    }else{
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo *nodo_iesimo = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int valorEnASCII = int(clave[i]);
        nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
    }
    return *(nodo_iesimo->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo *nodo_iesimo = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int valorEnASCII = int(clave[i]);
        nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
    }
    return *(nodo_iesimo->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* nodo_iesimo = raiz;
    for (int i = 0; i < clave.size(); i++) {
        int valorEnASCII = int(clave[i]);
        nodo_iesimo = nodo_iesimo->siguientes[valorEnASCII];
    }
    delete nodo_iesimo->definicion;
    nodo_iesimo->definicion = nullptr;
    _clavesDefinidas.erase(clave);
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}
