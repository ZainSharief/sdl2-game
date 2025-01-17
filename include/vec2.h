#ifndef VEC2_H
#define VEC2_H

struct vec2 {
    float x, y;

    vec2(float x = 0, float y = 0) : x(x), y(y) {}
};

inline vec2 addVec2(vec2 item1, vec2 item2) 
{
    return vec2(item1.x + item2.x, item1.y + item2.y);
}

inline vec2 subVec2(vec2 item1, vec2 item2) 
{
    return vec2(item1.x - item2.x, item1.y - item2.y);
}

inline vec2 multVec2(vec2 item1, vec2 item2) 
{
    return vec2(item1.x * item2.x, item1.y * item2.y);
}

inline vec2 divVec2(vec2 item1, vec2 item2) 
{
    return vec2(item1.x / item2.x, item1.y / item2.y);
}

inline vec2 minVec2(vec2 item1, vec2 item2)
{
    vec2 newitem = vec2(0, 0);

    if (item1.x > item2.x){
        newitem.x = item2.x;
    } else {
        newitem.x = item1.x;
    }

    if (item1.y > item2.y){
        newitem.y = item2.y;
    } else {
        newitem.y = item1.y;
    }

    return newitem;
}

inline vec2 normaliseVec2(vec2 item)
{
    float total = abs(item.x) + abs(item.y);
    if (total > 0){
        item.x = item.x / total;
        item.y = item.y / total;
    }
    return item;
}

#endif