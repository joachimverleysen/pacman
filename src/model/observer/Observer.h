//
// Created by joachimverleysen on 11/26/24.
//

#ifndef DOODLEJUMP_OBSERVER_H
#define DOODLEJUMP_OBSERVER_H


class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};


#endif //DOODLEJUMP_OBSERVER_H
