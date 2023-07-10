#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <glibmm.h>
#include <giomm.h>
#include "generated/bar_common.h"

namespace org {
namespace foo {

class BarProxy : public Glib::ObjectBase {
public:
    static void createForBus(Gio::DBus::BusType busType,
                             Gio::DBus::ProxyFlags proxyFlags,
                             const std::string &name,
                             const std::string &objectPath,
                             const Gio::SlotAsyncReady &slot,
                             const Glib::RefPtr<Gio::Cancellable> &cancellable = {});

    static Glib::RefPtr<BarProxy> createForBusFinish (const Glib::RefPtr<Gio::AsyncResult> &result);

    static Glib::RefPtr<BarProxy> createForBus_sync(
        Gio::DBus::BusType busType,
        Gio::DBus::ProxyFlags proxyFlags,
        const std::string &name,
        const std::string &objectPath,
        const Glib::RefPtr<Gio::Cancellable> &cancellable = {});

    Glib::RefPtr<Gio::DBus::Proxy> dbusProxy() const { return m_proxy; }

    void Baz(
        gint32 Param1,
        const Gio::SlotAsyncReady &slot,
        const Glib::RefPtr<Gio::Cancellable> &cancellable = {},
        int timeout_msec = -1);

    void Baz_finish (
        gint32 &Param2,
        const Glib::RefPtr<Gio::AsyncResult> &res);

    gint32
    Baz_sync(
        gint32 Param1,const Glib::RefPtr<Gio::Cancellable> &cancellable = {},
        int timeout_msec = -1);

    sigc::signal<void, gint32 > Signal_signal;

    void reference() const override {}
    void unreference() const override {}

protected:
    Glib::RefPtr<Gio::DBus::Proxy> m_proxy;

private:
    BarProxy(const Glib::RefPtr<Gio::DBus::Proxy> &proxy);

    void handle_signal(const Glib::ustring &sender_name,
                       const Glib::ustring &signal_name,
                       const Glib::VariantContainerBase &parameters);

    void handle_properties_changed(const Gio::DBus::Proxy::MapChangedProperties &changed_properties,
                                   const std::vector<Glib::ustring> &invalidated_properties);

};

}// foo
}// org

