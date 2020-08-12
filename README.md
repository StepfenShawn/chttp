# What is Chttp?
Chttp is a single-header HTTP request library for C/C++.

# Example
A http GET request example:  
```C++
#include "chttp.h"

int main()
{
    /*
     * GET(host, port, path)
     */
    GET("www.baidu.com", 80, "");
    return 0;
}
```

## TODO
* support the Linux and Mac OS
* Add more request types

## Contribution
Welcome to pull a request!