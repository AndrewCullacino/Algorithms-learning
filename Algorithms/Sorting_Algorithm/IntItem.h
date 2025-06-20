#ifndef ITEM_H  // this is the header guard(头文件保护) to avoid a function to be defined multiple times
#define ITEM_h

typedef int Item;

#define key(x) x

#define lt(x, y) (x <  y) // less than
#define le(x, y) (x <= y) // less than or equal to
#define ge(x, y) (x >= y) // greater than or equal to
#define gt(x, y) (x >  y) // greater than

#define show(x) printf("%d", x)
#define read(x) scanf("%d", &(x))

#endif  // header guard as well