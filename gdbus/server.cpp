#include "generated/bar_stub.h"
#include<unistd.h>

int num = 0;

class BarImpl : public org::foo::BarStub {
public:
    unsigned int usage_count() const {
        // Child
        return 0;
    }

    // Called when org.foo.bar.Baz() is invoked
    void Baz (gint32 param1, MethodInvocation &invocation) override {
        sleep(1);
        printf("Baz()..\n");
        // Return void
        num = param1;
        ++num;
        printf("num = %d\n", num);

        Signal_signal.emit(num * 2);

        invocation.ret(num);// return
    }


};

int main(int argc, char **argv) {
    // Initialize Glib and Gio
    Glib::init();
    Gio::init();

    // Instantiate and run the main loop
    Glib::RefPtr<Glib::MainLoop> ml = Glib::MainLoop::create();

    // Connect to the system bus and acquire our name
    BarImpl bi;
    guint connection_id = Gio::DBus::own_name(
            Gio::DBus::BUS_TYPE_SESSION,
            "org.foo.Bar",
            [&](const Glib::RefPtr<Gio::DBus::Connection> &connection,
                const Glib::ustring & /* name */) {
                g_print("Connected to bus.\n");
                if (bi.register_object(connection, "/org/foo/Bar") == 0)
                    ml->quit();
            },
            [&](const Glib::RefPtr<Gio::DBus::Connection> & /* connection */,
                const Glib::ustring & /* name */) {
                g_print("Name acquired.\n");
            },
            [&](const Glib::RefPtr<Gio::DBus::Connection> & /* connection */,
                const Glib::ustring & /* name */) {
                g_print("Name lost.\n");
                ml->quit();
            });

    ml->run();

    Gio::DBus::unown_name(connection_id);

    return 0;
}
