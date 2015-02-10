class table {
public:
    table();
    ~table();
    void insert(const data&);
    bool retrieve(key, data&)const;
    bool remove(key);
    void display(void)const;
private:

};
