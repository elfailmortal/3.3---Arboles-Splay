#include <iostream>
#include <sstream>
#include <string>
using namespace std;
//CLASE NODETREE
class NodeTree{
    public:
    //Atributos de los nodos del arbol
    int valor, nivel;
    NodeTree *padre;
    NodeTree *derecha;
    NodeTree *izquierda;
    NodeTree(int value){
        valor = value;
        nivel = 0;
        padre = nullptr;
        derecha = nullptr;
        izquierda = nullptr;
    };
};
//CLASE ArbolSPLAY junto con sus atributos y funciones
class ArbolSPLAY{
    public:
    NodeTree *root; //atributos de la raiz del arbol

    //constructores del arbol
    ArbolSPLAY(int value) { 
        root = new NodeTree(value); 
    }
    ArbolSPLAY() { 
        root = nullptr; 
    }
    //destructor del arbol
    ~ArbolSPLAY() { 
        delete root; 
    }
    //Funciones
    NodeTree* ZigDerecha(NodeTree*);
    NodeTree* ZagIzquierda(NodeTree*);
    NodeTree* insert(NodeTree*,int);
    /**
     * Metodo para insertar un valor entero dentro del árbol SPLAY
     * Se actualiza la raíz del arbol tras la inserción
     * 
     * Entrada: Un valor entero que será el valor a insertar en el árbol
     * 
     * Salida: no tiene salida, solo actualiza la raíz del arbol
     * 
     * Complejidad: O(log(n)) donde n es el número de nodos del árbol
     */
    void insertar(int value){
        //Define a la raiz como el nodo de raiz que resulta tras la actualizacion del arbol tras la inserción del valor entero de entrada
        //En el árbol SPLAY
        root = insert(root, value);
    };
    NodeTree* remove(NodeTree*,int);
    /**
     * Metodo para eliminar un valor del árbol SPLAY
     * Actualiza la raíz del árbol tras la eliminación
     * 
     * Entrada: un valor entero que será el valor a eliminar del arbol
     * 
     * Salida: no tiene salida, solo actualiza la raíz del árbol tras la eliminación
     *  
     * Complejidad: O(log(n)) donde n es el número de nodos del árbol
    */ 
    void eliminar(int value){
        //Define a la raíz como el resultado de la actualizacion del arbol tras la eliminacion del valor de entrada
        root = remove(root, value);
    };
    NodeTree* splay(NodeTree*,int);
    NodeTree* search(NodeTree*,int);
    /**
     * Método para buscar un valor entero dentro del árbol
     * Se actualiza la raíz del árbol tras la busqueda
     * 
     * Entrada: un valor entero que será el valor que se buscara en el arbol
     * 
     * Salida: No tiene salida, solo actualiza el valor de la raíz del árbol
     * 
     * Complejidad: O(log(n)) donde n es el número de nodos del árbol
     */
    void buscar(int value){
        //Se define a la raiz como el resultado de la actualizacion del arbol tras la busqueda del valor en el arbol
        root = search(root,value);
    };
    int getLevel(NodeTree*);
    /**
     * Función para obtener la raíz del árbol SPLAY
     * 
     * Entrada: No tiene entrada
     * 
     * Salida: Un puntero del tipo NodeTree que apunta al nodo raíz del árbol SPLAY
     * 
     * Complejidad: O(1)
     */
    NodeTree* getRoot(){
        return this->root;
    };
    void showTree(NodeTree*);
};
/**
 * Función para obtener el nivel de un nodo del arbol SPLAY
 * Se determina apartir del nivel de su nodo padre
 * Se hace recursiva mente para todos los nodos del arbol
 * 
 * Entrada: un puntero del tipo NodeTree que apunta al nodo que se quiere obtener su nivel
 * 
 * Salida: un valor entero con el nivel del nodo especificado, la raiz tiene un nivel de 0
 * 
 * Complejidad: O(n) donde n es el número de nodos del árbol
 */
