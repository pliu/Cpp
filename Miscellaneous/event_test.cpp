#include <event2/event.h>
#include <event2/event_struct.h>

static uint32_t c = 0;

void cb_func(evutil_socket_t fd, short what, void *arg)
{
    c++;
    printf("tick %d\n", c);
}

void run(struct event_base *base)
{
    struct timeval one_sec = { 1, 0 };
    struct event *ev;
    ev = event_new(base, -1, EV_PERSIST, cb_func, NULL);
    event_add(ev, &one_sec);
    event_base_dispatch(base);
}

int main() {
#ifdef WIN32
    WSADATA WSAData;
    WSAStartup(0x101, &WSAData);
#endif
    event_base *eb = event_base_new();
    run(eb);
}