#include <stdio.h>
#include <stdint.h>

#define PORT_MIN    1024
#define PORT_MAX    ((1<<16) - 1)

static uint16_t port_pool[PORT_MAX + 1];

static inline uint16_t port_pool_alloc(void)
{
    uint16_t port;
   
    port = port_pool[0];
    port_pool[0] = port_pool[port];
    return port;
}

static inline void port_pool_free(uint16_t port)
{
    port_pool[port] = port_pool[0];
    port_pool[0] = port;
}

static void port_pool_init(void)
{
    int port;

    for (port = PORT_MIN; port <= PORT_MAX; port++) {
        port_pool_free(port); 
    }
}

int main()
{
    uint16_t port;
    int count = 0;

    port_pool_init();

    while ((port = port_pool_alloc()) != 0) {
        printf("alloc: %hu\n", port);
        count++; 
    }

    printf("alloc count: %d\n", count);

}