int ArbolSPLAY::getLevel(NodeTree* nodo){
    //Si el nodo esta vacío o no existe
    //Su nivel es 0
    if(!nodo){
        return 0;
    }
    //Se asigna el nivel del nodo
    //Si existe un nodo padre, se toma su nivel y se le suma uno, pero si no existe un padre
    //Como en el caso de la raíz el nivel será 0 al ser la raíz
    nodo->nivel = (nodo->padre) ? nodo->padre->nivel + 1 : 0;
    //Se hace lo mismo con los nodos de la izquierda y el de la derecha de nuestro nodo de entrada
    getLevel(nodo->izquierda);
    getLevel(nodo->derecha);
    //Se regresa el nivel de nuestro nodo de entrada
    return nodo->nivel;
};
/**
 * Funcion para hacer la rotacion a la derecha (zig) del nodo especificado
 * Esta funcion es usada para ajustar la estructura del arbol SPLAY
 * Entrada: un nodo del tipo NodeTree en el que se hara la rotación
 * Salida: un nodo puntero del tipo NodeTree que apuntara a la nueva raíz del árbol
 * Complejidad: O(1)
 */
NodeTree* ArbolSPLAY::ZigDerecha(NodeTree* nodo) {
    //Se define un nodo auxilizar que sera igual al hijo izquierdo del nodo
    NodeTree *aux = nodo->izquierda;
    //Se actualiza el hijo izquierdo del nodo para que este sea igual al hijo derecho del nodo auxiliar
    nodo->izquierda = aux->derecha;
    //Si el hijo derecho del nodo auxiliar no esta vacio se actualizara su nodo padre para que apunte al nodo original
    if (aux->derecha != nullptr) {
        aux->derecha->padre = nodo;
    };
    //Se realiza la rotacion en el nodo auxiliar se convierte en el nuevo padre y el nodo original se convierte en su hijo derecho
    aux->derecha = nodo;
    //Se actualiza el padre del nodo original para que sea igual al padre del nodo auxiliar
    aux->padre = nodo->padre;
    //Se actualiza el padre del nodo original para que sea igual al nodo auxiliar
    nodo->padre = aux;
    //Se actualizan los niveles del nodo original y del nodo auxiliar
    nodo->nivel = getLevel(nodo);
    aux->nivel = getLevel(aux);
    //Se devuelve el nodo auxiliar
    return aux;
};
/**
 * Función para hacer la rotación a la izquierda (zag) del nodo que se especifique
 * Se usa esta funcion para actualizar el arbol SPLAY
 * Entrada: un nodo del tipo NodeTree en el que se hara la rotación
 * Salida: un puntero del tipo NodeTree que apunta a la nueva raiz del árbol
 * Complejidad: O(1)
 */
NodeTree* ArbolSPLAY::ZagIzquierda(NodeTree* nodo) {
    //Se define un nodo auxiliar que apuntara al hijo derecho del nodo original
    NodeTree *aux = nodo->derecha;
    //Se actualiza el hijo derecho del nodo original para que sea igual al hijo izquierdo del nodo auxiliar
    nodo->derecha = aux->izquierda;
    //Si el hijo izquierdo del nodo auxiliar no es nulo, se actualizara su nodo padre para que este sea el nodo original
    if (aux->izquierda != nullptr) {
        aux->izquierda->padre = nodo;
    };
    //Se realiza la rotación el nodo auxiliar sera el nuevo padre y su hijo izquierdo sera el nuevo nodo original
    //El hijo izquierdo del nodo auxiliar será igual al nodo original
    aux->izquierda = nodo;
    //El nodo padre del nodo auxiliar será igual al nodo padre del nodo original
    aux->padre = nodo->padre;
    //El nodo padre del nodo original sera igual al nodo auxiliar
    nodo->padre = aux;
    //Se actualizan los niveles de los nodos
    nodo->nivel = getLevel(nodo);
    aux->nivel = getLevel(aux);
    //Se regresa el nodo auxiliar que sera el nuevo nodo raiz del arbol tras la rotación
    return aux;
};
/**
 * Función para realizar la operacion SPLAY para ajustar la posición del nodo con un valor especificado en el arbol
 * Reorganizando al arbol en el proceso
 * Entradas: un puntero al nodo raíz del árbol del tipo NodeTree y un valor entero que se quiere llevar a la raíz del arbol
 * Salida: un puntero del tipo NodeTree que apunta al nuevo nodo raíz del arbol SPLAY, que será el nodo que contiene el valor especificado
 * Si el valor no existe en el arbol, el nodo raíz apuntará al ultimo nodo visitado
 * 
 * Complejidad: O(log(n)) donde n es el número de nodos del árbol
 */
