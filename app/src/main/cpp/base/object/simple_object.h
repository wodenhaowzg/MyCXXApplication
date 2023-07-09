//
// Created by ZaneWang on 2023/7/8.
//

#ifndef MYCXXAPPLICATION_SIMPLE_OBJECT_H
#define MYCXXAPPLICATION_SIMPLE_OBJECT_H


class SimpleObject {

public:
    SimpleObject() {
        init("");
    }

    SimpleObject(const char *name) {
        init(name);
    }

    int m_type = 1;
    const char *m_name = "";

    void FirstFunc() const {

    }

    void SecondFunc() {

    }

private:
    void init(const char *name) {
        m_name = name;
    }
};


#endif //MYCXXAPPLICATION_SIMPLE_OBJECT_H
