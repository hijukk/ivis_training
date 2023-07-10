#include "generated/bar_proxy.h"
#include<unistd.h>

Glib::RefPtr<org::foo::BarProxy> proxy;

void on_signal(const gint s);

void on_baz_finished(const Glib::RefPtr<Gio::AsyncResult> &result) {
    sleep(1);
    printf("on_baz_finished\n");
    gint res;
    
    proxy->Baz_finish(res, result);
    printf("res = %d\n", ++res);
    proxy->Baz(res, sigc::ptr_fun(&on_baz_finished));
}

void proxy_created(const Glib::RefPtr<Gio::AsyncResult> result) {
    sleep(1);
    gint res = 123;
    
    printf("proxy_created\n");

    proxy = org::foo::BarProxy::createForBusFinish(result);
    proxy->Signal_signal.connect(sigc::ptr_fun(&on_signal));
    proxy->Baz(res, sigc::ptr_fun(&on_baz_finished));

    std::cout << "res = " << res << std::endl;
}

void on_signal(const gint s)
{
    proxy->Baz(s, sigc::ptr_fun(&on_baz_finished));
}

int main(int argc, char **argv) {
    Glib::init();
    Gio::init();

    org::foo::BarProxy::createForBus(Gio::DBus::BUS_TYPE_SESSION,
                                     Gio::DBus::PROXY_FLAGS_NONE,
                                     "org.foo.Bar",
                                     "/org/foo/Bar",
                                     sigc::ptr_fun(&proxy_created));

    Glib::RefPtr<Glib::MainLoop> ml = Glib::MainLoop::create();
    ml->run();

    return 0;
}