NodeTree* ArbolSPLAY::splay(NodeTree* nodo, int value) {
    //Si el nodo actual es nulo o el valor del nodo actual coincide con el valor original
    //Se retorna el nodo actual
    if (nodo == nullptr || nodo->valor == value) {
        return nodo;
    };
    //Si el valor es menor que el valor del nodo actual se buscará en el subarbol izquierdo
    if (nodo->valor > value) {
        //Si no existe un hijo izquierdo se retorna el nodo actual
        if (nodo->izquierda == nullptr){
            return nodo;
        };
        //Si el valor del hijo izquierdo es mayor que el valor buscado
        if (nodo->izquierda->valor > value) {
            //Se realiza la operacion SPLAY de forma recursiva en el hijo izquierdo del hijo izquierdo del nodo
            nodo->izquierda->izquierda = splay(nodo->izquierda->izquierda, value);
            //Se realiza una rotacion a la derecha en el nodo actual
            nodo = ZigDerecha(nodo);
        //Si el valor del subarbol izquierdo es menor que el valor buscado
        }else if (nodo->izquierda->valor < value) {
            //Se realiza la operacion SPLAY de forma recursiva en el hijo derecho del hijo izquierdo del nodo
            nodo->izquierda->derecha = splay(nodo->izquierda->derecha, value);
            //Si el hijo derecho del hijo izquierdo no es nulo se realiza una rotacion a la izquierda
            if (nodo->izquierda->derecha != nullptr) {
                nodo->izquierda = ZagIzquierda(nodo->izquierda);
            };
        };
        //Si hay un hijo izquierdo se realiza una rotacion a la derecha y si no hay un hijo izquierdo se regresa el nodo
        return (nodo->izquierda == nullptr) ? nodo : ZigDerecha(nodo);
    //Si el valor es mayor que el valor del nodo actual se buscara en el subarbol derecho
    } else {
        //Si no existe un hijo derecho se regresa el nodo actual
        if (nodo->derecha == nullptr){
            return nodo;
        };
        //Si el valor del hijo derecho del nodo es mayor que el valor
        if (nodo->derecha->valor > value) {
            //Se hace una operacion splay recursiva en el hijo izquierdo del hijo derecho del nodo
            nodo->derecha->izquierda = splay(nodo->derecha->izquierda, value);
            //Si el hijo izquierdo del hijo derecho no es nulo
            if (nodo->derecha->izquierda != nullptr) {
                //Se realiza una rotacion derecha
                nodo->derecha = ZigDerecha(nodo->derecha);
            };
        //Si el valor del hijo derecho del nodo es menor que el valor
        } else if (nodo->derecha->valor < value) {
            //Se realiza una operacion SPLAY en el hijo derecho del hijo derecho del nodo
            nodo->derecha->derecha = splay(nodo->derecha->derecha, value);
            //Se realiza una rotacion a la izquierda
            nodo = ZagIzquierda(nodo);
        }
        //Si no el nodo no tiene un hijo derecho se regresa el nodo actual, pero si existe un hijo derecho se hace una rotacion izquierda
        return (nodo->derecha == nullptr) ? nodo : ZagIzquierda(nodo);
    };
};
/**
 * Funcion para insertar un nodo con un valor especifico al arbol
 * La funcion ajustara al arbol usando la operacion SPLAY antes de hacer el insert
 * 
 * Entradas: un puntero del tipo NodeTree que apunta al nuevo nodo raíz del arbol
 * un valor entero que sera el valor a ser insertado
 * 
 * Salida: un puntero NodeTree que apunta al nuevo nodo raíz del arbol
 * 
 * Complejidad: O(log(n)) donde n es el número de nodos del árbol
 */
