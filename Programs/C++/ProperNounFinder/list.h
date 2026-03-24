#include <iostream>
#include <cstdlib>

typedef std::string ldata;

struct lnode{
    ldata data;
    lnode * next;
    lnode * prev;
    
    lnode(); 
    lnode(lnode* p, lnode* n); 
    lnode(lnode* p, const ldata & d, lnode * n);	
};

class list{
private:
    size_t _size;
    lnode * head;
    lnode * tail;
  
    size_t _computeIndex(int index) const;

    void _init();           
    void _copy(const list & orig); 
    void _destroy();         
      
public:
    list();
    	 
    ~list();

    list(const list & orig);
                    
    list & operator=(const list & rhs);
    
    void add(const ldata & item, int index);
           	 
    void removeAt(int index);

    void remove(const ldata & item);
     
    size_t find(const ldata & item) const;
    
    ldata get(int index) const;
     
    size_t size() const;
    
    void output() const;
};

