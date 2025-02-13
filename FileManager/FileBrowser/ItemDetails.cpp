#include "ItemDetails.h"

std::ostream& operator<<(std::ostream& os, const ItemDetailsDisplay& item) {
    os << std::left << item.displayName;
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            os << arg;
        }
        else if constexpr (std::is_same_v<T, uintmax_t>) {
            os << arg;
        }
        else if constexpr (std::is_same_v<T, std::filesystem::file_time_type>) {
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(arg - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
            //os << std::put_time(std::localtime(&cftime), "%F %T");
        }
        }, item.value);
    return os;
}