NodeTree* ArbolSPLAY::insert(NodeTree* nodo, int value) {
    // Si el nodo es nulo, se crea un nuevo nodo con el valor y se retorna
    if (nodo == nullptr) {
        return new NodeTree(value);
    };
    // Se realiza la operación Splay en el árbol con el valor a insertar
    nodo = splay(nodo, value);
    // Si el valor ya existe en el árbol, se retorna el nodo existente
    if (nodo->valor == value) {
        return nodo;
    };
    // Se crea un nuevo nodo auxiliar con el valor a insertar
    NodeTree* aux = new NodeTree(value);
    // Si el valor a insertar es menor que el valor del nodo actual
    if (nodo->valor > value) {
        aux->derecha = nodo; // El nuevo nodo se convierte en padre del nodo actual
        aux->izquierda = nodo->izquierda; // El hijo izquierdo del nodo actual se convierte en el hijo izquierdo del nuevo nodo
        // Si hay un hijo izquierdo, se actualiza su padre
        if (aux->izquierda != nullptr) {
            aux->izquierda->padre = aux;
        };
        // Se establece que el hijo izquierdo del nodo actual es nulo
        nodo->izquierda = nullptr;
    } 
    // Si el valor a insertar es mayor que el valor del nodo actual
    else {
        aux->izquierda = nodo; // El nuevo nodo se convierte en padre del nodo actual
        aux->derecha = nodo->derecha; // El hijo derecho del nodo actual se convierte en el hijo derecho del nuevo nodo
        // Si hay un hijo derecho, se actualiza su padre
        if (aux->derecha != nullptr) {
            aux->derecha->padre = aux;
        }
        // Se establece que el hijo derecho del nodo actual es nulo
        nodo->derecha = nullptr;
    };
    // Se actualizan los padres de los nodos
    nodo->padre = aux; // El nodo original ahora tiene como padre al nuevo nodo
    nodo->nivel = getLevel(nodo); // Se actualiza el nivel del nodo original
    aux->nivel = getLevel(aux); // Se actualiza el nivel del nuevo nodo
    // Se retorna el nuevo nodo raíz que es el nodo auxiliar
    return aux;
};
/**
 * Función para buscar un valor en el arbol SPLAY
 * Si se encuentra el valor, la funcion convierte al nodo con ese valor en el nuevo nodo raíz del arbol
 * 
 * Entradas: 
 * Un puntero del tipo NodeTree que apunta al nodo raíz del arbol
 * Un valor entero que será el que busca en el arbol
 * 
 * Salida: Un puntero NodeTree que contiene el nodo con el valor buscado, o el ultimo nodo visitado si es que no se encuentra el valor en el arbol
 * 
 * Complejidad: O(log(n)) donde n es el número de nodos del árbol
 */
NodeTree* ArbolSPLAY::search(NodeTree* raiz,int value){
    //Se llama a la funcion SPLAY, para buscar el valor y reorganizar la estructura del arbol
    return splay(raiz,value);
};
/**
 * Funcion para eliminar un nodo con un valor especificado del arbol
 * La funcion reorganiza al arbol SPLAY antes de hacer la eliminacion
 * 
 * Entradas:
 * Un puntero del tipo NodeTree que apunta al nodo raíz del arbol en el que se hara la eliminación
 * Un valor entero que sera el valor a eliminar del arbol
 * 
 * Salida:
 * Un puntero del tipo NodeTree que apuntara al nuevo nodo raíz del arbol despues de la eliminacion
 * o un nodo vacio si es que arbol queda vacio
 * 
 * Complejidad: O(log(n)) donde n es el número de nodos del árbol
 */
