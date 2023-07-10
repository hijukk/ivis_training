/*
 * Generated by gdbus-codegen-glibmm 2.42.0. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#include "generated/bar_proxy.h"

#include <utility>

template<class T>
inline T specialGetter(Glib::Variant<T> variant)
{
    return variant.get();
}

template<>
inline std::string specialGetter(Glib::Variant<std::string> variant)
{
    // String is not guaranteed to be null-terminated, so don't use ::get()
    gsize n_elem;
    gsize elem_size = sizeof(char);
    char* data = (char*)g_variant_get_fixed_array(variant.gobj(), &n_elem, elem_size);

    return std::string(data, n_elem);
}

void org::foo::BarProxy::Baz(
    gint32 arg_Param1,
    const Gio::SlotAsyncReady &callback,
    const Glib::RefPtr<Gio::Cancellable> &cancellable,
    int timeout_msec)
{
    Glib::VariantContainerBase base;
    base = BarTypeWrap::Baz_pack(
        arg_Param1);

    m_proxy->call("Baz", callback, cancellable, base, timeout_msec);
}

void org::foo::BarProxy::Baz_finish(
    gint32 &out_Param2,
    const Glib::RefPtr<Gio::AsyncResult> &result)
{
    Glib::VariantContainerBase wrapped;
    wrapped = m_proxy->call_finish(result);

    Glib::Variant<gint32> out_Param2_v;
    wrapped.get_child(out_Param2_v, 0);
    out_Param2 = out_Param2_v.get();
}

gint32
org::foo::BarProxy::Baz_sync(
    gint32 arg_Param1,
    const Glib::RefPtr<Gio::Cancellable> &cancellable,
    int timeout_msec)
{
    Glib::VariantContainerBase base;
    base = BarTypeWrap::Baz_pack(
        arg_Param1);

    Glib::VariantContainerBase wrapped;
    wrapped = m_proxy->call_sync("Baz", cancellable, base, timeout_msec);

    gint32 out_Param2;
    Glib::Variant<gint32> out_Param2_v;
    wrapped.get_child(out_Param2_v, 0);
    out_Param2 = out_Param2_v.get();
    return out_Param2;
}

void org::foo::BarProxy::handle_signal(const Glib::ustring&/* sender_name */,
    const Glib::ustring& signal_name,
    const Glib::VariantContainerBase& parameters)
{
    static_cast<void>(signal_name); // maybe unused
    static_cast<void>(parameters); // maybe unused

    if (signal_name == "Signal") {
        if (parameters.get_n_children() != 1) return;
        Glib::Variant<gint32> base_SigNum;
        parameters.get_child(base_SigNum, 0);
        gint32 p_SigNum;
        p_SigNum = base_SigNum.get();

        Signal_signal.emit((p_SigNum));
    }
}

void org::foo::BarProxy::handle_properties_changed(
    const Gio::DBus::Proxy::MapChangedProperties &changed_properties,
    const std::vector<Glib::ustring> &/* invalidated_properties */)
{
    static_cast<void>(changed_properties); // maybe unused

    // Only check changed_properties since value will already be cached. Glib can be setup to get
    // values of invalidated properties in which case property will be in changed_properties when
    // value is actually received. See Gio::DBus::ProxyFlags::PROXY_FLAGS_GET_INVALIDATED_PROPERTIES .

}

org::foo::BarProxy::BarProxy(const Glib::RefPtr<Gio::DBus::Proxy> &proxy) : m_proxy(proxy)
{
    m_proxy->signal_signal().connect(sigc::mem_fun(this, &BarProxy::handle_signal));
    m_proxy->signal_properties_changed().
        connect(sigc::mem_fun(this, &BarProxy::handle_properties_changed));
}

void org::foo::BarProxy::createForBus(
    Gio::DBus::BusType busType,
    Gio::DBus::ProxyFlags proxyFlags,
    const std::string &name,
    const std::string &objectPath,
    const Gio::SlotAsyncReady &slot,
    const Glib::RefPtr<Gio::Cancellable> &cancellable)
{
    Gio::DBus::Proxy::create_for_bus(busType,
        name,
        objectPath,
        "org.foo.Bar",
        slot,
        cancellable,
        Glib::RefPtr<Gio::DBus::InterfaceInfo>(),
        proxyFlags);
}

Glib::RefPtr<org::foo::BarProxy> org::foo::BarProxy::createForBusFinish(const Glib::RefPtr<Gio::AsyncResult> &result)
{
    Glib::RefPtr<Gio::DBus::Proxy> proxy =
        Gio::DBus::Proxy::create_for_bus_finish(result);
    org::foo::BarProxy *p =
        new org::foo::BarProxy(proxy);
    return Glib::RefPtr<org::foo::BarProxy>(p);
}

Glib::RefPtr<org::foo::BarProxy> org::foo::BarProxy::createForBus_sync(
    Gio::DBus::BusType busType,
    Gio::DBus::ProxyFlags proxyFlags,
    const std::string &name,
    const std::string &objectPath,
    const Glib::RefPtr<Gio::Cancellable> &cancellable)
{
    Glib::RefPtr<Gio::DBus::Proxy> proxy =
        Gio::DBus::Proxy::create_for_bus_sync(busType,
            name,
            objectPath,
            "org.foo.Bar",
            cancellable,
            Glib::RefPtr<Gio::DBus::InterfaceInfo>(),
            proxyFlags);
    org::foo::BarProxy *p =
        new org::foo::BarProxy(proxy);
    return Glib::RefPtr<org::foo::BarProxy>(p);
}
