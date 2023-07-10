static const char interfaceXml0[] = R"XML_DELIMITER(<?xml version="1.0" encoding="UTF-8" ?>
<node name="/org/foo/Bar">
	<interface name="org.foo.Bar">
		<method name="Baz">
			<arg type="i" name="Param1" direction="in" />
			<arg type="i" name="Param2" direction="out" /> 
		</method>
		<signal name="Signal">
			<arg type="i" name="SigNum" />
		</signal>
	</interface>
</node>
)XML_DELIMITER";

#include "generated/bar_stub.h"

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

org::foo::BarStub::BarStub():
    m_interfaceName("org.foo.Bar")
{
    Signal_signal.connect(sigc::bind<0>(sigc::mem_fun(this, &BarStub::Signal_emitter),
            std::vector<Glib::ustring>({""})) );
    Signal_selectiveSignal.connect(sigc::mem_fun(this, &BarStub::Signal_emitter));
}

org::foo::BarStub::~BarStub()
{
    unregister_object();
}

guint org::foo::BarStub::register_object(
    const Glib::RefPtr<Gio::DBus::Connection> &connection,
    const Glib::ustring &object_path)
{
    if (!introspection_data) {
        try {
            introspection_data = Gio::DBus::NodeInfo::create_for_xml(interfaceXml0);
        } catch(const Glib::Error& ex) {
            g_warning("Unable to create introspection data for %s: %s", object_path.c_str(), ex.what().c_str());
            return 0;
        }
    }

    Gio::DBus::InterfaceVTable *interface_vtable =
        new Gio::DBus::InterfaceVTable(
            sigc::mem_fun(this, &BarStub::on_method_call),
            sigc::mem_fun(this, &BarStub::on_interface_get_property),
            sigc::mem_fun(this, &BarStub::on_interface_set_property));

    guint registration_id;
    try {
        registration_id = connection->register_object(object_path,
            introspection_data->lookup_interface("org.foo.Bar"),
            *interface_vtable);
    } catch(const Glib::Error &ex) {
        g_warning("Registration of object %s failed: %s", object_path.c_str(), ex.what().c_str());
        return 0;
    }

    m_registered_objects.emplace_back(RegisteredObject {
        registration_id,
        connection,
        object_path
    });

    return registration_id;
}

void org::foo::BarStub::unregister_object()
{
    for (const RegisteredObject &obj: m_registered_objects) {
        obj.connection->unregister_object(obj.id);
    }
    m_registered_objects.clear();
}

void org::foo::BarStub::on_method_call(
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &method_name,
    const Glib::VariantContainerBase &parameters,
    const Glib::RefPtr<Gio::DBus::MethodInvocation> &invocation)
{
    static_cast<void>(method_name); // maybe unused
    static_cast<void>(parameters); // maybe unused
    static_cast<void>(invocation); // maybe unused

    if (method_name.compare("Baz") == 0) {
        Glib::Variant<gint32> base_Param1;
        parameters.get_child(base_Param1, 0);
        gint32 p_Param1 = specialGetter(base_Param1);

        MethodInvocation methodInvocation(invocation);
        Baz(
            (p_Param1),
            methodInvocation);
    }

}

void org::foo::BarStub::on_interface_get_property(
    Glib::VariantBase &property,
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &property_name)
{
    static_cast<void>(property); // maybe unused
    static_cast<void>(property_name); // maybe unused

}

bool org::foo::BarStub::on_interface_set_property(
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &property_name,
    const Glib::VariantBase &value)
{
    static_cast<void>(property_name); // maybe unused
    static_cast<void>(value); // maybe unused

    return true;
}

void org::foo::BarStub::Signal_emitter(
    const std::vector<Glib::ustring> &destination_bus_names,gint32 SigNum)
{
    std::vector<Glib::VariantBase> paramsList;

    paramsList.push_back(Glib::Variant<gint32>::create((SigNum)));;

    const Glib::VariantContainerBase params =
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(paramsList);
    for (const RegisteredObject &obj: m_registered_objects) {
        for (const auto &bus_name: destination_bus_names) {
            obj.connection->emit_signal(
                    obj.object_path,
                    "org.foo.Bar",
                    "Signal",
                    bus_name,
                    params);
        }
    }
}


bool org::foo::BarStub::emitSignal(
    const std::string &propName,
    Glib::VariantBase &value)
{
    std::map<Glib::ustring, Glib::VariantBase> changedProps;
    std::vector<Glib::ustring> changedPropsNoValue;

    changedProps[propName] = value;

    Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>> changedPropsVar =
        Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(changedProps);
    Glib::Variant<std::vector<Glib::ustring>> changedPropsNoValueVar =
        Glib::Variant<std::vector<Glib::ustring>>::create(changedPropsNoValue);
    std::vector<Glib::VariantBase> ps;
    ps.push_back(Glib::Variant<Glib::ustring>::create(m_interfaceName));
    ps.push_back(changedPropsVar);
    ps.push_back(changedPropsNoValueVar);
    Glib::VariantContainerBase propertiesChangedVariant =
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(ps);

    for (const RegisteredObject &obj: m_registered_objects) {
        obj.connection->emit_signal(
            obj.object_path,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            Glib::ustring(),
            propertiesChangedVariant);
    }

    return true;
}