NodeTree* ArbolSPLAY::remove(NodeTree* nodo, int value) {
    // Si el nodo es nulo, se retorna nullptr
    if (!nodo) {
        return nullptr;
    }
    // Se realiza la operación Splay para mover el nodo con el valor a eliminar a la raíz
    nodo = splay(nodo, value);
    // Si el valor no coincide con el nodo raíz, el valor no está en el árbol
    if (value != nodo->valor) {
        return nodo;
    }
    NodeTree *aux; // Variable auxiliar para almacenar el nodo a eliminar
    // Caso 1: Si no hay hijo izquierdo, se actualiza el nodo raíz a su hijo derecho
    if (!nodo->izquierda) {
        aux = nodo; // Guardamos el nodo a eliminar
        nodo = nodo->derecha; // Asignamos el hijo derecho como nuevo nodo raíz
        if (nodo != nullptr) {
            nodo->padre = nullptr; // Actualizamos el padre del nuevo nodo raíz
        }
    } 
    // Caso 2: Si hay un hijo izquierdo
    else {
        aux = nodo; // Guardamos el nodo a eliminar
        // Se realiza Splay en el hijo izquierdo para encontrar el máximo (el nodo más grande)
        nodo = splay(nodo->izquierda, value);
        // Se establece el hijo derecho del nuevo nodo raíz
        nodo->derecha = aux->derecha;
        if (nodo->derecha != nullptr) {
            nodo->derecha->padre = nodo; // Actualizamos el padre del hijo derecho
        }
    }
    // Liberamos la memoria del nodo a eliminar
    delete aux;
    // Si el nuevo nodo raíz no es nulo, actualizamos su padre y nivel
    if (nodo != nullptr) {
        nodo->padre = nullptr; // Actualizamos el padre del nuevo nodo raíz
        nodo->nivel = getLevel(nodo); // Actualizamos el nivel del nuevo nodo raíz
    }
    return nodo; // Retornamos el nuevo nodo raíz
};
/**
 * Funcion para mostrar el arbol SPLAY incluyendo información sobre el nodo, su padre hijos, nivel y factor de balanceo.
 * ejemplo: 4 (padre: null, 'L': 2  'R': 6)  lvl: 0
 * 
 * Entrada: Un puntero del tipo NodeTree* que apunta al nodo raíz del arbol que se va a mostrar
 * 
 * Salida: no tiene salida, pero se imprime el arbol en el formato que se menciono previamente
 * 
 * Complejidad: O(n) donde n es el número de nodos del árbol   
 */
void ArbolSPLAY::showTree(NodeTree* raiz){
    // Si el nodo actual es nulo, se retorna
    if (raiz == nullptr) {
        return;
    }
    // Se obtienen los valores del padre, hijo izquierdo y derecho para imprimir
    string parent = (raiz->padre) ? to_string(raiz->padre->valor) : "NULL";
    string left = (raiz->izquierda) ? to_string(raiz->izquierda->valor) : "NULL";
    string right = (raiz->derecha) ? to_string(raiz->derecha->valor) : "NULL";
    // Se calcula el Factor de Balance (FB)
    int FB = getLevel(raiz->izquierda) - getLevel(raiz->derecha);
    // Se imprime la información del nodo actual
    cout << raiz->valor << " (padre: " << parent << ", L: " << left << " R: " << right << ") lvl: " << raiz->nivel << ", BF: " << FB << endl;
    // Se llaman recursivamente a los hijos izquierdo y derecho para mostrar sus datos
    showTree(raiz->izquierda);
    showTree(raiz->derecha);
};
int main(){
    cout << "Inserts  1, 7, 8, 24,  30, 9.   Mostrar el arbol." << endl;
    ArbolSPLAY* ASplay = new ArbolSPLAY();
    ASplay->insertar(1);
    ASplay->insertar(7);
    ASplay->insertar(8);
    ASplay->insertar(24);
    ASplay->insertar(30);
    ASplay->insertar(9);
    ASplay->showTree(ASplay->getRoot());
    cout << endl;
    cout << "Delete:  7. Mostrar el arbol. " << endl;
    ASplay->eliminar(7);
    ASplay->showTree(ASplay->getRoot());
    cout << endl;
    cout << "Buscar: 9 " << endl;
    ASplay->buscar(9);
    ASplay->showTree(ASplay->getRoot());
    cout << endl;
    cout << "Insert 5 y 10. Mostrar el arbol." << endl;
    ASplay->insertar(5);
    ASplay->insertar(10);
    ASplay->showTree(ASplay->getRoot());
};
