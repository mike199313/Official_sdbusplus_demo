#include <exception>
#include <map>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/sdbuspp_support/server.hpp>
#include <sdbusplus/server.hpp>
#include <string>
#include <tuple>

#include <xyz/openbmc_project/tutorial/hellomethod/Manager/server.hpp>

namespace sdbusplus::server::xyz::openbmc_project::tutorial::hellomethod
{

int Manager::_callback_Commit(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    auto o = static_cast<Manager*>(context);

    try
    {
        return sdbusplus::sdbuspp::method_callback(
                msg, o->get_bus().getInterface(), error,
                std::function(
                    [=](int32_t&& transactionId, std::string&& msg)
                    {
                        return o->commit(
                                transactionId, msg);
                    }
                ));
    }
    catch (const std::exception&)
    {
        o->get_bus().set_current_exception(std::current_exception());
        return 1;
    }
}

namespace details
{
namespace Manager
{
static const auto _param_Commit =
        utility::tuple_to_array(message::types::type_id<
                int32_t, std::string>());
static const auto _return_Commit =
        utility::tuple_to_array(std::make_tuple('\0'));
}
}





const vtable_t Manager::_vtable[] = {
    vtable::start(),

    vtable::method("Commit",
                   details::Manager::_param_Commit.data(),
                   details::Manager::_return_Commit.data(),
                   _callback_Commit),

    vtable::end()
};

} // namespace sdbusplus::server::xyz::openbmc_project::tutorial::hellomethod

